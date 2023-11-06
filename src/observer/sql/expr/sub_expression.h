#include "sql/expr/expression.h"
#include "sql/operator/physical_operator.h"
#include "storage/trx/vacuous_trx.h"
#include "util/utils.h"
#include <memory>
/**
 * @brief In/Exists比较表达式
 * @ingroup Expression
 */
class InComparisonExpr : public Expression {
  public:
    InComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
    virtual ~InComparisonExpr();

    ExprType type() const override {
        return ExprType::INCOMPARISON;
    }

    RC get_value(const Tuple& tuple, Value& value) const override;

    AttrType value_type() const override {
        return BOOLEANS;
    }

    CompOp comp() const {
        return comp_;
    }

    std::unique_ptr<Expression>& left() {
        return left_;
    }
    std::unique_ptr<Expression>& right() {
        return right_;
    }

    /**
     * 尝试在没有tuple的情况下获取当前表达式的值
     * 在优化的时候，可能会使用到
     */
    RC try_get_value(Value& value) const override;

    RC compare_value(const Value& left, std::vector<Value>& right, bool& value) const;

  private:
    CompOp comp_;
    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
};

/**
 * @brief 子查询列表表达式
 * @ingroup Expression
 */
class SubSelectExpr : public Expression {
  public:
    SubSelectExpr() = default;
    SubSelectExpr(std::unique_ptr<PhysicalOperator> physical_operator)
        : select_physical_operator(std::move(physical_operator)) {}

    RC init(CompOp comp_) {
        VacuousTrxKit kit;
        RC rc = select_physical_operator->open(kit.create_trx(1));
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to open child operator: %s", strrc(rc));
        }
        std::vector<Tuple*> tuples;
        while (RC::SUCCESS == (rc = select_physical_operator->next())) {
            Tuple* tuple = select_physical_operator->current_tuple();
            // tuples.push_back(tuple->clone());
            if (tuple->cell_num() > 1) {
                rc = RC::SUB_SELECT_ERROR;
                return rc;
            }

            Value value;
            value.set_string(tuple->to_string().c_str());
            values.push_back(value);
        }
        if (values.empty()) {
            Value value;
            value.set_isNull(true);
            values.push_back(value);
        }
        if (!(comp_ == IN || comp_ == NOT_IN || comp_ == EXISTS || comp_ == NOT_EXISTS)) {
            if (values.size() > 1) {
                rc = RC::SUB_SELECT_ERROR;
                return rc;
            }
        }

        visited = 1;
        return RC::SUCCESS;
    }

    virtual ~SubSelectExpr() = default;

    RC get_values(Trx* trx, std::vector<Value>& vals) {
        RC rc = RC::SUCCESS;
        if (visited) {
            vals = values;
            return rc;
        }
        else {
            RC rc = select_physical_operator->open(trx);
            if (rc != RC::SUCCESS) {
                LOG_WARN("failed to open child operator: %s", strrc(rc));
            }
            std::vector<Tuple*> tuples;
            while (RC::SUCCESS == (rc = select_physical_operator->next())) {
                Tuple* tuple = select_physical_operator->current_tuple();
                // tuples.push_back(tuple->clone());
                if (tuple->cell_num() >= 1) {
                    rc = RC::SUB_SELECT_ERROR;
                    return rc;
                }

                Value value;
                value.set_string(tuple->to_string().c_str());
                values.push_back(value);
            }
            if (values.empty()) {
                Value value;
                value.set_isNull(true);
                values.push_back(value);
            }
            visited = 1;
        }
        return rc;
    }

    AttrType value_type() const override {
        return AttrType::UNDEFINED;
    }

    ExprType type() const override {
        return ExprType::SUBSELECT;
    }

    RC get_value(const Tuple& tuple, Value& value) const override;

  private:
    std::unique_ptr<PhysicalOperator> select_physical_operator;
    int visited = 0;
    std::vector<Value> values;
};

/**
 * @brief 常量列表表达式
 * @ingroup Expression
 */
class ValueListExpr : public Expression {
  public:
    ValueListExpr() = default;
    explicit ValueListExpr(const std::vector<Value>& values) : values_(values) {}

    virtual ~ValueListExpr() = default;

    RC get_value(const Tuple& tuple, Value& value) const override;

    ExprType type() const override {
        return ExprType::VALUELIST;
    }

    AttrType value_type() const override {
        return values_[0].attr_type();
    }

    const std::vector<Value>& get_values() const {
        return values_;
    }

  private:
    std::vector<Value> values_;
};