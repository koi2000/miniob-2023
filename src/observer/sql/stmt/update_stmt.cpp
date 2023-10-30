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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "util/date.h"

UpdateStmt::UpdateStmt(Table* table, std::vector<Field> field, std::vector<Value> value)
    : table_(table), fields_(field), values_(value) {}

UpdateStmt::UpdateStmt(Table* table, std::vector<Field> field, std::vector<Value> value, FilterStmt* filter_stmt)
    : table_(table), fields_(field), values_(value), filter_stmt_(filter_stmt) {}

RC UpdateStmt::create(Db* db, const UpdateSqlNode& update, Stmt*& stmt) {
    const char* table_name = update.relation_name.c_str();
    if (db == nullptr || table_name == nullptr) {
        LOG_WARN("Invalid argument!");
        return RC::INVALID_ARGUMENT;
    }
    // 校验数据库是否存在
    Table* table = db->find_table(table_name);
    if (table == nullptr) {
        LOG_WARN("db not found!");
        return RC::SCHEMA_TABLE_EXIST;
    }
    // 校验update时是否有对应类型字段
    std::vector<Value> values = update.value;
    const TableMeta& table_meta = table->table_meta();
    const int field_num = table_meta.field_num() - table_meta.sys_field_num();
    const int sys_field_num = table_meta.sys_field_num();
    RC rc = RC::INVALID_ARGUMENT;
    std::vector<Field> fields;
    for (int k = 0; k < update.attribute_name.size(); k++) {
        for (int i = sys_field_num; i < field_num; i++) {
            const FieldMeta* field_meta = table_meta.field(i);
            const AttrType field_type = field_meta->type();
            const char* field_name = field_meta->name();
            // 匹配成功
            if (update.attribute_name[k] == field_name) {
                rc = RC::SUCCESS;
                Field field = Field(table, field_meta);
                fields.push_back(field);
                // 针对Date类型进行特殊处理
                if (field_type == DATES) {
                    int32_t date = -1;
                    RC rc = string_to_date(values[k].get_string().c_str(), date);
                    if (rc != RC::SUCCESS) {
                        LOG_TRACE("Parse type Date Error");
                        return rc;
                    }
                    value_init_date(&values[k], date);
                }
                break;
            }
        }
    }

    // 处理Where子句
    if (!update.conditions.empty()) {
        FilterStmt* filter_stmt = nullptr;
        std::unordered_map<std::string, Table*> table_map;
        table_map.insert(std::pair<std::string, Table*>(std::string(table_name), table));
        RC rc = FilterStmt::create(db, table, &table_map, update.conditions.data(),
                                   static_cast<int>(update.conditions.size()), filter_stmt);
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
            return rc;
        }
        stmt = new UpdateStmt(table, fields, values, filter_stmt);
    }
    else {
        stmt = new UpdateStmt(table, fields, values);
    }
    return rc;
}
