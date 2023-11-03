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

class OrderByPhysicalOperator : public PhysicalOperator {
  public:
    OrderByPhysicalOperator(std::vector<std::string> table_names,
                           std::vector<std::string> field_names,
                           std::vector<OrderPolicy> order_policys)
        : table_names_(table_names), field_names_(field_names), order_policys_(order_policys) {}

    virtual ~OrderByPhysicalOperator() = default;

    PhysicalOperatorType type() const override {
        return PhysicalOperatorType::ORDERBY;
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

  private:
    std::vector<std::string> table_names_;
    std::vector<std::string> field_names_;
    std::vector<OrderPolicy> order_policys_;
    std::vector<Tuple*> tuples;
    Tuple* current_tuple_;
    int index = 0;
};
