/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2022/12/30.
//

#include "sql/operator/orderby_physical_operator.h"
#include "util/date.h"
#include <algorithm>

bool customCompare(const Tuple* a,
                   const Tuple* b,
                   std::vector<std::string> table_names,
                   std::vector<std::string> field_names,
                   std::vector<OrderPolicy> order_policys) {
    for (int i = 0; i < order_policys.size(); i++) {
        OrderPolicy order_policy = order_policys[i];
        if (order_policy == ORDER_ASC) {
            TupleCellSpec tupleCellSpec = TupleCellSpec(table_names[i].c_str(), field_names[i].c_str());
            Value val1;
            Value val2;
            a->find_cell(tupleCellSpec, val1);
            b->find_cell(tupleCellSpec, val2);
            if (val1.compare(val2) > 0) {
                return true;
            }
            else if (val1.compare(val2) < 0) {
                return false;
            }
        }
        else if (order_policy == ORDER_DESC) {
            TupleCellSpec tupleCellSpec = TupleCellSpec(table_names[i].c_str(), field_names[i].c_str());
            Value val1;
            Value val2;
            a->find_cell(tupleCellSpec, val1);
            b->find_cell(tupleCellSpec, val2);
            if (val1.compare(val2) < 0) {
                return true;
            }
            else if (val1.compare(val2) > 0) {
                return false;
            }
        }
    }
    return false;  // 默认情况下，不进行交换
}

// open截断读取出全部数据，并开始排序
RC OrderByPhysicalOperator::open(Trx* trx) {
    if (children_.empty()) {
        return RC::SUCCESS;
    }
    std::unique_ptr<PhysicalOperator>& child = children_[0];
    RC rc = child->open(trx);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to open child operator: %s", strrc(rc));
        return rc;
    }
    // std::vector<Tuple*> tuples;
    while (RC::SUCCESS == (rc = child->next())) {
        Tuple* tuple = child->current_tuple();
        // ProjectTuple* derivedPtr1 = dynamic_cast<ProjectTuple*>(tuple);
        // if (derivedPtr1 != nullptr) {
        //     tuples.push_back(*derivedPtr1);
        // }
        // else {
        //     RowTuple* derivedPtr2 = dynamic_cast<RowTuple*>(tuple);
        //     if (derivedPtr2 != nullptr) {
        //         tuples.push_back(*derivedPtr2);
        //     }
        //     else {
        //         JoinedTuple* derivedPtr3 = dynamic_cast<JoinedTuple*>(tuple);
        //         if (derivedPtr3 != nullptr) {
        //             tuples.push_back(*derivedPtr3);
        //         }
        //     }
        // }

        tuples.push_back(tuple->clone());
    }
    // 如何排序？
    std::sort(tuples.begin(), tuples.end(),
              [&](Tuple* a, Tuple* b) { return customCompare(a, b, table_names_, field_names_, order_policys_); });
    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next() {
    if (index == tuples.size()) {
        return RC::RECORD_EOF;
    }

    RC rc = RC::SUCCESS;
    if (children_.empty()) {
        return RC::RECORD_EOF;
    }
    current_tuple_ = tuples[index];
    index++;
    return RC::SUCCESS;
}

Tuple* OrderByPhysicalOperator::current_tuple() {
    return current_tuple_;
}