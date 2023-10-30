
#pragma
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"
#include <vector>

class UpdateStmt;

/**
 * @brief 更新物理算子
 * @ingroup PhysicalOperator
 */

class UpdatePhysicalOperator : public PhysicalOperator {
  public:
    UpdatePhysicalOperator(Table* table, std::vector<std::string> field_names, std::vector<Value> values);
    virtual ~UpdatePhysicalOperator() = default;

    PhysicalOperatorType type() const override {
        return PhysicalOperatorType::UPDATE;
    }

    RC open(Trx* trx) override;
    RC next() override;
    RC close() override;

    Tuple* current_tuple() override {
        return nullptr;
    }

  private:
    Table* table_ = nullptr;
    Trx* trx_ = nullptr;
    std::vector<std::string> field_names_;
    std::vector<Value> values_;
};