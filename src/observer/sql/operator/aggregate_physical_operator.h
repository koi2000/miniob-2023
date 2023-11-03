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
// Created by WangYunlai on 2022/07/01.
//

#pragma once

#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"

class AggrPhysicalOperator : public PhysicalOperator {
  public:
    AggrPhysicalOperator(std::string table_name,
                         std::vector<AggrType> aggrTypes,
                         std::vector<std::string> field_names,
                         std::vector<AttrType> field_types)
        : table_name_(table_name), aggrTypes_(aggrTypes), field_names_(field_names), field_types_(field_types) {}

    virtual ~AggrPhysicalOperator() = default;

    PhysicalOperatorType type() const override {
        return PhysicalOperatorType::AGGR;
    }

    RC next() override;

    RC open(Trx* trx) override;

    RC close() override {
        if (!children_.empty()) {
            children_[0]->close();
        }
        return RC::SUCCESS;
    }

    Tuple* current_tuple() override;
    Value getAggrValue(std::vector<Value>& tuples, std::string fieldName, AttrType attr_type, AggrType type);

  private:
    std::vector<AggrType> aggrTypes_;
    std::vector<std::string> field_names_;
    std::vector<AttrType> field_types_;
    std::string table_name_;
    ValueListTuple tuple_;
    std::vector<Value> results;
    int visited = 0;
    int count = 0;
};
