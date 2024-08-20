#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/orderby_stmt.h"
#include "storage/field/field.h"

/**
 * @brief 逻辑算子
 * @ingroup LogicalOperator
 */
class OrderByLogicalOperator : public LogicalOperator
{
public:
  OrderByLogicalOperator(
      std::vector<std::unique_ptr<OrderByUnit>> &&orderby_units, std::vector<std::unique_ptr<Expression>> &&exprs);

  virtual ~OrderByLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::ORDERBY; }

  std::vector<std::unique_ptr<OrderByUnit>> &orderby_units() { return orderby_units_; }

  std::vector<std::unique_ptr<Expression>> &exprs() { return exprs_; }

private:
  std::vector<std::unique_ptr<OrderByUnit>> orderby_units_;
  /// 在 create order by stmt 之前提取 select clause 后的 field_expr (非a gg_expr 中的)和 agg_expr
  std::vector<std::unique_ptr<Expression>> exprs_;
};