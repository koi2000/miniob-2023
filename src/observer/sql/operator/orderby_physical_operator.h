#pragma once

#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/stmt/orderby_stmt.h"
#include <memory>

/**
 * @brief 物理算子
 * @ingroup PhysicalOperator
 */
class OrderByPhysicalOperator : public PhysicalOperator {
  public:
    OrderByPhysicalOperator(std::vector<std::unique_ptr<OrderByUnit>>&& orderby_units,
                            std::vector<std::unique_ptr<Expression>>&& exprs);

    virtual ~OrderByPhysicalOperator() = default;

    PhysicalOperatorType type() const override {
        return PhysicalOperatorType::ORDERBY;
    }

    RC fetch_and_sort_tables();
    RC open(Trx* trx) override;
    RC next() override;
    RC close() override;
    Tuple* current_tuple() override;

  private:
    std::vector<std::unique_ptr<OrderByUnit>> orderby_units_;  // 排序列
    std::vector<std::vector<Value>> values_;
    SplicedTuple tuple_;

    std::vector<int> ordered_idx_;  // 存储从 values_中取 数据的顺序
    std::vector<int>::iterator it_;
};