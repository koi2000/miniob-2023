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
// Created by WangYunlai on 2022/12/30.
//

#include "sql/operator/aggregate_physical_operator.h"
#include "util/date.h"
RC AggrPhysicalOperator::open(Trx* trx) {
    if (children_.empty()) {
        return RC::SUCCESS;
    }
    visited = 0;
    count = 0;
    std::unique_ptr<PhysicalOperator>& child = children_[0];
    RC rc = child->open(trx);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to open child operator: %s", strrc(rc));
        return rc;
    }
    return RC::SUCCESS;
}

Value AggrPhysicalOperator::getAggrValue(std::vector<Value>& values,
                                         std::string fieldName,
                                         AttrType attr_type,
                                         AggrType type) {
    Value result;
    if (type == COUNTS) {
        result.set_int(values.size());
        return result;
    }
    if (values.empty()) {
        result.set_string("NULL");
        return result;
    }

    switch (type) {
        case MAXS: {
            if (attr_type == INTS || attr_type == FLOATS || attr_type == DATES) {
                result.set_int(0);
            }
            else if (attr_type == CHARS) {
                result.set_string(std::string("").c_str());
            }
            if (!values.empty()) {
                if (attr_type == INTS || attr_type == FLOATS || attr_type == DATES) {
                    result.set_int(values[0].get_int());
                }
                else if (attr_type == CHARS) {
                    result.set_string(values[0].get_string().c_str());
                }
            }
            break;
        }
        case MINS: {
            if (attr_type == INTS || attr_type == FLOATS || attr_type == DATES) {
                result.set_int(0);
            }
            else if (attr_type == CHARS) {
                result.set_string(std::string("").c_str());
            }
            if (!values.empty()) {
                if (attr_type == INTS || attr_type == FLOATS || attr_type == DATES) {
                    result.set_int(values[0].get_int());
                }
                else if (attr_type == CHARS) {
                    result.set_string(values[0].get_string().c_str());
                }
            }
            break;
        }
        case AVGS: {
            result.set_int(0);
            break;
        }
        case SUMS: {
            result.set_int(0);
            break;
        }
        default: break;
    }
    if (type == MAXS || type == MINS) {
        for (int i = 0; i < values.size(); i++) {
            Value val = values[i];
            if (type == MAXS) {
                if (val.compare(result) > 0) {
                    if (attr_type == INTS || attr_type == DATES) {
                        result.set_int(val.get_int());
                    }
                    else if (attr_type == FLOATS) {
                        result.set_float(val.get_float());
                    }
                    else {
                        result.set_string(val.get_string().c_str());
                    }
                }
            }
            else {
                if (val.compare(result) < 0) {
                    if (attr_type == INTS || attr_type == DATES) {
                        result.set_int(val.get_int());
                    }
                    else if (attr_type == FLOATS) {
                        result.set_float(val.get_float());
                    }
                    else {
                        result.set_string(val.get_string().c_str());
                    }
                }
            }
        }
    }
    else {
        for (int i = 0; i < values.size(); i++) {
            Value val = values[i];
            if (attr_type == INTS) {
                result.set_int(result.get_int() + val.get_int());
            }
            else {
                result.set_float(result.get_float() + val.get_float());
            }
        }
    }
    if (type == AVGS) {
        result.set_float(result.get_float() / values.size());
    }
    return result;
}

RC AggrPhysicalOperator::next() {
    if (visited) {
        return RC::RECORD_EOF;
    }

    RC rc = RC::SUCCESS;
    if (children_.empty()) {
        return RC::RECORD_EOF;
    }
    PhysicalOperator* child = children_[0].get();
    std::vector<std::vector<Value>> values_list(aggrTypes_.size());
    while (RC::SUCCESS == (rc = child->next())) {
        Tuple* tuple = child->current_tuple();
        count++;
        // 枚举所有的AggrType/字段
        for (int i = 0; i < aggrTypes_.size(); i++) {
            Value val;
            TupleCellSpec spec = TupleCellSpec(table_name_.c_str(), field_names_[i].c_str());
            tuple->find_cell(spec, val);
            // null字段不参与聚合操作
            if (val.isNull()) {
                continue;
            }
            values_list[i].push_back(val);
        }
    }
    // 枚举所有的AggrType/字段
    for (int i = 0; i < aggrTypes_.size(); i++) {
        if (field_names_[i] == "*" && aggrTypes_[i] == COUNTS) {
            Value val;
            val.set_int(count);
            results.push_back(val);
            continue;
        }else if(field_names_[i] == "*" && aggrTypes_[i] != COUNTS){
            return RC::SCHEMA_DB_NOT_EXIST;
        }
        results.push_back(getAggrValue(values_list[i], field_names_[i], field_types_[i], aggrTypes_[i]));
    }
    return RC::SUCCESS;
}

Tuple* AggrPhysicalOperator::current_tuple() {
    visited = 1;
    std::vector<Value> cells;
    for (int i = 0; i < results.size(); i++) {
        Value value = results[i];
        // if (field_names_[i] == "*" && aggrTypes_[i] == COUNTS) {
        //     value.set_int(count);
        // }
        if (field_types_[i] == DATES && aggrTypes_[i] != COUNTS) {
            std::string res = date_to_string(value.get_int());
            value.set_string(res.c_str());
        }
        cells.push_back(value);
    }
    tuple_.set_cells(cells);
    return &tuple_;
}