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
// Created by Wangyunlai on 2022/12/07
//

#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/stmt/filter_stmt.h"
/**
 * @brief 连接算子
 * @ingroup LogicalOperator
 * @details 连接算子，用于连接两个表。对应的物理算子或者实现，可能有NestedLoopJoin，HashJoin等等。
 */
class JoinLogicalOperator : public LogicalOperator 
{
public:
  JoinLogicalOperator() = default;
  virtual ~JoinLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::JOIN;
  }

  void set_predicates(std::vector<std::unique_ptr<Expression>> &&exprs) {
    predicates_ = std::move(exprs);
  }

  std::vector<std::unique_ptr<Expression>> predicates(){
    return std::move(predicates_);
  }

private:
  std::vector<std::unique_ptr<Expression>> predicates_;
};
