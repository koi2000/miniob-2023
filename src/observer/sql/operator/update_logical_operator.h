#pragma once
#include <vector>

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator {
  public:
    UpdateLogicalOperator(Table* table, std::string field, Value value);
    virtual ~UpdateLogicalOperator() = default;

    LogicalOperatorType type() const override {
        return LogicalOperatorType::UPDATE;
    }

    Table* table() const {
        return table_;
    }
    std::string field() const {
        return field_;
    }
    Value value() const {
        return value_;
    }

  private:
    Table* table_ = nullptr;
    std::string field_;
    Value value_;
};