#include "sql/operator/view_get_logical_operator.h"

ViewGetLogicalOperator::ViewGetLogicalOperator(View *table, const std::vector<Field> &fields, ReadWriteMode mode)
    : table_(table), fields_(fields), mode_(mode)
{}

void ViewGetLogicalOperator::set_predicates(std::vector<std::unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}