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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class Table;
class FilterStmt;
class SelectStmt;

/**
 * @brief 存储Update
 * @ingroup SQLParser 
*/
struct UpdateValueStmt
{
    int isSubQuery;
    Value value;
    SelectStmt* select;
};

/**
 * @brief 更新语句
 * @details 在miniob中只需要实现单字段的更新，stmt中需要存储两个值，一是字段名，二是值
 * @ingroup Statement
 */
class UpdateStmt : public Stmt {
  public:
    UpdateStmt() = default;
    UpdateStmt(Table* table, std::vector<Field> field, std::vector<UpdateValueStmt> value);
    UpdateStmt(Table* table, std::vector<Field> field, std::vector<UpdateValueStmt> value, FilterStmt* filter_stmt);

    StmtType type() const override {
        return StmtType::UPDATE;
    }

  public:
    static RC create(Db* db, const UpdateSqlNode& update_sql, Stmt*& stmt);

  public:
    Table* table() const {
        return table_;
    }
    std::vector<UpdateValueStmt> values() const {
        return values_;
    }
    std::vector<Field> fields() const {
        return fields_;
    }
    FilterStmt* filter_stmt() const {
        return filter_stmt_;
    }

  private:
    Table* table_ = nullptr;
    std::vector<UpdateValueStmt> values_;
    std::vector<Field> fields_;
    FilterStmt* filter_stmt_ = nullptr;
};
