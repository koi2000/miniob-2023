/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include "sql/expr/sub_expression.h"
#include "sql/operator/aggregate_logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/orderby_logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/optimizer/physical_plan_generator.h"

#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/update_stmt.h"

using namespace std;

RC LogicalPlanGenerator::create(Stmt* stmt, unique_ptr<LogicalOperator>& logical_operator) {
    RC rc = RC::SUCCESS;
    switch (stmt->type()) {
        case StmtType::CALC: {
            CalcStmt* calc_stmt = static_cast<CalcStmt*>(stmt);
            rc = create_plan(calc_stmt, logical_operator);
        } break;

        case StmtType::SELECT: {
            SelectStmt* select_stmt = static_cast<SelectStmt*>(stmt);
            rc = create_plan(select_stmt, logical_operator);
        } break;

        case StmtType::INSERT: {
            InsertStmt* insert_stmt = static_cast<InsertStmt*>(stmt);
            rc = create_plan(insert_stmt, logical_operator);
        } break;

        case StmtType::UPDATE: {
            UpdateStmt* update_stmt = static_cast<UpdateStmt*>(stmt);
            rc = create_plan(update_stmt, logical_operator);
        } break;

        case StmtType::DELETE: {
            DeleteStmt* delete_stmt = static_cast<DeleteStmt*>(stmt);
            rc = create_plan(delete_stmt, logical_operator);
        } break;

        case StmtType::EXPLAIN: {
            ExplainStmt* explain_stmt = static_cast<ExplainStmt*>(stmt);
            rc = create_plan(explain_stmt, logical_operator);
        } break;
        default: {
            rc = RC::UNIMPLENMENT;
        }
    }
    return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt* calc_stmt, std::unique_ptr<LogicalOperator>& logical_operator) {
    logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
    return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(SelectStmt* select_stmt, unique_ptr<LogicalOperator>& logical_operator) {
    unique_ptr<LogicalOperator> table_oper(nullptr);

    const std::vector<Table*>& tables = select_stmt->tables();
    std::unordered_map<std::string, Table*> table_map = select_stmt->table_map();
    const std::vector<Field>& all_fields = select_stmt->query_fields();
    for (Table* table : tables) {
        std::vector<Field> fields;
        for (const Field& field : all_fields) {
            if (0 == strcmp(field.table_name(), table->name())) {
                fields.push_back(field);
            }
        }

        unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, true /*readonly*/));
        if (table_oper == nullptr) {
            table_oper = std::move(table_get_oper);
        }
        else {
            JoinLogicalOperator* join_oper = new JoinLogicalOperator;
            join_oper->add_child(std::move(table_oper));
            join_oper->add_child(std::move(table_get_oper));
            // 处理inner join中的on条件
            FilterStmt* filter_stmt = select_stmt->inner_join_filter_stmt();
            std::vector<unique_ptr<Expression>> cmp_exprs;
            const std::vector<FilterUnit*>& filter_units = filter_stmt->filter_units();
            for (const FilterUnit* filter_unit : filter_units) {
                const FilterObj& filter_obj_left = filter_unit->left();
                const FilterObj& filter_obj_right = filter_unit->right();

                // 只收集on后的表明相同的条件
                if (filter_obj_left.is_attr && filter_obj_right.is_attr) {
                    if (!((table->name() == filter_obj_left.field.table_name() &&
                           filter_obj_right.field.table_name() == tables[0]->name()) ||
                          (table->name() == filter_obj_right.field.table_name() &&
                           filter_obj_left.field.table_name() == tables[0]->name()))) {
                        continue;
                    }
                }
                // 表名需要对应上
                if (!(!filter_obj_left.is_attr && !filter_obj_right.is_attr)) {
                    if (!((filter_obj_left.is_attr && filter_obj_left.field.table_name() == table->name()) ||
                          (filter_obj_right.is_attr && filter_obj_right.field.table_name() == table->name()))) {
                        continue;
                    }
                }

                unique_ptr<Expression> left(filter_obj_left.is_attr ?
                                                static_cast<Expression*>(new FieldExpr(filter_obj_left.field)) :
                                                static_cast<Expression*>(new ValueExpr(filter_obj_left.value)));

                unique_ptr<Expression> right(filter_obj_right.is_attr ?
                                                 static_cast<Expression*>(new FieldExpr(filter_obj_right.field)) :
                                                 static_cast<Expression*>(new ValueExpr(filter_obj_right.value)));

                ComparisonExpr* cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
                cmp_exprs.emplace_back(cmp_expr);
            }
            if (!cmp_exprs.empty()) {
                join_oper->set_predicates(std::move(cmp_exprs));
            }
            table_oper = unique_ptr<LogicalOperator>(join_oper);
        }
    }

    unique_ptr<LogicalOperator> predicate_oper;
    RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
        return rc;
    }

    unique_ptr<LogicalOperator> project_oper(new ProjectLogicalOperator(all_fields));
    if (predicate_oper) {
        if (table_oper) {
            predicate_oper->add_child(std::move(table_oper));
        }
        project_oper->add_child(std::move(predicate_oper));
    }
    else {
        if (table_oper) {
            project_oper->add_child(std::move(table_oper));
        }
    }
    // 处理aggregate
    if (!select_stmt->aggr_nodes().empty()) {
        std::vector<AttrType> attr_types;
        std::vector<AggrType> aggr_types;
        std::vector<std::string> field_names;
        for (AggrNode aggrNode : select_stmt->aggr_nodes()) {
            aggr_types.push_back(aggrNode.type);
            // if (aggrNode.attribute == "*") {
            //     field_names.push_back((*tables[0]->table_meta().field_metas())[0].name());
            // }
            // else {
            //     field_names.push_back(aggrNode.attribute);
            // }
            field_names.push_back(aggrNode.attribute);

            std::vector<FieldMeta> field_metas = *table_map[aggrNode.relation]->table_meta().field_metas();
            int flag = 0;
            for (FieldMeta field_meta : field_metas) {
                if (field_meta.name() == aggrNode.attribute) {
                    attr_types.push_back(field_meta.type());
                    flag = 1;
                    break;
                }
                if (aggrNode.attribute == "*") {
                    attr_types.push_back(AttrType::INTS);
                    flag = 1;
                    break;
                }
            }
            if (!flag)
                return RC::SCHEMA_FIELD_MISSING;
        }

        unique_ptr<LogicalOperator> aggr_oper(
            new AggrLogicalOperator(string(tables[0]->name()), field_names, attr_types, aggr_types));
        aggr_oper->add_child(std::move(project_oper));
        logical_operator.swap(aggr_oper);
        return RC::SUCCESS;
    }
    // 处理orderBy
    if (!select_stmt->orderBySqlNodes().empty()) {
        std::vector<std::string> table_names;
        std::vector<std::string> field_names;
        std::vector<OrderPolicy> order_policys;
        for (OrderBySqlNode orderby_node : select_stmt->orderBySqlNodes()) {
            table_names.push_back(orderby_node.relation);
            field_names.push_back(orderby_node.attribute);
            order_policys.push_back(orderby_node.orderPolicy);
        }

        unique_ptr<LogicalOperator> orderby_oper(new OrderByLogicalOperator(table_names, field_names, order_policys));
        orderby_oper->add_child(std::move(project_oper));
        logical_operator.swap(orderby_oper);
        return RC::SUCCESS;
    }
    logical_operator.swap(project_oper);
    return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt* filter_stmt, unique_ptr<LogicalOperator>& logical_operator) {
    std::vector<unique_ptr<Expression>> cmp_exprs;
    const std::vector<FilterUnit*>& filter_units = filter_stmt->filter_units();
    for (const FilterUnit* filter_unit : filter_units) {
        const FilterObj& filter_obj_left = filter_unit->left();
        const FilterObj& filter_obj_right = filter_unit->right();

        unique_ptr<Expression> left(filter_obj_left.is_attr ?
                                        static_cast<Expression*>(new FieldExpr(filter_obj_left.field)) :
                                        static_cast<Expression*>(new ValueExpr(filter_obj_left.value)));

        if (filter_obj_right.is_subselect == 1) {
            unique_ptr<Expression> right(static_cast<Expression*>(new ValueListExpr(filter_obj_right.in_values)));

            InComparisonExpr* cmp_expr = new InComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
            cmp_exprs.emplace_back(cmp_expr);
        }
        else if (filter_obj_right.is_subselect == 2) {
            unique_ptr<LogicalOperator> logical_operator;
            unique_ptr<PhysicalOperator> physical_operator;
            RC rc = create_plan(filter_obj_right.select_stmt, logical_operator);

            if (rc != RC::SUCCESS) {
                return rc;
            }
            PhysicalPlanGenerator phy;
            rc = phy.create(*logical_operator.get(), physical_operator);
            if (rc != RC::SUCCESS) {
                return rc;
            }
            SubSelectExpr* expr = new SubSelectExpr(std::move(physical_operator));
            rc = expr->init(filter_unit->comp());
            if (rc != RC::SUCCESS) {
                return rc;
            }
            unique_ptr<Expression> right(static_cast<Expression*>(expr));
            InComparisonExpr* cmp_expr = new InComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));

            cmp_exprs.emplace_back(cmp_expr);
        }
        else {
            unique_ptr<Expression> right(filter_obj_right.is_attr ?
                                             static_cast<Expression*>(new FieldExpr(filter_obj_right.field)) :
                                             static_cast<Expression*>(new ValueExpr(filter_obj_right.value)));

            ComparisonExpr* cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
            cmp_exprs.emplace_back(cmp_expr);
        }
    }

    unique_ptr<PredicateLogicalOperator> predicate_oper;
    if (!cmp_exprs.empty()) {
        unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
        predicate_oper =
            unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    }

    logical_operator = std::move(predicate_oper);
    return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(InsertStmt* insert_stmt, unique_ptr<LogicalOperator>& logical_operator) {
    Table* table = insert_stmt->table();
    vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

    InsertLogicalOperator* insert_operator = new InsertLogicalOperator(table, values);
    logical_operator.reset(insert_operator);
    return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt* update_stmt, unique_ptr<LogicalOperator>& logical_operator) {
    Table* table = update_stmt->table();
    std::vector<std::string> field_names;
    for (Field field : update_stmt->fields()) {
        field_names.push_back(field.field_name());
    }
    std::vector<UpdateValueLogicalOperator> opers;
    for (UpdateValueStmt stmt : update_stmt->values()) {
        UpdateValueLogicalOperator oper;
        if (stmt.isSubQuery) {
            unique_ptr<LogicalOperator> sub_logical_operator;
            RC rc = create_plan(stmt.select, sub_logical_operator);
            if (rc != RC::SUCCESS) {
                return rc;
            }
            oper.isSubQuery = 1;
            oper.select = std::move(sub_logical_operator);
            opers.push_back(std::move(oper));
        }
        else {
            oper.isSubQuery = 0;
            oper.value = stmt.value;
            opers.push_back(std::move(oper));
        }
    }

    unique_ptr<LogicalOperator> update_operator(new UpdateLogicalOperator(table, field_names, std::move(opers)));
    // 添加子节点
    FilterStmt* filter_stmt = update_stmt->filter_stmt();
    std::vector<Field> fields;
    for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
        const FieldMeta* field_meta = table->table_meta().field(i);
        fields.push_back(Field(table, field_meta));
    }
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

    unique_ptr<LogicalOperator> predicate_oper;
    RC rc;
    if (filter_stmt != nullptr) {
        rc = create_plan(filter_stmt, predicate_oper);
    }
    if (predicate_oper) {
        predicate_oper->add_child(std::move(table_get_oper));
        update_operator->add_child(std::move(predicate_oper));
    }
    else {
        update_operator->add_child(std::move(table_get_oper));
    }

    logical_operator = std::move(update_operator);
    return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt* delete_stmt, unique_ptr<LogicalOperator>& logical_operator) {
    Table* table = delete_stmt->table();
    FilterStmt* filter_stmt = delete_stmt->filter_stmt();
    std::vector<Field> fields;
    for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
        const FieldMeta* field_meta = table->table_meta().field(i);
        fields.push_back(Field(table, field_meta));
    }
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

    unique_ptr<LogicalOperator> predicate_oper;
    RC rc = create_plan(filter_stmt, predicate_oper);
    if (rc != RC::SUCCESS) {
        return rc;
    }

    unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

    if (predicate_oper) {
        predicate_oper->add_child(std::move(table_get_oper));
        delete_oper->add_child(std::move(predicate_oper));
    }
    else {
        delete_oper->add_child(std::move(table_get_oper));
    }

    logical_operator = std::move(delete_oper);
    return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt* explain_stmt, unique_ptr<LogicalOperator>& logical_operator) {
    Stmt* child_stmt = explain_stmt->child();
    unique_ptr<LogicalOperator> child_oper;
    RC rc = create(child_stmt, child_oper);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
        return rc;
    }

    logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
    logical_operator->add_child(std::move(child_oper));
    return rc;
}
