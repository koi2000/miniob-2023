
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UNIQUE
        UPDATE
        INNER
        JOIN
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        EQ
        LT
        GT
        LE
        GE
        NE
        LIKE
        NOT
        NULL_T
        IS
        INS
        EXISTSS
        MAX
        MIN
        COUNT
        AVG
        SUM
        ASC
        ORDER
        BY

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                   sql_node;
  ConditionSqlNode *                condition;
  Value *                           value;
  enum CompOp                       comp;
  RelAttrSqlNode *                  rel_attr;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  std::vector<Expression *> *       expression_list;
  std::vector<Value> *              value_list;
  std::vector<ConditionSqlNode> *   condition_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<JoinSqlNode> *        relation_list;
  std::vector<std::pair<std::string,UpdateValueNode>>* update_list;
  std::vector<std::string> *        index_attribute_names;
  std::vector<std::string> *        aggr_attribute_names;
  std::vector<OrderBySqlNode> *     orderby_list;
  enum OrderPolicy                  order_policy;
  OrderBySqlNode*                   order_node;
  char *                            string;
  int                               number;
  float                             floats;
  enum AggrType                     aggr_type;
  AggrNode*                         aggr_node;
  std::vector<AggrNode>*            aggr_list;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <number>              number
%type <comp>                comp_op
%type <rel_attr>            rel_attr
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <condition_list>      where
%type <condition_list>      condition_list
%type <condition_list>      inner_join_conditions
%type <rel_attr_list>       select_attr
%type <relation_list>       rel_list
%type <index_attribute_names>       index_ids
%type <update_list>         update_pair_list
%type <rel_attr_list>       attr_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <aggr_attribute_names>     AGGR_ATTR_LIST
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
%type <aggr_type>           AGGR_TYPE
%type <aggr_node>           AGG_FUNC
%type <aggr_list>           AGG_FUNC_LIST
%type <orderby_list>        order_by
%type <number>              nullable
%type <orderby_list>        order_attr_list
%type <order_policy>        order_policy
%type <order_node>          order_attr


// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID index_ids  RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      // create_index.attribute_name = $7;
      create_index.unique = 0;
      if ($8 != nullptr) {
        create_index.attribute_names.swap(*$8);
      }
      create_index.attribute_names.push_back($7);
      free($3);
      free($5);
      free($7);
    } | CREATE UNIQUE INDEX ID ON ID LBRACE ID index_ids  RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      create_index.unique = 1;
      if ($9 != nullptr) {
        create_index.attribute_names.swap(*$9);
      }
      create_index.attribute_names.push_back($8);
      free($4);
      free($6);
      free($8);
    }
    ;

index_ids:
    /* empty */ {
        $$ = nullptr;
    }
    | COMMA ID index_ids {
        if($3 == nullptr){
            $$ = new std::vector<std::string>();
        } else {
            $$ = $3;
        }
        $$->push_back($2);
        free($2);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->allowNull = $6;
      free($1);
    }
    | ID type nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->allowNull = $3;
      free($1);
    }
    ;

nullable: 
    /**/{
        $$ = 1;
    }
    | NULL_T {
        $$ = 1;
    }
    | NOT NULL_T {
        $$ = 0;
    }

number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$=INTS; }
    | STRING_T { $$=CHARS; }
    | FLOAT_T  { $$=FLOATS; }
    | DATE_T   { $$=DATES; }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE 
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($7 != nullptr) {
        $$->insertion.values.swap(*$7);
      }
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
      free($3);
    }
    ;

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | value value_list {
        if ($2 != nullptr) {
            $$ = $2;
        } else {
            $$ = new std::vector<Value>;
        }
        $$->emplace_back(*$1);
        delete $1;
    }
    | COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |NULL_T {
      $$ = new Value(0);
      $$ -> set_isNull(true);
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET update_pair_list where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;

      if ($4 != nullptr) {
        for (std::pair<std::string,UpdateValueNode>& pair_node : *$4) {
          $$->update.attribute_name.push_back(pair_node.first);
          $$->update.value.push_back(pair_node.second);
        }
      }
    
      if ($5 != nullptr) {
        $$->update.conditions.swap(*$5);
        delete $5;
      }
      free($2);
      free($4);
    }
    ;

update_pair_list:
    /*empty*/ 
    {
        $$ = nullptr;
    }
    | ID EQ LBRACE select_stmt RBRACE update_pair_list {
        if($6 == nullptr) {
            $$ = new std::vector<std::pair<std::string,UpdateValueNode>>();
        } else {
            $$ = $6;
        }
        UpdateValueNode updNode;
        updNode.isSubQuery = 1;
        updNode.select = $4->selection;
        $$->emplace_back($1, updNode);
        free($1);
        free($4);
    }
    | COMMA ID EQ LBRACE select_stmt RBRACE update_pair_list{
        if($7 == nullptr) {
            $$ = new std::vector<std::pair<std::string,UpdateValueNode>>();
        } else {
            $$ = $7;
        }
        UpdateValueNode updNode;
        updNode.isSubQuery = 1;
        updNode.select = $5->selection;
        $$->emplace_back($2, updNode);
        free($2);
        free($5);
    }   
    | ID EQ value update_pair_list {
        if($4 == nullptr) {
            $$ = new std::vector<std::pair<std::string,UpdateValueNode>>();
        } else {
            $$ = $4;
        }
        UpdateValueNode updNode;
        updNode.isSubQuery = 0;
        updNode.value = *$3;
        $$->emplace_back($1,updNode);
        free($1);
        free($3);
    }
    | COMMA ID EQ value update_pair_list {
        if($5 == nullptr){
            $$ = new std::vector<std::pair<std::string,UpdateValueNode>>();
        } else {
            $$ = $5;
        }
        UpdateValueNode updNode;
        updNode.isSubQuery = 0;
        updNode.value = *$4;
        $$->emplace_back($2,updNode);
        free($2);
        free($4);
    }
    ;


select_stmt:        /*  select 语句的语法解析树*/
    SELECT select_attr FROM ID rel_list where order_by
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        std::vector<RelAttrSqlNode> realAttr;
        std::vector<AggrNode> aggrs;
        for (RelAttrSqlNode& relAttrSqlNode : *$2) {
            if(relAttrSqlNode.is_aggr){
                aggrs.push_back(relAttrSqlNode.aggrNode);
            }else{
                realAttr.push_back(relAttrSqlNode);
            }
        }
        $$->selection.attributes.swap(realAttr);
        reverse(aggrs.begin(),aggrs.end());
        $$->selection.aggrs.swap(aggrs);
        delete $2;
      }
      
      $$->selection.relations.push_back($4);
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());

      if ($6 != nullptr) {
        $$->selection.conditions.swap(*$6);
        delete $6;
      }
      if ($7 != nullptr) {
        $$->selection.order_bys.swap(*$7);
        delete $7;
      }
      if ($5 != nullptr){
        for (JoinSqlNode& join_node : *$5) {
          $$->selection.relations.push_back(join_node.table_name);
          for(ConditionSqlNode& condition: join_node.conditions){
              $$->selection.inner_join_conditions.push_back(condition);
          }
        }
      }
      free($4);
    }
    ;

order_by:
    /* empty */ {
        $$ = nullptr;
    }
    | ORDER BY order_attr order_attr_list {
        if ($4 == nullptr){
            $$ = new std::vector<OrderBySqlNode>();
        }else {
            $$ = $4;
        }
        std::reverse($$->begin(),$$->end());
        $$->insert($$->begin(), *$3);
        //$$ -> push_back(*$3);
        free($3);
    }
    ;

order_attr:
    ID order_policy {
        OrderBySqlNode* order_by = new OrderBySqlNode;
        order_by->relation = "";
        order_by->attribute = $1;
        order_by->orderPolicy = $2;
        free($1);
        $$ = order_by;
    }
    | ID DOT ID order_policy {
        OrderBySqlNode* order_by = new OrderBySqlNode;
        order_by->relation = $1;
        order_by->attribute = $3;
        order_by->orderPolicy = $4;
        free($1);
        free($3);
        $$ = order_by;
    }
    ;

order_attr_list:
    /* empty */ {
        $$ = nullptr;
    }
    | order_attr order_attr_list {
        if ($2 == nullptr) {
            $$ = new std::vector<OrderBySqlNode>();
        } else {
            $$ = $2;
        }
        $$ -> push_back(*$1);
    }
    | COMMA order_attr order_attr_list{
        if($3 == nullptr) {
            $$ = new std::vector<OrderBySqlNode>();
        }else {
            $$ = $3;
        }
        $$ -> push_back(*$2);
    }
    ;

order_policy:
    /* empty */ {
        $$ = ORDER_ASC;
    }
    | ASC {
        $$ = ORDER_ASC;
    }
    | DESC {
        $$ = ORDER_DESC;
    }
    ;

AGG_FUNC_LIST:
    /* */ {
        $$ = nullptr;
    }
    | ID AGG_FUNC_LIST {
        if($2 ==nullptr){
            $$ = new std::vector<AggrNode>();
        }else {
            $$ = $2;
        }
        AggrNode aggr;
        aggr.is_attr = 1;
        $$ -> push_back(aggr);
    }
    | AGG_FUNC AGG_FUNC_LIST {
        if($2 ==nullptr){
            $$ = new std::vector<AggrNode>();
        } else {
            $$ = $2;
        }
        
        $$ -> push_back(*$1);
    }
    | COMMA ID AGG_FUNC_LIST{
        if($3 ==nullptr){
            $$ = new std::vector<AggrNode>();
        }else{
            $$ = $3;
        }
        AggrNode aggr;
        aggr.is_attr = 1;
        $$ -> push_back(aggr);
    }
    | COMMA AGG_FUNC AGG_FUNC_LIST{
        if($3 == nullptr) {
            $$ = new std::vector<AggrNode>();
        }else{
            $$ = $3;
        }
        $$ -> push_back(*$2);
        // free($2);
    }
    ;

AGG_FUNC: 
    /**/ {
        $$ = nullptr;
    }
    | AGGR_TYPE LBRACE AGGR_ATTR_LIST RBRACE {
        $$ = new AggrNode();
        $$->relation = "";
        $$->attributes.swap(*$3);
        $$->type = $1;
    }
    ;

AGGR_ATTR_LIST:
    /* */ {
        $$ = new std::vector<std::string>();
    }
    | ID AGGR_ATTR_LIST {
        if($2==nullptr){
            $$ = new std::vector<std::string>();
        }else{
            $$ = $2;
        }
        
        $$->push_back($1);
    }
    | '*' AGGR_ATTR_LIST {
        if($2==nullptr){
            $$ = new std::vector<std::string>();
        }else{
            $$ = $2;
        }
        $$->push_back("*");
    }
    | COMMA ID AGGR_ATTR_LIST {
        if($3 != nullptr) {
            $$ = $3;
        }else{
            $$ = new std::vector<std::string>();
        }
        $$->push_back($2);
        free($2);
    }
    | ID DOT ID AGGR_ATTR_LIST {
        if($4 != nullptr) {
            $$ = $4;
        }else{
            $$ = new std::vector<std::string>();
        }
        std::string str = std::string($1) + "." + std::string($3);
        $$->push_back(str);
        free($1);
        free($3);
    }
    | COMMA ID DOT ID AGGR_ATTR_LIST {
        if ($5 != nullptr) {
            $$ = $5;
        }else {
            $$ = new std::vector<std::string>();
        }
        std::string str = std::string($2) + "." + std::string($4);
        $$->push_back(str);
        free($2);
        free($4);
    }
    ;

AGGR_TYPE:
    MAX     { $$ = MAXS; }
    | MIN   { $$ = MINS; }
    | AVG   { $$ = AVGS; }
    | SUM   { $$ = SUMS; }
    | COUNT { $$ = COUNTS; }
    ;

calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression
    {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($1);
    }
    ;
expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    ;

select_attr:
    /* */ {
      $$ = nullptr;
    }
    |'*' {
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      $$->emplace_back(attr);
    }
    | rel_attr attr_list {
      if ($2 != nullptr) {
        $$ = $2;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }
    ;

rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    | AGG_FUNC {
      $$ = new RelAttrSqlNode;
      $$ -> is_aggr = 1;
      $$ -> aggrNode = *$1;
      free($1);
    }
    ;

attr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA rel_attr attr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }

      $$->emplace_back(*$2);
      delete $2;
    }
    ;

rel_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID rel_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<JoinSqlNode>;
      }

      $$->emplace_back($2, std::vector<ConditionSqlNode>());
      free($2);
    } /*通过这一段可以得到所有的relation*/
    | INNER JOIN ID inner_join_conditions rel_list {
      if ($5 != nullptr) {
        $$ = $5;
      } else {
        $$ = new std::vector<JoinSqlNode>;
      }

      $$->emplace_back($3,*$4);
      free($3);
    }
    ;

inner_join_conditions:
	/* empty */ {
        $$ = nullptr; // 或者可以使用一个空的条件列表
    }
	| ON condition {
        $$ = new std::vector<ConditionSqlNode>; // 创建一个条件列表
        $$->emplace_back(*$2); // 将条件添加到列表中
	}
	| ON condition AND condition_list {
        if ($4 != nullptr) {
            $$ = $4;
        } else {
            $$ = new std::vector<ConditionSqlNode>;
        }
        $$->emplace_back(*$2);
        delete $2;
    }
	;


where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    ;
condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
condition:
    rel_attr comp_op value
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op value 
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 0;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | rel_attr comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | rel_attr IS NULL_T 
    {
        $$ = new ConditionSqlNode;
        $$->left_is_attr = 1;
        $$->left_attr = *$1;
        $$->right_is_attr = 0;
        $$->right_value = Value();
        $$->right_value.set_isNull(true);
        $$->comp = IS_COM;

        delete $1;
    }
    | rel_attr IS NOT NULL_T
    {
        $$ = new ConditionSqlNode;
        $$->left_is_attr = 1;
        $$->left_attr = *$1;
        $$->right_is_attr = 0;
        $$->right_value = Value();
        $$->right_value.set_isNull(true);
        $$->comp = ISNOT_COM;

        delete $1;
    }
    | value IS NULL_T 
    {
        $$ = new ConditionSqlNode;
        $$->left_is_attr = 0;
        $$->left_value = *$1;
        $$->right_is_attr = 0;
        $$->right_value = Value();
        $$->right_value.set_isNull(true);
        $$->comp = IS_COM;

        delete $1;
    }
    | value IS NOT NULL_T 
    {
        $$ = new ConditionSqlNode;
        $$->left_is_attr = 0;
        $$->left_value = *$1;
        $$->right_is_attr = 0;
        $$->right_value = Value();
        $$->right_value.set_isNull(true);
        $$->comp = ISNOT_COM;

        delete $1;
    }
    | value comp_op LBRACE value_list RBRACE {
        $$ = new ConditionSqlNode;
        $$ -> left_is_attr = 0;
        $$ -> left_value = *$1;
        $$ -> right_is_attr = 0;
        $$ -> right_is_subselect = 1;
        $$ -> in_values.swap(*$4);
        $$ -> comp = $2;

        delete $1;
    }
    | value comp_op LBRACE select_stmt RBRACE {
        $$ = new ConditionSqlNode;
        $$ -> left_is_attr = 0;
        $$ -> left_value = *$1;
        $$ -> right_is_attr = 0;
        $$ -> right_is_subselect = 2;
        $$ -> select = &($4 -> selection);
        $$ -> comp = $2;

        delete $1;
    } 
    | rel_attr comp_op LBRACE value_list RBRACE {
        $$ = new ConditionSqlNode;
        $$->left_is_attr = 1;
        $$->left_attr = *$1;
        $$->right_is_attr = 0;
        $$->right_is_subselect = 1;
        $$->in_values.swap(*$4);
        $$->comp = $2;

        delete $1;
    }
    | rel_attr comp_op LBRACE select_stmt RBRACE {
        $$ = new ConditionSqlNode;
        $$ -> left_is_attr = 1;
        $$ -> left_attr = *$1;
        $$ -> right_is_attr = 0;
        $$ -> right_is_subselect = 2;
        $$ -> select = &($4 -> selection);
        $$ -> comp = $2;

        delete $1;
    }
    | LBRACE select_stmt RBRACE comp_op rel_attr {
        $$ = new ConditionSqlNode;
        $$ -> left_is_attr = 1;
        $$ -> left_attr = *$5;
        $$ -> right_is_attr = 0;
        $$ -> right_is_subselect = 2;
        $$ -> select = &($2 -> selection);
        if ($4 == LESS_THAN) {
            $$ -> comp = GREAT_THAN;
        } else if($4 == LESS_EQUAL){
            $$ -> comp = GREAT_EQUAL;
        } else if ($4 == GREAT_THAN){
            $$ -> comp = LESS_THAN;
        } else if($4 == GREAT_EQUAL){
            $$ -> comp = LESS_EQUAL;
        }else {
            $$ -> comp = $4;
        }

        delete $5;
    }
    | EXISTSS LBRACE select_stmt RBRACE {
        $$ = new ConditionSqlNode;
        $$ -> left_is_attr = 0;
        $$ -> left_value = Value(0);
        $$ -> right_is_attr = 0;
        $$ -> right_is_subselect = 2;
        $$ -> select = &($3 -> selection);
        $$ -> comp = EXISTS;
    }
    | NOT EXISTSS LBRACE select_stmt RBRACE {
        $$ = new ConditionSqlNode;
        $$ -> left_is_attr = 0;
        $$ -> left_value = Value(0);
        $$ -> right_is_attr = 0;
        $$ -> right_is_subselect = 2;
        $$ -> select = &($4 -> selection);
        $$ -> comp = NOT_EXISTS;
    }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE { $$ = STR_LIKE; };
    | NOT LIKE { $$ = STR_NOT_LIKE; };    
    | INS { $$ = IN; };    
    | NOT INS { $$ = NOT_IN; };    
    | EXISTSS { $$ = EXISTS; };    
    | NOT EXISTSS { $$ = NOT_EXISTS; };    
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
