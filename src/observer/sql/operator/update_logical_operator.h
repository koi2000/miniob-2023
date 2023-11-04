#pragma once
#include <vector>

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"

#include <memory>
struct UpdateValueLogicalOperator {
    int isSubQuery;
    Value value;
    std::unique_ptr<LogicalOperator> select;
};

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator {
  public:
    UpdateLogicalOperator(Table* table, std::vector<std::string> fields, std::vector<UpdateValueLogicalOperator> values);
    virtual ~UpdateLogicalOperator() = default;

    LogicalOperatorType type() const override {
        return LogicalOperatorType::UPDATE;
    }

    Table* table() const {
        return table_;
    }
    std::vector<std::string> fields() const {
        return fields_;
    }
    std::vector<UpdateValueLogicalOperator> values() {
        return std::move(values_);
    }

  private:
    Table* table_ = nullptr;
    std::vector<std::string> fields_;
    std::vector<UpdateValueLogicalOperator> values_;
};