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
 * @brief 聚合函数对应逻辑算子
 * @details child为TableGet，获取经过Filter之后的所有数据，需要记录对哪些字段进行哪些操作
 */
class AggrLogicalOperator : public LogicalOperator {
  public:
    AggrLogicalOperator(std::string table_name,
                        
                        std::vector<std::string> field_names,
                        std::vector<AttrType> field_types,
                        std::vector<AggrType> aggrTypes)
        : table_name_(table_name), aggrTypes_(aggrTypes), field_names_(field_names), field_types_(field_types) {}

    virtual ~AggrLogicalOperator() = default;

    LogicalOperatorType type() const override {
        return LogicalOperatorType::AGGR;
    }

    std::vector<AggrType> aggeTypes() {
        return aggrTypes_;
    }

    std::vector<AttrType> field_types() {
        return field_types_;
    }

    std::vector<std::string> field_names() {
        return field_names_;
    }

    std::string table_name(){
        return table_name_;
    }

  private:
    std::vector<AggrType> aggrTypes_;
    std::vector<std::string> field_names_;
    std::vector<AttrType> field_types_;
    std::string table_name_;
};
