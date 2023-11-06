#include "sql/expr/sub_expression.h"
#include "storage/trx/vacuous_trx.h"

InComparisonExpr::InComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right)) {}

InComparisonExpr::~InComparisonExpr() {}

RC InComparisonExpr::get_value(const Tuple& tuple, Value& value) const {
    Value left_value;

    RC rc = left_->get_value(tuple, left_value);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
        return rc;
    }
    std::vector<Value> values;
    if (right_->type() == ExprType::VALUELIST) {
        ValueListExpr* val = dynamic_cast<ValueListExpr*>(right_.get());
        values = val->get_values();
    }
    else if (right_->type() == ExprType::SUBSELECT) {
        SubSelectExpr* val = dynamic_cast<SubSelectExpr*>(right_.get());
        VacuousTrxKit kit;
        values = val->get_values(kit.create_trx(1));
    }

    // rc = right_->get_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
        return rc;
    }

    bool bool_value = false;
    rc = compare_value(left_value, values, bool_value);
    if (rc == RC::SUCCESS) {
        value.set_boolean(bool_value);
    }
    return rc;
}

RC InComparisonExpr::try_get_value(Value& value) const {
    return RC::SUCCESS;
}

RC InComparisonExpr::compare_value(const Value& left, std::vector<Value>& right, bool& value) const {
    value = false;
    if (comp_ == EXISTS) {
        if (!right.empty()) {
            value = true;
            return RC::SUCCESS;
        }
    }
    else if (comp_ == NOT_EXISTS) {
        if (right.empty()) {
            value = true;
            return RC::SUCCESS;
        }
    }

    for (Value& val : right) {
        if (left.attr_type() == INTS) {
            try_to_cast(INTS, true, val);
            if (val.get_int() == left.get_int()) {
                value = true;
                break;
            }
        }
        if (left.attr_type() == FLOATS) {
            try_to_cast(FLOATS, true, val);
            if (val.get_float() == left.get_float()) {
                value = true;
                break;
            }
        }
        if (left.attr_type() == CHARS) {
            try_to_cast(CHARS, true, val);
            if (val.get_string() == left.get_string()) {
                value = true;
                break;
            }
        }
        if (left.attr_type() == DATES) {
            try_to_cast(DATES, true, val);
            if (val.get_int() == left.get_int()) {
                value = true;
                break;
            }
        }
    }
    if (comp_ == NOT_IN) {
        if (!value) {
            value = true;
        }
        else {
            value = false;
        }
    }
    return RC::SUCCESS;
}

RC ValueListExpr::get_value(const Tuple& tuple, Value& value) const {
    return RC::SUCCESS;
}

RC SubSelectExpr::get_value(const Tuple& tuple, Value& value) const {
    return RC::SUCCESS;
}
