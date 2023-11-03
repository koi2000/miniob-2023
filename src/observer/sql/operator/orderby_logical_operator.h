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
// Created by Wangyunlai on 2022/12/07.
//

#pragma once

#include <memory>
#include <vector>

#include "sql/operator/logical_operator.h"

/**
 * @brief OrderBy对应逻辑算子
 * @details child为TableGet，获取经过Filter之后的所有数据，然后进行sort排序
 */
class OrderByLogicalOperator : public LogicalOperator {
  public:
    OrderByLogicalOperator(std::vector<std::string> table_names,
                           std::vector<std::string> field_names,
                           std::vector<OrderPolicy> order_policys)
        : table_names_(table_names), field_names_(field_names), order_policys_(order_policys) {}

    virtual ~OrderByLogicalOperator() = default;

    LogicalOperatorType type() const override {
        return LogicalOperatorType::ORDERBY;
    }

    std::vector<std::string> table_names() {
        return table_names_;
    }

    std::vector<std::string> field_names() {
        return field_names_;
    }

    std::vector<OrderPolicy> order_policys() {
        return order_policys_;
    }

  private:
    std::vector<std::string> table_names_;
    std::vector<std::string> field_names_;
    std::vector<OrderPolicy> order_policys_;
};
