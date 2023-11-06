

#include "sql/operator/update_physical_operator.h"
#include "common/log/log.h"
#include "sql/stmt/update_stmt.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

UpdatePhysicalOperator::UpdatePhysicalOperator(Table* table,
                                               std::vector<std::string> field_names,
                                               std::vector<UpdateValuePhysicalOperator> values)
    : table_(table), field_names_(field_names), values_(std::move(values)) {}

RC UpdatePhysicalOperator::open(Trx* trx) {
    if (children_.empty()) {
        return RC::SUCCESS;
    }

    std::unique_ptr<PhysicalOperator>& child = children_[0];
    RC rc = child->open(trx);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to open child operator: %s", strrc(rc));
        return rc;
    }
    trx_ = trx;
    return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next() {
    RC rc = RC::SUCCESS;
    if (children_.empty()) {
        return RC::RECORD_EOF;
    }
    PhysicalOperator* child = children_[0].get();
    while (RC::SUCCESS == (rc = child->next())) {
        Tuple* tuple = child->current_tuple();
        if (tuple == nullptr) {
            LOG_WARN("failed to get current record: %s", strrc(rc));
        }
        RowTuple* row_tuple = static_cast<RowTuple*>(tuple);
        Record& record = row_tuple->record();
        std::vector<Value> values;
        for (size_t i = 0; i < values_.size(); i++) {
            if (values_[i].isSubQuery) {
                RC rc = values_[i].select->open(trx_);
                int count = 0;
                while (RC::SUCCESS == (rc = values_[i].select->next())) {
                    Tuple* tuple = values_[i].select->current_tuple();
                    std::string res = tuple->to_string();
                    count++;
                    Value val;
                    val.set_string(res.c_str());
                    values.push_back(val);
                }
                if (count >= 2) {
                    return RC::FILE_NOT_EXIST;
                }
                if (count == 0) {
                    Value val;
                    val.set_isNull(true);
                    values.push_back(val);
                }
            }
            else {
                values.push_back(values_[i].value);
            }
        }

        rc = trx_->update_record(table_, field_names_, values, record);
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to update record: %s", strrc(rc));
            return rc;
        }
    }
    return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close() {
    if (!children_.empty()) {
        children_[0]->close();
    }
    return RC::SUCCESS;
}
