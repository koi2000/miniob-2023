

#include "sql/operator/update_physical_operator.h"
#include "common/log/log.h"
#include "sql/stmt/update_stmt.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

UpdatePhysicalOperator::UpdatePhysicalOperator(Table* table, std::string field_name, Value value)
    : table_(table), field_name_(field_name), value_(std::move(value)) {}

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
        rc = trx_->update_record(table_, field_name_, &value_, record);
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
