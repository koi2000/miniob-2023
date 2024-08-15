/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "common/time/date.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg, bool flag = false)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  error_sql_node->error.flag = flag;
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

AggrFuncType get_aggr_func_type(char *func_name)
{
  int len = strlen(func_name);
  for (int i = 0; i < len; i++) {
    func_name[i] = tolower(func_name[i]);
  }
  if (0 == strcmp(func_name, "max")) {
    return AggrFuncType::AGG_MAX;
  } else if (0 == strcmp(func_name, "min")) {
    return AggrFuncType::AGG_MIN;
  } else if (0 == strcmp(func_name, "sum")) {
    return AggrFuncType::AGG_SUM;
  } else if (0 == strcmp(func_name, "avg")) {
    return AggrFuncType::AGG_AVG;
  } else if (0 == strcmp(func_name, "count")) {
    return AggrFuncType::AGG_COUNT;
  } 
  return AggrFuncType::AGGR_FUNC_TYPE_NUM;
}


#line 136 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    CREATE = 259,
    DROP = 260,
    TABLE = 261,
    TABLES = 262,
    INDEX = 263,
    VIEW = 264,
    CALC = 265,
    SELECT = 266,
    DESC = 267,
    SHOW = 268,
    SYNC = 269,
    INSERT = 270,
    DELETE = 271,
    UPDATE = 272,
    LBRACE = 273,
    RBRACE = 274,
    COMMA = 275,
    TRX_BEGIN = 276,
    TRX_COMMIT = 277,
    TRX_ROLLBACK = 278,
    INT_T = 279,
    STRING_T = 280,
    FLOAT_T = 281,
    DATE_T = 282,
    TEXT_T = 283,
    HELP = 284,
    EXIT = 285,
    DOT = 286,
    INTO = 287,
    VALUES = 288,
    FROM = 289,
    WHERE = 290,
    AND = 291,
    OR = 292,
    SET = 293,
    ON = 294,
    LOAD = 295,
    DATA = 296,
    INFILE = 297,
    EXPLAIN = 298,
    IS = 299,
    NULL_T = 300,
    NULLABLE = 301,
    INNER = 302,
    JOIN = 303,
    AS = 304,
    IN = 305,
    EXISTS = 306,
    EQ = 307,
    LT = 308,
    GT = 309,
    LE = 310,
    GE = 311,
    NE = 312,
    NOT = 313,
    LIKE = 314,
    UNIQUE = 315,
    AGGR_MAX = 316,
    AGGR_MIN = 317,
    AGGR_SUM = 318,
    AGGR_AVG = 319,
    AGGR_COUNT = 320,
    LENGTH = 321,
    ROUND = 322,
    DATE_FORMAT = 323,
    ORDER = 324,
    GROUP = 325,
    BY = 326,
    ASC = 327,
    HAVING = 328,
    NUMBER = 329,
    FLOAT = 330,
    ID = 331,
    SSS = 332,
    DATE_STR = 333,
    UMINUS = 334
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 153 "yacc_sql.y"

  ParsedSqlNode *                   sql_node;
  Value *                           value;
  enum CompOp                       comp;
  RelAttrSqlNode *                  rel_attr;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  UpdateKV *                        update_kv;
  std::vector<UpdateKV> *           update_kv_list;
  std::vector<Expression *> *       expression_list;
  std::vector<Value> *              value_list;
  std::vector<std::string> *        relation_list;
  std::vector<std::vector<Value>> * insert_value_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  InnerJoinSqlNode *                inner_joins;
  std::vector<InnerJoinSqlNode> *   inner_joins_list;
  OrderBySqlNode*                   orderby_unit;
  std::vector<OrderBySqlNode> *     orderby_unit_list;
  char *                            string;
  int                               number;
  float                             floats;
  bool                              boolean;

#line 293 "yacc_sql.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);

#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   279

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  152
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  271

#define YYUNDEFTOK  2
#define YYMAXUTOK   334


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    81,    79,     2,    80,     2,    82,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    83
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   256,   256,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   289,   295,   300,   306,   312,
     318,   324,   331,   337,   345,   367,   370,   376,   379,   392,
     403,   412,   428,   444,   455,   458,   471,   480,   492,   495,
     499,   506,   509,   516,   523,   541,   544,   545,   546,   547,
     548,   551,   572,   575,   589,   592,   605,   625,   628,   644,
     648,   652,   668,   673,   680,   692,   715,   718,   731,   741,
     744,   756,   759,   762,   767,   783,   786,   804,   812,   821,
     858,   868,   877,   892,   895,   898,   901,   904,   907,   916,
     919,   924,   929,   932,   935,   941,   964,   971,   974,   977,
     983,   993,   998,  1005,  1010,  1016,  1025,  1028,  1034,  1038,
    1045,  1049,  1056,  1063,  1067,  1074,  1081,  1088,  1096,  1103,
    1111,  1114,  1121,  1124,  1131,  1134,  1141,  1142,  1143,  1144,
    1145,  1146,  1147,  1148,  1149,  1150,  1154,  1155,  1159,  1172,
    1180,  1190,  1191
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "VIEW", "CALC", "SELECT", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "AND", "OR", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "IS",
  "NULL_T", "NULLABLE", "INNER", "JOIN", "AS", "IN", "EXISTS", "EQ", "LT",
  "GT", "LE", "GE", "NE", "NOT", "LIKE", "UNIQUE", "AGGR_MAX", "AGGR_MIN",
  "AGGR_SUM", "AGGR_AVG", "AGGR_COUNT", "LENGTH", "ROUND", "DATE_FORMAT",
  "ORDER", "GROUP", "BY", "ASC", "HAVING", "NUMBER", "FLOAT", "ID", "SSS",
  "DATE_STR", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "unique_option", "idx_col_list",
  "drop_index_stmt", "show_index_stmt", "create_table_stmt",
  "attr_def_list", "attr_def", "null_option", "as_option",
  "create_view_stmt", "number", "type", "insert_stmt", "insert_col_list",
  "insert_value_list", "insert_value", "value_list", "value",
  "delete_stmt", "update_stmt", "update_kv_list", "update_kv", "from_list",
  "alias", "from_node", "join_list", "sub_query_expr", "select_stmt",
  "calc_stmt", "expression_list", "expression", "aggr_func_expr",
  "sys_func_type", "func_expr", "rel_attr", "where", "is_null_comp",
  "condition", "sort_unit", "sort_list", "opt_order_by", "opt_group_by",
  "opt_having", "comp_op", "exists_op", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,    43,
      45,    42,    47,   334
};
# endif

#define YYPACT_NINF (-190)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-52)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     184,    16,   104,    39,    39,   -65,    12,  -190,    -9,     0,
     -43,  -190,  -190,  -190,  -190,  -190,   -30,     8,   184,    60,
      75,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,    33,    42,  -190,    84,    45,    49,    13,
    -190,  -190,  -190,  -190,  -190,  -190,    -1,  -190,  -190,    39,
      98,  -190,  -190,  -190,   -28,  -190,   118,  -190,  -190,   103,
    -190,  -190,   107,    66,    80,   121,   108,   119,  -190,  -190,
    -190,  -190,    -6,    -5,    86,  -190,   126,   149,   150,    39,
     -20,  -190,    91,    94,  -190,    39,    39,    39,    39,   151,
      39,    97,    99,   156,   141,   101,    89,   102,   105,  -190,
     167,   110,   167,   144,   114,  -190,  -190,   161,   -13,  -190,
    -190,  -190,  -190,     1,     1,  -190,  -190,    39,   172,   -39,
     173,  -190,   116,   171,    77,  -190,   157,   188,  -190,   178,
     122,   191,  -190,   195,  -190,   140,  -190,  -190,  -190,  -190,
    -190,   170,    97,   141,   195,   200,  -190,   168,   185,    90,
      39,    39,   101,   141,   214,  -190,  -190,  -190,  -190,  -190,
      -3,   105,   202,   147,   206,   208,   180,  -190,   173,   160,
     212,    39,   213,  -190,   -31,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,   -24,  -190,  -190,    39,    77,    77,    20,    20,
     188,  -190,   169,   158,  -190,   201,  -190,   191,    -2,   195,
     187,   174,   175,  -190,   176,   179,  -190,    51,   200,  -190,
    -190,   203,  -190,  -190,    20,  -190,   217,  -190,  -190,  -190,
     230,  -190,  -190,   167,  -190,   167,   195,   -39,    39,    77,
     186,    39,   235,   213,  -190,   -29,  -190,  -190,   237,   218,
    -190,    90,   189,  -190,    51,  -190,  -190,  -190,  -190,    77,
      39,  -190,    61,    -7,   238,  -190,  -190,  -190,  -190,    39,
    -190
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    35,     0,    93,    93,     0,     0,    27,     0,     0,
       0,    28,    29,    30,    26,    25,     0,     0,     0,     0,
     151,    24,    23,    16,    17,    18,    19,     9,    10,    11,
      12,    13,    14,     8,    15,     5,     7,     6,     4,     3,
      20,    21,    22,     0,     0,    36,     0,     0,     0,    93,
      73,   107,   108,   109,    69,    70,   111,    72,    71,    93,
     115,   100,   104,    90,    81,   102,     0,   103,   101,    88,
      33,    32,     0,     0,     0,     0,     0,     0,   149,     1,
     152,     2,    51,     0,     0,    31,     0,     0,     0,    93,
       0,    99,     0,     0,    82,    93,    93,    93,    93,    91,
      93,     0,     0,    62,   116,     0,     0,     0,     0,    52,
       0,     0,     0,     0,     0,    87,    98,     0,    81,   112,
     114,   113,    83,    94,    95,    96,    97,    93,     0,    81,
      79,    40,     0,     0,    93,    74,     0,    76,   150,     0,
       0,    44,    43,    37,    53,     0,    39,   106,   105,    92,
     110,    85,     0,   116,    37,     0,   146,     0,     0,   117,
      93,    93,     0,   116,     0,    56,    57,    58,    59,    60,
      48,     0,     0,     0,     0,     0,     0,    84,    79,   132,
       0,    93,    64,   147,     0,   144,   136,   137,   138,   139,
     140,   141,     0,   142,   121,    93,    93,    93,   122,    78,
      76,    75,     0,     0,    49,     0,    47,    44,    41,    37,
       0,     0,     0,    80,     0,   134,    63,    67,     0,    61,
     118,     0,   145,   143,   120,   123,   124,    77,   148,    55,
       0,    50,    45,     0,    38,     0,    37,    81,    93,    93,
     130,    93,     0,    64,   119,    48,    42,    54,     0,     0,
     133,   135,     0,    89,    67,    66,    65,    46,    34,    93,
      93,    68,    85,   125,   128,   131,    86,   126,   127,    93,
     129
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -190,  -190,   241,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -150,  -190,  -190,  -190,    54,    92,
      17,    62,  -190,  -190,  -190,  -190,  -190,    25,    53,    15,
     166,  -190,  -190,    73,   112,   100,  -126,   123,    14,  -190,
     -48,  -190,    -4,   -57,  -190,  -190,  -190,  -190,  -135,  -190,
    -189,  -190,    10,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    46,   174,    31,    32,    33,   172,   141,
     206,   110,    34,   230,   170,    35,   133,   219,   182,   242,
      61,    36,    37,   163,   137,   153,    99,   130,   177,    62,
      38,    39,    63,    64,    65,    66,    67,    68,   135,   194,
     159,   264,   265,   253,   215,   240,   195,   160,    40,    41,
      42,    81
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      69,    87,    91,   151,   180,   267,   148,   225,   226,   -51,
      93,    70,   108,   111,   220,   203,   204,    89,   179,    71,
      72,    93,    43,    73,     4,    44,   222,   221,   201,   205,
      90,    49,   118,    75,    74,   223,    93,    94,   123,   124,
     125,   126,   204,   109,   112,    88,    76,   109,    94,    77,
     251,    95,    96,    97,    98,   205,   119,    49,    50,   234,
      79,   120,   142,    94,   144,   268,    95,    96,    97,    98,
     262,   241,    95,    96,    97,    98,    45,   158,    80,    51,
      52,    53,    97,    98,    50,   117,   248,    54,    55,    56,
      57,    58,    84,    59,    60,    49,   128,   196,   197,    95,
      96,    97,    98,   198,   199,    51,    52,    53,   176,    82,
      47,   249,    48,    54,    55,    56,    57,    58,    83,    59,
      60,    85,    50,   149,   217,    86,   196,   197,   156,    92,
      95,    96,    97,    98,    50,   157,   100,   101,   224,   158,
     158,   102,   103,    51,    52,    53,   165,   166,   167,   168,
     169,    54,    55,    56,    57,    58,   104,    59,    60,   105,
     106,   107,   113,    54,    55,   114,    57,    58,   115,   116,
     122,   127,   121,   129,   132,   131,   134,   136,     4,   139,
     147,   140,   158,   145,   254,   246,   143,   247,     1,     2,
     146,   150,   154,   152,     3,     4,     5,     6,     7,     8,
       9,    10,   158,   263,   155,    11,    12,    13,   162,   161,
     164,   171,   263,    14,    15,   173,   175,   176,   181,   183,
     202,   208,    16,   209,    17,   210,   211,    18,   212,   184,
     214,   216,   229,   218,   250,   185,   235,   186,   187,   188,
     189,   190,   191,   192,   193,   228,   231,   238,   244,   245,
     236,   237,   239,   196,   255,   252,   258,   259,   269,    78,
     260,   232,   257,   207,    95,    96,    97,    98,   256,   261,
     233,   243,   138,   227,   200,   178,   266,     0,   213,   270
};

static const yytype_int16 yycheck[] =
{
       4,    49,    59,   129,   154,    12,    19,   196,   197,    11,
      49,    76,    18,    18,    45,    18,    45,    18,   153,     7,
       8,    49,     6,    32,    11,     9,    50,    58,   163,    58,
      31,    18,    89,    76,    34,    59,    49,    76,    95,    96,
      97,    98,    45,    49,    49,    49,    76,    49,    76,    41,
     239,    79,    80,    81,    82,    58,    76,    18,    45,   209,
       0,    81,   110,    76,   112,    72,    79,    80,    81,    82,
     259,    20,    79,    80,    81,    82,    60,   134,     3,    66,
      67,    68,    81,    82,    45,    89,   236,    74,    75,    76,
      77,    78,     8,    80,    81,    18,   100,    36,    37,    79,
      80,    81,    82,   160,   161,    66,    67,    68,    47,    76,
       6,   237,     8,    74,    75,    76,    77,    78,    76,    80,
      81,    76,    45,   127,   181,    76,    36,    37,    51,    31,
      79,    80,    81,    82,    45,    58,    18,    34,   195,   196,
     197,    34,    76,    66,    67,    68,    24,    25,    26,    27,
      28,    74,    75,    76,    77,    78,    76,    80,    81,    38,
      52,    42,    76,    74,    75,    39,    77,    78,    19,    19,
      76,    20,    81,    76,    18,    76,    35,    76,    11,    77,
      19,    76,   239,    39,   241,   233,    76,   235,     4,     5,
      76,    19,    76,    20,    10,    11,    12,    13,    14,    15,
      16,    17,   259,   260,    33,    21,    22,    23,    20,    52,
      32,    20,   269,    29,    30,    20,    76,    47,    18,    51,
       6,    19,    38,    76,    40,    19,    18,    43,    48,    44,
      70,    19,    74,    20,   238,    50,    49,    52,    53,    54,
      55,    56,    57,    58,    59,    76,    45,    71,    45,    19,
      76,    76,    73,    36,    19,    69,    19,    39,    20,    18,
      71,   207,   245,   171,    79,    80,    81,    82,   243,   254,
     208,   218,   106,   200,   162,   152,   262,    -1,   178,   269
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,    10,    11,    12,    13,    14,    15,    16,
      17,    21,    22,    23,    29,    30,    38,    40,    43,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    99,   100,   101,   106,   109,   115,   116,   124,   125,
     142,   143,   144,     6,     9,    60,    97,     6,     8,    18,
      45,    66,    67,    68,    74,    75,    76,    77,    78,    80,
      81,   114,   123,   126,   127,   128,   129,   130,   131,   126,
      76,     7,     8,    32,    34,    76,    76,    41,    86,     0,
       3,   145,    76,    76,     8,    76,    76,   124,   126,    18,
      31,   127,    31,    49,    76,    79,    80,    81,    82,   120,
      18,    34,    34,    76,    76,    38,    52,    42,    18,    49,
     105,    18,    49,    76,    39,    19,    19,   126,   127,    76,
      81,    81,    76,   127,   127,   127,   127,    20,   126,    76,
     121,    76,    18,   110,    35,   132,    76,   118,   114,    77,
      76,   103,   124,    76,   124,    39,    76,    19,    19,   126,
      19,   120,    20,   119,    76,    33,    51,    58,   127,   134,
     141,    52,    20,   117,    32,    24,    25,    26,    27,    28,
     108,    20,   102,    20,    98,    76,    47,   122,   121,   132,
      98,    18,   112,    51,    44,    50,    52,    53,    54,    55,
      56,    57,    58,    59,   133,   140,    36,    37,   127,   127,
     118,   132,     6,    18,    45,    58,   104,   103,    19,    76,
      19,    18,    48,   119,    70,   138,    19,   127,    20,   111,
      45,    58,    50,    59,   127,   134,   134,   117,    76,    74,
     107,    45,   102,   105,    98,    49,    76,    76,    71,    73,
     139,    20,   113,   112,    45,    19,   124,   124,    98,   120,
     126,   134,    69,   137,   127,    19,   111,   104,    19,    39,
      71,   113,   134,   127,   135,   136,   122,    12,    72,    20,
     136
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    85,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    97,    98,    98,    99,
     100,   101,   101,   101,   102,   102,   103,   103,   104,   104,
     104,   105,   105,   106,   106,   107,   108,   108,   108,   108,
     108,   109,   110,   110,   111,   111,   112,   113,   113,   114,
     114,   114,   114,   114,   115,   116,   117,   117,   118,   119,
     119,   120,   120,   120,   121,   122,   122,   123,   124,   124,
     125,   126,   126,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   128,   128,   129,   129,   129,
     130,   131,   131,   131,   131,   131,   132,   132,   133,   133,
     134,   134,   134,   134,   134,   135,   135,   135,   136,   136,
     137,   137,   138,   138,   139,   139,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   141,   141,   142,   143,
     144,   145,   145
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     2,    10,     0,     1,     0,     3,     5,
       4,     7,     9,     5,     0,     3,     6,     3,     0,     1,
       2,     0,     1,     5,     9,     1,     1,     1,     1,     1,
       1,     7,     0,     4,     0,     3,     4,     0,     3,     1,
       1,     1,     1,     1,     4,     6,     0,     3,     3,     0,
       3,     0,     1,     2,     3,     0,     7,     3,     2,     9,
       2,     2,     4,     0,     3,     3,     3,     3,     3,     2,
       1,     1,     1,     1,     1,     4,     4,     1,     1,     1,
       4,     1,     3,     3,     3,     1,     0,     2,     2,     3,
       3,     2,     2,     3,     3,     1,     2,     2,     1,     3,
       0,     3,     0,     3,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     1,     2,     7,     2,
       4,     0,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 257 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1812 "yacc_sql.cpp"
    break;

  case 25:
#line 289 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1821 "yacc_sql.cpp"
    break;

  case 26:
#line 295 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1829 "yacc_sql.cpp"
    break;

  case 27:
#line 300 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1837 "yacc_sql.cpp"
    break;

  case 28:
#line 306 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1845 "yacc_sql.cpp"
    break;

  case 29:
#line 312 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1853 "yacc_sql.cpp"
    break;

  case 30:
#line 318 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1861 "yacc_sql.cpp"
    break;

  case 31:
#line 324 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1871 "yacc_sql.cpp"
    break;

  case 32:
#line 331 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1879 "yacc_sql.cpp"
    break;

  case 33:
#line 337 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1889 "yacc_sql.cpp"
    break;

  case 34:
#line 346 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.unique = (yyvsp[-8].boolean);
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      
      std::vector<std::string> *idx_cols = (yyvsp[-1].relation_list);
      if (nullptr != idx_cols) {
        create_index.attr_names.swap(*idx_cols);
        delete (yyvsp[-1].relation_list);
      }
      create_index.attr_names.emplace_back((yyvsp[-2].string));
      std::reverse(create_index.attr_names.begin(), create_index.attr_names.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 1912 "yacc_sql.cpp"
    break;

  case 35:
#line 367 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 1920 "yacc_sql.cpp"
    break;

  case 36:
#line 371 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 1928 "yacc_sql.cpp"
    break;

  case 37:
#line 376 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 1936 "yacc_sql.cpp"
    break;

  case 38:
#line 380 "yacc_sql.y"
    {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 1950 "yacc_sql.cpp"
    break;

  case 39:
#line 393 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1962 "yacc_sql.cpp"
    break;

  case 40:
#line 404 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
      (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1972 "yacc_sql.cpp"
    break;

  case 41:
#line 413 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 1992 "yacc_sql.cpp"
    break;

  case 42:
#line 429 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-6].string);
      free((yyvsp[-6].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-3].attr_infos);
      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-4].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-4].attr_info);
    }
#line 2012 "yacc_sql.cpp"
    break;

  case 43:
#line 445 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
    }
#line 2024 "yacc_sql.cpp"
    break;

  case 44:
#line 455 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2032 "yacc_sql.cpp"
    break;

  case 45:
#line 459 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2046 "yacc_sql.cpp"
    break;

  case 46:
#line 472 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-5].string));
    }
#line 2059 "yacc_sql.cpp"
    break;

  case 47:
#line 481 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 2072 "yacc_sql.cpp"
    break;

  case 48:
#line 492 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2080 "yacc_sql.cpp"
    break;

  case 49:
#line 496 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2088 "yacc_sql.cpp"
    break;

  case 50:
#line 500 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2096 "yacc_sql.cpp"
    break;

  case 51:
#line 506 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2104 "yacc_sql.cpp"
    break;

  case 52:
#line 510 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2112 "yacc_sql.cpp"
    break;

  case 53:
#line 517 "yacc_sql.y"
    {
        (yyval.sql_node) = (yyvsp[0].sql_node);
        (yyval.sql_node)->flag = SCF_CREATE_VIEW;
        (yyval.sql_node)->create_view.view_name = (yyvsp[-2].string);
        free((yyvsp[-2].string));
    }
#line 2123 "yacc_sql.cpp"
    break;

  case 54:
#line 524 "yacc_sql.y"
    {
        (yyval.sql_node) = (yyvsp[0].sql_node);
        (yyval.sql_node)->flag = SCF_CREATE_VIEW;
        (yyval.sql_node)->create_view.view_name = (yyvsp[-6].string);

        std::vector<std::string>& col_names = (yyval.sql_node)->create_view.col_names;
        if (nullptr != (yyvsp[-3].relation_list)) {
            col_names.swap(*(yyvsp[-3].relation_list));
            delete (yyvsp[-3].relation_list);
        }
        col_names.emplace_back((yyvsp[-4].string));
        std::reverse(col_names.begin(),col_names.end());
        free((yyvsp[-6].string));
    }
#line 2142 "yacc_sql.cpp"
    break;

  case 55:
#line 541 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2148 "yacc_sql.cpp"
    break;

  case 56:
#line 544 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2154 "yacc_sql.cpp"
    break;

  case 57:
#line 545 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2160 "yacc_sql.cpp"
    break;

  case 58:
#line 546 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2166 "yacc_sql.cpp"
    break;

  case 59:
#line 547 "yacc_sql.y"
               { (yyval.number)=DATES;}
#line 2172 "yacc_sql.cpp"
    break;

  case 60:
#line 548 "yacc_sql.y"
               { (yyval.number)=TEXTS; }
#line 2178 "yacc_sql.cpp"
    break;

  case 61:
#line 552 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-4].string);
      if ((yyvsp[0].insert_value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[0].insert_value_list));
        delete (yyvsp[0].insert_value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-1].value_list));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      if (nullptr != (yyvsp[-3].relation_list)) {
        (yyval.sql_node)->insertion.attrs_name.swap(*(yyvsp[-3].relation_list));
        std::reverse((yyval.sql_node)->insertion.attrs_name.begin(), (yyval.sql_node)->insertion.attrs_name.end());
        delete (yyvsp[-3].relation_list);
      }
      delete (yyvsp[-1].value_list);
      free((yyvsp[-4].string));
    }
#line 2200 "yacc_sql.cpp"
    break;

  case 62:
#line 572 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2208 "yacc_sql.cpp"
    break;

  case 63:
#line 576 "yacc_sql.y"
    {
      if ((yyvsp[-1].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[-1].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->emplace_back((yyvsp[-2].string));
      free((yyvsp[-2].string));      
    }
#line 2222 "yacc_sql.cpp"
    break;

  case 64:
#line 589 "yacc_sql.y"
    {
      (yyval.insert_value_list) = nullptr;
    }
#line 2230 "yacc_sql.cpp"
    break;

  case 65:
#line 593 "yacc_sql.y"
    {
      if ((yyvsp[0].insert_value_list) != nullptr) {
        (yyval.insert_value_list) = (yyvsp[0].insert_value_list);
      } else {
        (yyval.insert_value_list) = new std::vector<std::vector<Value>>;
      }
      (yyval.insert_value_list)->emplace_back(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
#line 2244 "yacc_sql.cpp"
    break;

  case 66:
#line 606 "yacc_sql.y"
    {
      Value tmp;
      if(!exp2value((yyvsp[-2].expression), tmp)) {
        yyerror(&(yyloc), sql_string, sql_result, scanner, "exp2value error");
        YYERROR;
      }
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[-1].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(tmp);
      std::reverse((yyval.value_list)->begin(), (yyval.value_list)->end());
      delete (yyvsp[-2].expression);
    }
#line 2264 "yacc_sql.cpp"
    break;

  case 67:
#line 625 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2272 "yacc_sql.cpp"
    break;

  case 68:
#line 628 "yacc_sql.y"
                                   { 
      Value tmp;
      if(!exp2value((yyvsp[-1].expression),tmp)) {
        yyerror(&(yyloc), sql_string, sql_result, scanner, "error");
        YYERROR;
      }
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(tmp);
      delete (yyvsp[-1].expression);
    }
#line 2291 "yacc_sql.cpp"
    break;

  case 69:
#line 644 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]); // useless
    }
#line 2300 "yacc_sql.cpp"
    break;

  case 70:
#line 648 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]); // useless
    }
#line 2309 "yacc_sql.cpp"
    break;

  case 71:
#line 652 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      std::string str(tmp);
      Value * value = new Value();
      int date;
      if(string_to_date(str,date) < 0) {
        yyerror(&(yyloc),sql_string,sql_result,scanner,"date invaid",true);
        YYERROR;
      }
      else
      {
        value->set_date(date);
      }
      (yyval.value) = value;
      free(tmp);
    }
#line 2330 "yacc_sql.cpp"
    break;

  case 72:
#line 668 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2340 "yacc_sql.cpp"
    break;

  case 73:
#line 673 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2349 "yacc_sql.cpp"
    break;

  case 74:
#line 681 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      (yyval.sql_node)->deletion.conditions = nullptr;
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2363 "yacc_sql.cpp"
    break;

  case 75:
#line 693 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-4].string);
      (yyval.sql_node)->update.attribute_names.emplace_back((yyvsp[-2].update_kv)->attr_name);
      (yyval.sql_node)->update.values.emplace_back((yyvsp[-2].update_kv)->value);
      if (nullptr != (yyvsp[-1].update_kv_list)) {
        for (UpdateKV kv : *(yyvsp[-1].update_kv_list)) {
          (yyval.sql_node)->update.attribute_names.emplace_back(kv.attr_name);
          (yyval.sql_node)->update.values.emplace_back(kv.value);
        }
        delete (yyvsp[-1].update_kv_list);
      }
      (yyval.sql_node)->update.conditions = nullptr;
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->update.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-4].string));
      delete (yyvsp[-2].update_kv);
    }
#line 2387 "yacc_sql.cpp"
    break;

  case 76:
#line 715 "yacc_sql.y"
    {
      (yyval.update_kv_list) = nullptr;
    }
#line 2395 "yacc_sql.cpp"
    break;

  case 77:
#line 719 "yacc_sql.y"
    {
      if ((yyvsp[0].update_kv_list) != nullptr) {
        (yyval.update_kv_list) = (yyvsp[0].update_kv_list);
      } else {
        (yyval.update_kv_list) = new std::vector<UpdateKV>;
      }
      (yyval.update_kv_list)->emplace_back(*(yyvsp[-1].update_kv));
      delete (yyvsp[-1].update_kv);
    }
#line 2409 "yacc_sql.cpp"
    break;

  case 78:
#line 732 "yacc_sql.y"
    {
      (yyval.update_kv) = new UpdateKV;
      (yyval.update_kv)->attr_name = (yyvsp[-2].string);
      (yyval.update_kv)->value = (yyvsp[0].expression);
      free((yyvsp[-2].string));
    }
#line 2420 "yacc_sql.cpp"
    break;

  case 79:
#line 741 "yacc_sql.y"
                {
      (yyval.inner_joins_list) = nullptr;
    }
#line 2428 "yacc_sql.cpp"
    break;

  case 80:
#line 744 "yacc_sql.y"
                                {
      if (nullptr != (yyvsp[0].inner_joins_list)) {
        (yyval.inner_joins_list) = (yyvsp[0].inner_joins_list);
      } else {
        (yyval.inner_joins_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.inner_joins_list)->emplace_back(*(yyvsp[-1].inner_joins));
      delete (yyvsp[-1].inner_joins);
    }
#line 2442 "yacc_sql.cpp"
    break;

  case 81:
#line 756 "yacc_sql.y"
                {
      (yyval.string) = nullptr;
    }
#line 2450 "yacc_sql.cpp"
    break;

  case 82:
#line 759 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2458 "yacc_sql.cpp"
    break;

  case 83:
#line 762 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2466 "yacc_sql.cpp"
    break;

  case 84:
#line 767 "yacc_sql.y"
                       {
      if (nullptr != (yyvsp[0].inner_joins)) {
        (yyval.inner_joins) = (yyvsp[0].inner_joins);
      } else {
        (yyval.inner_joins) = new InnerJoinSqlNode;
      }
      (yyval.inner_joins)->base_relation.first = (yyvsp[-2].string);
      (yyval.inner_joins)->base_relation.second = nullptr == (yyvsp[-1].string) ? "" : std::string((yyvsp[-1].string));
      std::reverse((yyval.inner_joins)->join_relations.begin(), (yyval.inner_joins)->join_relations.end());
      std::reverse((yyval.inner_joins)->conditions.begin(), (yyval.inner_joins)->conditions.end());
      free((yyvsp[-2].string));
      free((yyvsp[-1].string));
    }
#line 2484 "yacc_sql.cpp"
    break;

  case 85:
#line 783 "yacc_sql.y"
                {
      (yyval.inner_joins) = nullptr;
    }
#line 2492 "yacc_sql.cpp"
    break;

  case 86:
#line 786 "yacc_sql.y"
                                                 {
      if (nullptr != (yyvsp[0].inner_joins)) {
        (yyval.inner_joins) = (yyvsp[0].inner_joins);
      } else {
        (yyval.inner_joins) = new InnerJoinSqlNode;
      }
      std::string temp = "";
      if (nullptr != (yyvsp[-3].string)) {
        temp = (yyvsp[-3].string);
      }
      (yyval.inner_joins)->join_relations.emplace_back((yyvsp[-4].string), temp);
      (yyval.inner_joins)->conditions.emplace_back((yyvsp[-1].expression));
      free((yyvsp[-4].string));
      free((yyvsp[-3].string));
    }
#line 2512 "yacc_sql.cpp"
    break;

  case 87:
#line 805 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr((yyvsp[-1].sql_node)->selection); // 子查询中所有的 Expression 都交给 SubQueryExpr 来管理了
      delete (yyvsp[-1].sql_node);
    }
#line 2521 "yacc_sql.cpp"
    break;

  case 88:
#line 813 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].expression_list) != nullptr) {
        std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
        (yyval.sql_node)->selection.project_exprs.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2534 "yacc_sql.cpp"
    break;

  case 89:
#line 822 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-7].expression_list) != nullptr) {
        std::reverse((yyvsp[-7].expression_list)->begin(), (yyvsp[-7].expression_list)->end());
        (yyval.sql_node)->selection.project_exprs.swap(*(yyvsp[-7].expression_list));
        delete (yyvsp[-7].expression_list);
      }
      if ((yyvsp[-4].inner_joins_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-4].inner_joins_list));
        delete (yyvsp[-4].inner_joins_list);
      }
      (yyval.sql_node)->selection.relations.push_back(*(yyvsp[-5].inner_joins));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      (yyval.sql_node)->selection.conditions = nullptr;
      if ((yyvsp[-3].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions = (yyvsp[-3].expression);
      }
      if ((yyvsp[-2].expression_list) != nullptr) {
        (yyval.sql_node)->selection.groupby_exprs.swap(*(yyvsp[-2].expression_list));
        delete (yyvsp[-2].expression_list);
        std::reverse((yyval.sql_node)->selection.groupby_exprs.begin(), (yyval.sql_node)->selection.groupby_exprs.end());
      }
      (yyval.sql_node)->selection.having_conditions = nullptr;
      if ((yyvsp[-1].expression) != nullptr) {
        (yyval.sql_node)->selection.having_conditions = (yyvsp[-1].expression);
      }

      if ((yyvsp[0].orderby_unit_list) != nullptr) {
        (yyval.sql_node)->selection.orderbys.swap(*(yyvsp[0].orderby_unit_list));
        delete (yyvsp[0].orderby_unit_list);
      }
      delete (yyvsp[-5].inner_joins);
    }
#line 2573 "yacc_sql.cpp"
    break;

  case 90:
#line 859 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2584 "yacc_sql.cpp"
    break;

  case 91:
#line 869 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      if (nullptr != (yyvsp[0].string)) {
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      free((yyvsp[0].string));
    }
#line 2597 "yacc_sql.cpp"
    break;

  case 92:
#line 878 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      if (nullptr != (yyvsp[-2].string)) {
        (yyvsp[-3].expression)->set_alias((yyvsp[-2].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-3].expression));
      free((yyvsp[-2].string));
    }
#line 2614 "yacc_sql.cpp"
    break;

  case 93:
#line 892 "yacc_sql.y"
          {
      (yyval.expression) = nullptr;
    }
#line 2622 "yacc_sql.cpp"
    break;

  case 94:
#line 895 "yacc_sql.y"
                               {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2630 "yacc_sql.cpp"
    break;

  case 95:
#line 898 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2638 "yacc_sql.cpp"
    break;

  case 96:
#line 901 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2646 "yacc_sql.cpp"
    break;

  case 97:
#line 904 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2654 "yacc_sql.cpp"
    break;

  case 98:
#line 907 "yacc_sql.y"
                                    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->front();
      } else {
        (yyval.expression) = new ExprListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2668 "yacc_sql.cpp"
    break;

  case 99:
#line 916 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2676 "yacc_sql.cpp"
    break;

  case 100:
#line 919 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2686 "yacc_sql.cpp"
    break;

  case 101:
#line 924 "yacc_sql.y"
               {
      (yyval.expression) = new FieldExpr((yyvsp[0].rel_attr)->relation_name, (yyvsp[0].rel_attr)->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2696 "yacc_sql.cpp"
    break;

  case 102:
#line 929 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression); // AggrFuncExpr
    }
#line 2704 "yacc_sql.cpp"
    break;

  case 103:
#line 932 "yacc_sql.y"
                {
      (yyval.expression) = (yyvsp[0].expression); // SysFuncExpr
    }
#line 2712 "yacc_sql.cpp"
    break;

  case 104:
#line 935 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression); // SubQueryExpr
    }
#line 2720 "yacc_sql.cpp"
    break;

  case 105:
#line 942 "yacc_sql.y"
    {
      if((yyvsp[-1].expression) == nullptr) {
        yyerror(&(yyloc), sql_string, sql_result, scanner, "only support count(*)");
        YYERROR;
      }

      Expression* rhs = (yyvsp[-1].expression);
      if ((yyvsp[-1].expression)->type() == ExprType::FIELD) {
        FieldExpr* field_expr = static_cast<FieldExpr*>((yyvsp[-1].expression));
        if (field_expr->get_field_name() == "*") {
          if(get_aggr_func_type((yyvsp[-3].string)) != AggrFuncType::AGG_COUNT) {
            delete (yyvsp[-1].expression);
            yyerror(&(yyloc), sql_string, sql_result, scanner, "only support count(*)");
            YYERROR;
          }
          rhs = new ValueExpr(Value(1));
          delete (yyvsp[-1].expression);
        }
      }
      (yyval.expression) = new AggrFuncExpr(get_aggr_func_type((yyvsp[-3].string)), rhs);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2747 "yacc_sql.cpp"
    break;

  case 106:
#line 965 "yacc_sql.y"
    {
        yyerror(&(yyloc), sql_string, sql_result, scanner, "only support count(*)");
        YYERROR;
    }
#line 2756 "yacc_sql.cpp"
    break;

  case 107:
#line 971 "yacc_sql.y"
           {
      (yyval.number) = SysFuncType::SYS_FUNC_LENGTH;
    }
#line 2764 "yacc_sql.cpp"
    break;

  case 108:
#line 974 "yacc_sql.y"
            {
      (yyval.number) = SysFuncType::SYS_FUNC_ROUND;
    }
#line 2772 "yacc_sql.cpp"
    break;

  case 109:
#line 977 "yacc_sql.y"
                  {
      (yyval.number) = SysFuncType::SYS_FUNC_DATE_FORMAT;
    }
#line 2780 "yacc_sql.cpp"
    break;

  case 110:
#line 984 "yacc_sql.y"
    {
      std::reverse((yyvsp[-1].expression_list)->begin(),(yyvsp[-1].expression_list)->end());
      (yyval.expression) = new SysFuncExpr((SysFuncType)(yyvsp[-3].number),*(yyvsp[-1].expression_list));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2791 "yacc_sql.cpp"
    break;

  case 111:
#line 993 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2801 "yacc_sql.cpp"
    break;

  case 112:
#line 998 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2813 "yacc_sql.cpp"
    break;

  case 113:
#line 1005 "yacc_sql.y"
                  {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = "*";
      (yyval.rel_attr)->attribute_name = "*";
    }
#line 2823 "yacc_sql.cpp"
    break;

  case 114:
#line 1010 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      free((yyvsp[-2].string));
    }
#line 2834 "yacc_sql.cpp"
    break;

  case 115:
#line 1016 "yacc_sql.y"
          {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = "*";
      (yyval.rel_attr)->attribute_name = "*";
    }
#line 2844 "yacc_sql.cpp"
    break;

  case 116:
#line 1025 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2852 "yacc_sql.cpp"
    break;

  case 117:
#line 1028 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[0].expression);  
    }
#line 2860 "yacc_sql.cpp"
    break;

  case 118:
#line 1035 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2868 "yacc_sql.cpp"
    break;

  case 119:
#line 1039 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2876 "yacc_sql.cpp"
    break;

  case 120:
#line 1046 "yacc_sql.y"
    {
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2884 "yacc_sql.cpp"
    break;

  case 121:
#line 1050 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[0].boolean) ? IS_NULL : IS_NOT_NULL, (yyvsp[-1].expression), value_expr);
    }
#line 2895 "yacc_sql.cpp"
    break;

  case 122:
#line 1057 "yacc_sql.y"
    {
      Value val;
      val.set_null();
      ValueExpr *value_expr = new ValueExpr(val);
      (yyval.expression) = new ComparisonExpr((yyvsp[-1].comp), value_expr, (yyvsp[0].expression));
    }
#line 2906 "yacc_sql.cpp"
    break;

  case 123:
#line 1064 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2914 "yacc_sql.cpp"
    break;

  case 124:
#line 1068 "yacc_sql.y"
    {
      (yyval.expression) = new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2922 "yacc_sql.cpp"
    break;

  case 125:
#line 1075 "yacc_sql.y"
        {
    (yyval.orderby_unit) = new OrderBySqlNode();//默认是升序
    (yyval.orderby_unit)->expr = (yyvsp[0].expression);
    (yyval.orderby_unit)->is_asc = true;
	}
#line 2932 "yacc_sql.cpp"
    break;

  case 126:
#line 1082 "yacc_sql.y"
        {
    (yyval.orderby_unit) = new OrderBySqlNode();
    (yyval.orderby_unit)->expr = (yyvsp[-1].expression);
    (yyval.orderby_unit)->is_asc = false;
	}
#line 2942 "yacc_sql.cpp"
    break;

  case 127:
#line 1089 "yacc_sql.y"
        {
    (yyval.orderby_unit) = new OrderBySqlNode();//默认是升序
    (yyval.orderby_unit)->expr = (yyvsp[-1].expression);
    (yyval.orderby_unit)->is_asc = true;
	}
#line 2952 "yacc_sql.cpp"
    break;

  case 128:
#line 1097 "yacc_sql.y"
        {
    (yyval.orderby_unit_list) = new std::vector<OrderBySqlNode>;
    (yyval.orderby_unit_list)->emplace_back(*(yyvsp[0].orderby_unit));
    delete (yyvsp[0].orderby_unit);
	}
#line 2962 "yacc_sql.cpp"
    break;

  case 129:
#line 1104 "yacc_sql.y"
        {
    (yyvsp[0].orderby_unit_list)->emplace_back(*(yyvsp[-2].orderby_unit));
    (yyval.orderby_unit_list) = (yyvsp[0].orderby_unit_list);
    delete (yyvsp[-2].orderby_unit);
	}
#line 2972 "yacc_sql.cpp"
    break;

  case 130:
#line 1111 "yacc_sql.y"
                    {
   (yyval.orderby_unit_list) = nullptr;
  }
#line 2980 "yacc_sql.cpp"
    break;

  case 131:
#line 1115 "yacc_sql.y"
        {
      (yyval.orderby_unit_list) = (yyvsp[0].orderby_unit_list);
      std::reverse((yyval.orderby_unit_list)->begin(),(yyval.orderby_unit_list)->end());
	}
#line 2989 "yacc_sql.cpp"
    break;

  case 132:
#line 1121 "yacc_sql.y"
                    {
   (yyval.expression_list) = nullptr;
  }
#line 2997 "yacc_sql.cpp"
    break;

  case 133:
#line 1125 "yacc_sql.y"
        {
      (yyval.expression_list) = (yyvsp[0].expression_list);
      std::reverse((yyval.expression_list)->begin(),(yyval.expression_list)->end());
	}
#line 3006 "yacc_sql.cpp"
    break;

  case 134:
#line 1131 "yacc_sql.y"
              {
   (yyval.expression) = nullptr;
  }
#line 3014 "yacc_sql.cpp"
    break;

  case 135:
#line 1135 "yacc_sql.y"
        {
      (yyval.expression) = (yyvsp[0].expression);
	}
#line 3022 "yacc_sql.cpp"
    break;

  case 136:
#line 1141 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3028 "yacc_sql.cpp"
    break;

  case 137:
#line 1142 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3034 "yacc_sql.cpp"
    break;

  case 138:
#line 1143 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3040 "yacc_sql.cpp"
    break;

  case 139:
#line 1144 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3046 "yacc_sql.cpp"
    break;

  case 140:
#line 1145 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3052 "yacc_sql.cpp"
    break;

  case 141:
#line 1146 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3058 "yacc_sql.cpp"
    break;

  case 142:
#line 1147 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP;}
#line 3064 "yacc_sql.cpp"
    break;

  case 143:
#line 1148 "yacc_sql.y"
               {(yyval.comp) = NOT_LIKE_OP;}
#line 3070 "yacc_sql.cpp"
    break;

  case 144:
#line 1149 "yacc_sql.y"
         { (yyval.comp) = IN_OP; }
#line 3076 "yacc_sql.cpp"
    break;

  case 145:
#line 1150 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_OP; }
#line 3082 "yacc_sql.cpp"
    break;

  case 146:
#line 1154 "yacc_sql.y"
           { (yyval.comp) = EXISTS_OP; }
#line 3088 "yacc_sql.cpp"
    break;

  case 147:
#line 1155 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS_OP; }
#line 3094 "yacc_sql.cpp"
    break;

  case 148:
#line 1160 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3108 "yacc_sql.cpp"
    break;

  case 149:
#line 1173 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3117 "yacc_sql.cpp"
    break;

  case 150:
#line 1181 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3129 "yacc_sql.cpp"
    break;


#line 3133 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1193 "yacc_sql.y"

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
