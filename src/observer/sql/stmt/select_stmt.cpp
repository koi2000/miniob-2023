/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

SelectStmt::~SelectStmt() {
    if (nullptr != filter_stmt_) {
        delete filter_stmt_;
        filter_stmt_ = nullptr;
    }
    if (nullptr != inner_join_filter_stmt_) {
        delete filter_stmt_;
        filter_stmt_ = nullptr;
    }
}

static void wildcard_fields(Table* table, std::vector<Field>& field_metas) {
    const TableMeta& table_meta = table->table_meta();
    const int field_num = table_meta.field_num();
    for (int i = table_meta.sys_field_num(); i < field_num; i++) {
        field_metas.push_back(Field(table, table_meta.field(i)));
    }
}

RC SelectStmt::create(Db* db, const SelectSqlNode& select_sqls, Stmt*& stmt) {
    if (nullptr == db) {
        LOG_WARN("invalid argument. db is null");
        return RC::INVALID_ARGUMENT;
    }
    SelectSqlNode& select_sql = const_cast<SelectSqlNode&>(select_sqls);
    // collect tables in `from` statement
    std::vector<Table*> tables;
    std::unordered_map<std::string, Table*> table_map;
    for (size_t i = 0; i < select_sql.relations.size(); i++) {
        const char* table_name = select_sql.relations[i].c_str();
        if (nullptr == table_name) {
            LOG_WARN("invalid argument. relation name is null. index=%d", i);
            return RC::INVALID_ARGUMENT;
        }

        Table* table = db->find_table(table_name);
        if (nullptr == table) {
            LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
            return RC::SCHEMA_TABLE_NOT_EXIST;
        }

        tables.push_back(table);
        table_map.insert(std::pair<std::string, Table*>(table_name, table));
    }
    Table* default_table = nullptr;
    if (tables.size() == 1) {
        default_table = tables[0];
    }
    // 处理aggregate相关问题
    if (!select_sql.aggrs.empty() && !select_sql.attributes.empty()) {
        return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    std::vector<AggrNode>& aggrNodes = const_cast<std::vector<AggrNode>&>(select_sql.aggrs);
    if (!aggrNodes.empty()) {
        for (AggrNode& aggrNode : aggrNodes) {
            if (aggrNode.is_attr) {
                return RC::SCHEMA_TABLE_NOT_EXIST;
            }

            if (aggrNode.attributes.empty()) {
                return RC::SCHEMA_TABLE_NOT_EXIST;
            }
            std::string relAttr = aggrNode.attributes[0];
            char delimiter = '.';
            if (relAttr.find(delimiter) != std::string::npos) {
                // 分割字符串
                std::vector<std::string> tokens;
                size_t startPos = 0;
                size_t endPos = relAttr.find(delimiter);

                while (endPos != std::string::npos) {
                    tokens.push_back(relAttr.substr(startPos, endPos - startPos));
                    startPos = endPos + 1;
                    endPos = relAttr.find(delimiter, startPos);
                }
                // 处理最后一个分割后的部分
                tokens.push_back(relAttr.substr(startPos));
                aggrNode.relation = tokens[0];
                aggrNode.attribute = tokens[1];
            }
            else {
                aggrNode.relation = default_table->name();
                aggrNode.attribute = aggrNode.attributes[0];
            }
            if (aggrNode.attributes.size() >= 2) {
                return RC::SCHEMA_TABLE_NOT_EXIST;
            }
        }
    }

    for (AggrNode& aggrNode : select_sql.aggrs) {
        if (aggrNode.relation == "") {
            aggrNode.relation = default_table->name();
        }
        std::vector<FieldMeta> field_metas = *table_map[aggrNode.relation]->table_meta().field_metas();
        int flag = 0;
        for (FieldMeta field_meta : field_metas) {
            std::string re = aggrNode.attribute;
            if (field_meta.name() == aggrNode.attribute) {
                flag = 1;
                break;
            }
            if (aggrNode.attribute == "*") {
                if (aggrNode.type == MAXS || aggrNode.type == MINS || aggrNode.type == AVGS) {
                    return RC::SCHEMA_FIELD_MISSING;
                }
                flag = 1;
                break;
            }
        }
        if (!flag)
            return RC::SCHEMA_FIELD_MISSING;
    }

    // collect query fields in `select` statement
    std::vector<Field> query_fields;
    std::vector<OrderBySqlNode> orderBySqlNodes = select_sql.order_bys;
    // 校验一下表和字段
    for (int i = 0; i < orderBySqlNodes.size(); i++) {
        OrderBySqlNode* orderBySqlNode = &orderBySqlNodes[i];
        if (orderBySqlNode->relation == "") {
            orderBySqlNode->relation = tables[0]->name();
        }
        if (!table_map.count(orderBySqlNode->relation)) {
            return RC::SCHEMA_TABLE_NOT_EXIST;
        }
        Table* table = table_map[orderBySqlNode->relation];
        const std::vector<FieldMeta> field_metas = *table->table_meta().field_metas();
        int flag = 0;
        for (FieldMeta field_meta : field_metas) {
            if (field_meta.name() == orderBySqlNode->attribute) {
                flag = 1;
            }
        }
        if (!flag)
            return RC::SCHEMA_FIELD_MISSING;
    }

    for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
        const RelAttrSqlNode& relation_attr = select_sql.attributes[i];

        if (common::is_blank(relation_attr.relation_name.c_str()) &&
            0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
            for (Table* table : tables) {
                wildcard_fields(table, query_fields);
            }
        }
        else if (!common::is_blank(relation_attr.relation_name.c_str())) {
            const char* table_name = relation_attr.relation_name.c_str();
            const char* field_name = relation_attr.attribute_name.c_str();

            if (0 == strcmp(table_name, "*")) {
                if (0 != strcmp(field_name, "*")) {
                    LOG_WARN("invalid field name while table is *. attr=%s", field_name);
                    return RC::SCHEMA_FIELD_MISSING;
                }
                for (Table* table : tables) {
                    wildcard_fields(table, query_fields);
                }
            }
            else {
                auto iter = table_map.find(table_name);
                if (iter == table_map.end()) {
                    LOG_WARN("no such table in from list: %s", table_name);
                    return RC::SCHEMA_FIELD_MISSING;
                }

                Table* table = iter->second;
                if (0 == strcmp(field_name, "*")) {
                    wildcard_fields(table, query_fields);
                }
                else {
                    const FieldMeta* field_meta = table->table_meta().field(field_name);
                    if (nullptr == field_meta) {
                        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
                        return RC::SCHEMA_FIELD_MISSING;
                    }

                    query_fields.push_back(Field(table, field_meta));
                }
            }
        }
        else {
            if (tables.size() != 1) {
                LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
                return RC::SCHEMA_FIELD_MISSING;
            }

            Table* table = tables[0];
            const FieldMeta* field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
            if (nullptr == field_meta) {
                LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(),
                         relation_attr.attribute_name.c_str());
                return RC::SCHEMA_FIELD_MISSING;
            }

            query_fields.push_back(Field(table, field_meta));
        }
    }

    LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

    // create filter statement in `where` statement
    FilterStmt* filter_stmt = nullptr;
    RC rc = FilterStmt::create(db, default_table, &table_map, select_sql.conditions.data(),
                               static_cast<int>(select_sql.conditions.size()), filter_stmt);
    if (rc != RC::SUCCESS) {
        LOG_WARN("cannot construct filter stmt");
        return rc;
    }
    // create filter statement in 'inner join' statement
    FilterStmt* inner_join_filter_stmt = nullptr;
    rc = FilterStmt::create(db, default_table, &table_map, select_sql.inner_join_conditions.data(),
                            static_cast<int>(select_sql.inner_join_conditions.size()), inner_join_filter_stmt);
    if (rc != RC::SUCCESS) {
        LOG_WARN("cannot construct filter stmt");
        return rc;
    }
    // everything alright
    SelectStmt* select_stmt = new SelectStmt();
    // TODO add expression copy
    select_stmt->tables_.swap(tables);
    select_stmt->table_map_ =table_map;
    select_stmt->query_fields_.swap(query_fields);
    select_stmt->filter_stmt_ = filter_stmt;
    select_stmt->inner_join_filter_stmt_ = inner_join_filter_stmt;
    select_stmt->aggr_nodes_ = aggrNodes;
    select_stmt->orderBySqlNodes_ = orderBySqlNodes;
    stmt = select_stmt;
    return RC::SUCCESS;
}
