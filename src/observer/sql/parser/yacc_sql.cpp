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


#line 114 "yacc_sql.cpp"

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
    CALC = 264,
    SELECT = 265,
    DESC = 266,
    SHOW = 267,
    SYNC = 268,
    INSERT = 269,
    DELETE = 270,
    UNIQUE = 271,
    UPDATE = 272,
    INNER = 273,
    JOIN = 274,
    LBRACE = 275,
    RBRACE = 276,
    COMMA = 277,
    TRX_BEGIN = 278,
    TRX_COMMIT = 279,
    TRX_ROLLBACK = 280,
    INT_T = 281,
    STRING_T = 282,
    FLOAT_T = 283,
    DATE_T = 284,
    HELP = 285,
    EXIT = 286,
    DOT = 287,
    INTO = 288,
    VALUES = 289,
    FROM = 290,
    WHERE = 291,
    AND = 292,
    SET = 293,
    ON = 294,
    LOAD = 295,
    DATA = 296,
    INFILE = 297,
    EXPLAIN = 298,
    EQ = 299,
    LT = 300,
    GT = 301,
    LE = 302,
    GE = 303,
    NE = 304,
    LIKE = 305,
    NOT = 306,
    NULL_T = 307,
    IS = 308,
    INS = 309,
    EXISTSS = 310,
    MAX = 311,
    MIN = 312,
    COUNT = 313,
    AVG = 314,
    SUM = 315,
    ASC = 316,
    ORDER = 317,
    BY = 318,
    NUMBER = 319,
    FLOAT = 320,
    ID = 321,
    SSS = 322,
    UMINUS = 323
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 120 "yacc_sql.y"

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

#line 263 "yacc_sql.cpp"

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
#define YYFINAL  74
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   346

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  146
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  274

#define YYUNDEFTOK  2
#define YYMAXUTOK   323


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
       2,     2,    70,    68,     2,    69,     2,    71,     2,     2,
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
      65,    66,    67,    72
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   214,   214,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   245,   251,   256,   262,   268,   274,   280,
     287,   293,   301,   316,   334,   337,   349,   359,   378,   381,
     394,   403,   415,   418,   421,   426,   429,   430,   431,   432,
     435,   451,   454,   463,   474,   478,   482,   486,   494,   506,
     529,   532,   545,   558,   571,   588,   631,   634,   648,   656,
     668,   671,   679,   690,   693,   696,   746,   749,   758,   761,
     770,   778,   787,   798,   812,   813,   814,   815,   816,   820,
     830,   835,   846,   849,   852,   855,   858,   862,   865,   873,
     876,   883,   895,   900,   907,   917,   920,   934,   937,   947,
     960,   963,   967,   981,   984,   990,   993,   998,  1005,  1017,
    1029,  1041,  1053,  1065,  1077,  1089,  1101,  1112,  1123,  1134,
    1148,  1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,
    1158,  1159,  1163,  1176,  1184,  1194,  1195
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "CALC", "SELECT", "DESC", "SHOW", "SYNC", "INSERT",
  "DELETE", "UNIQUE", "UPDATE", "INNER", "JOIN", "LBRACE", "RBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "EQ",
  "LT", "GT", "LE", "GE", "NE", "LIKE", "NOT", "NULL_T", "IS", "INS",
  "EXISTSS", "MAX", "MIN", "COUNT", "AVG", "SUM", "ASC", "ORDER", "BY",
  "NUMBER", "FLOAT", "ID", "SSS", "'+'", "'-'", "'*'", "'/'", "UMINUS",
  "$accept", "commands", "command_wrapper", "exit_stmt", "help_stmt",
  "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "index_ids", "drop_index_stmt", "create_table_stmt",
  "attr_def_list", "attr_def", "nullable", "number", "type", "insert_stmt",
  "value_list", "value", "delete_stmt", "update_stmt", "update_pair_list",
  "select_stmt", "order_by", "order_attr", "order_attr_list",
  "order_policy", "AGG_FUNC", "AGGR_ATTR_LIST", "AGGR_TYPE", "calc_stmt",
  "expression_list", "expression", "select_attr", "rel_attr", "attr_list",
  "rel_list", "inner_join_conditions", "where", "condition_list",
  "condition", "comp_op", "load_data_stmt", "explain_stmt",
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
     315,   316,   317,   318,   319,   320,   321,   322,    43,    45,
      42,    47,   323
};
# endif

#define YYPACT_NINF (-254)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-116)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     222,   108,    44,    34,   224,   -50,    11,  -254,    -8,    30,
      19,  -254,  -254,  -254,  -254,  -254,    27,    68,   222,    28,
      64,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,
    -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,
    -254,    46,    49,   115,    60,    69,    34,  -254,  -254,  -254,
    -254,    34,  -254,  -254,     1,  -254,  -254,  -254,  -254,  -254,
     104,  -254,  -254,   114,   109,   121,  -254,  -254,    71,    84,
     147,   143,   146,  -254,  -254,  -254,  -254,   170,   153,   132,
    -254,   160,   -13,  -254,    34,    34,    34,    34,    34,   134,
      24,   154,   102,  -254,   175,   176,     2,   -38,   152,   155,
     162,   174,   164,  -254,  -254,    26,    26,  -254,  -254,  -254,
     172,     9,    24,   223,    18,   121,   228,   117,  -254,   183,
     206,   176,  -254,   218,   214,   233,   236,   191,  -254,    21,
     192,  -254,  -254,  -254,   242,   200,   176,  -254,   -38,   251,
     263,  -254,   230,   229,    54,  -254,   268,  -254,  -254,  -254,
    -254,    -7,   155,   254,   219,   266,   221,  -254,    24,   225,
      18,   226,   100,  -254,  -254,  -254,  -254,  -254,  -254,  -254,
     -16,    53,  -254,  -254,   137,    77,   158,    89,    75,   279,
       2,   227,   239,   240,  -254,  -254,   233,  -254,   293,   253,
      24,  -254,   281,  -254,   258,  -254,   -38,   301,   100,  -254,
    -254,  -254,   271,  -254,    -3,  -254,  -254,   272,  -254,    -3,
    -254,  -254,  -254,   279,     2,   304,  -254,  -254,  -254,   305,
    -254,  -254,   261,   307,   293,  -254,   212,    18,   264,   100,
    -254,  -254,  -254,   308,   310,  -254,   311,   312,   313,  -254,
       2,    80,   293,  -254,   314,   299,  -254,    -2,    10,  -254,
    -254,  -254,  -254,  -254,     2,  -254,  -254,  -254,  -254,    89,
    -254,   273,  -254,  -254,   264,    10,  -254,  -254,  -254,    -1,
      10,  -254,  -254,  -254
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    76,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     145,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,    56,    54,    55,
      57,     0,    98,    89,    90,    84,    85,    88,    86,    87,
     102,   100,   104,     0,     0,   105,    31,    30,     0,     0,
       0,     0,     0,   143,     1,   146,     2,     0,     0,     0,
      29,     0,     0,    97,     0,     0,     0,     0,     0,     0,
      78,     0,    76,   101,     0,   113,    60,     0,     0,     0,
       0,     0,     0,    96,    91,    92,    93,    94,    95,   103,
       0,    78,    78,     0,   107,   105,     0,    76,    58,     0,
       0,   113,   144,     0,     0,    38,     0,     0,    36,    78,
       0,    79,    80,    77,     0,     0,   113,   106,     0,     0,
       0,   114,   116,     0,     0,    59,     0,    46,    47,    48,
      49,    42,     0,     0,     0,     0,     0,    81,    78,     0,
     107,    66,    51,   130,   131,   132,   133,   134,   135,   136,
       0,     0,   138,   140,    76,     0,    76,    76,     0,     0,
      60,     0,     0,     0,    43,    41,    38,    37,    34,     0,
      78,    82,   110,   108,     0,    65,     0,     0,    51,   137,
     139,   141,     0,   124,    51,   119,   121,     0,   122,    51,
     118,   120,   117,     0,    60,     0,    63,   142,    45,     0,
      44,    39,     0,     0,    34,    83,    76,   107,     0,    51,
      50,    52,   125,     0,     0,   123,     0,     0,     0,    64,
      60,    42,    34,    32,     0,   111,   109,    73,    70,    53,
     126,   127,   128,   129,    60,    61,    40,    35,    33,    76,
      75,     0,    74,    68,     0,    70,    67,    62,   112,    73,
      70,    71,    69,    72
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -254,  -254,   319,  -254,  -254,  -254,  -254,  -254,  -254,  -254,
    -254,  -254,  -254,  -209,  -254,  -254,   156,   186,    99,  -254,
    -254,  -254,   -18,   -96,  -254,  -254,  -177,    50,  -254,  -217,
    -253,    72,  -254,  -107,  -254,  -254,   259,   120,  -254,    -4,
     231,  -154,  -254,  -101,  -175,   118,   205,  -254,  -254,  -254,
    -254
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   223,    31,    32,   153,   125,   185,   219,
     151,    33,   197,    52,    34,    35,   121,    36,   195,   265,
     266,   263,    62,   113,    63,    37,    53,    54,    64,   140,
      93,   136,   227,   118,   141,   142,   174,    38,    39,    40,
      76
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      65,   122,   212,   216,   131,   132,   193,     4,   103,   260,
     260,   248,   271,   182,    47,   244,    66,   273,    67,   196,
     145,   139,   157,    84,   119,    68,    48,    49,    74,    50,
     261,   110,   264,   257,   199,   161,   134,   239,   200,   201,
     135,   130,   162,   110,   183,   184,   110,   270,   180,    47,
      44,   191,    45,   156,    46,    85,    86,    87,    88,   262,
     262,    48,    49,   255,    50,    69,   198,    75,   120,    85,
      86,    87,    88,   246,   179,   111,   247,   267,   205,   112,
     210,   139,   214,   225,   268,    70,    47,   111,   115,  -115,
     111,   112,  -115,    71,   112,   213,    87,    88,    48,    49,
     229,    50,   198,    51,   202,   203,    47,  -115,   198,    72,
    -115,  -115,    77,   198,    41,    78,    42,  -115,    48,    49,
    -115,    50,   196,    79,    43,  -115,    80,    47,   207,   208,
     139,   183,   184,   198,    90,    81,    89,    94,  -115,    48,
      49,    47,    50,    92,    91,    55,    56,    57,    58,    59,
      95,  -115,    47,    48,    49,    60,    50,   204,    55,    56,
      57,    58,    59,   139,    48,    49,    82,    50,    60,    47,
     206,    83,   211,    55,    56,    57,    58,    59,   209,  -115,
     231,    48,    49,    60,    50,    96,   233,    97,    98,    47,
      99,   236,   100,    55,    56,    57,    58,    59,   101,   102,
     109,    48,    49,    60,    50,   105,   106,   107,   108,   116,
      47,   249,   117,   127,    55,    56,    57,    58,    59,   123,
     114,   124,    48,    49,    60,    50,     1,     2,   126,   215,
     128,     3,     4,     5,     6,     7,     8,     9,   129,    10,
     147,   148,   149,   150,   133,    11,    12,    13,   138,   143,
     144,   146,    14,    15,   234,   152,   154,   155,   158,   237,
      16,   159,    17,   238,    47,    18,   160,   177,    55,    56,
      57,    58,    59,   178,   181,   187,    48,    49,    60,    50,
      55,    56,    57,    58,    59,   188,   189,   190,   194,     4,
      60,   192,   220,   217,    61,   163,   164,   165,   166,   167,
     168,   169,   170,   218,   171,   172,   173,   163,   164,   165,
     166,   167,   168,   169,   170,   222,   175,   172,   173,   224,
     226,   228,   230,   232,   235,   240,   241,   242,   243,   250,
     247,   251,   252,   253,   254,   258,   259,    73,   186,   269,
     256,   272,   221,   104,   245,   176,   137
};

static const yytype_int16 yycheck[] =
{
       4,    97,   177,   180,   111,   112,   160,    10,    21,    11,
      11,   228,   265,    20,    52,   224,    66,   270,     7,    22,
     121,   117,   129,    22,    22,    33,    64,    65,     0,    67,
      32,    22,    22,   242,    50,   136,    18,   214,    54,    55,
      22,    32,   138,    22,    51,    52,    22,   264,   144,    52,
       6,   158,     8,    32,    20,    68,    69,    70,    71,    61,
      61,    64,    65,   240,    67,    35,   162,     3,    66,    68,
      69,    70,    71,   227,    20,    66,    66,   254,   174,    70,
     176,   177,   178,   190,   259,    66,    52,    66,    92,     0,
      66,    70,     3,    66,    70,    20,    70,    71,    64,    65,
     196,    67,   198,    69,    51,    52,    52,    18,   204,    41,
      21,    22,    66,   209,     6,    66,     8,     0,    64,    65,
       3,    67,    22,     8,    16,    36,    66,    52,    51,    52,
     226,    51,    52,   229,    20,    66,    32,    66,    21,    64,
      65,    52,    67,    22,    35,    56,    57,    58,    59,    60,
      66,    62,    52,    64,    65,    66,    67,    20,    56,    57,
      58,    59,    60,   259,    64,    65,    46,    67,    66,    52,
     174,    51,   176,    56,    57,    58,    59,    60,    20,    62,
     198,    64,    65,    66,    67,    38,   204,    44,    42,    52,
      20,   209,    39,    56,    57,    58,    59,    60,    66,    39,
      66,    64,    65,    66,    67,    85,    86,    87,    88,    34,
      52,   229,    36,    39,    56,    57,    58,    59,    60,    67,
      66,    66,    64,    65,    66,    67,     4,     5,    66,   179,
      66,     9,    10,    11,    12,    13,    14,    15,    66,    17,
      26,    27,    28,    29,    21,    23,    24,    25,    20,    66,
      44,    33,    30,    31,   204,    22,    20,    66,    66,   209,
      38,    19,    40,   213,    52,    43,    66,    37,    56,    57,
      58,    59,    60,    44,     6,    21,    64,    65,    66,    67,
      56,    57,    58,    59,    60,    66,    20,    66,    62,    10,
      66,    66,    52,    66,    70,    44,    45,    46,    47,    48,
      49,    50,    51,    64,    53,    54,    55,    44,    45,    46,
      47,    48,    49,    50,    51,    22,    53,    54,    55,    66,
      39,    63,    21,    52,    52,    21,    21,    66,    21,    21,
      66,    21,    21,    21,    21,    21,    37,    18,   152,    66,
     241,   269,   186,    84,   226,   140,   115
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      17,    23,    24,    25,    30,    31,    38,    40,    43,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    87,    88,    94,    97,    98,   100,   108,   120,   121,
     122,     6,     8,    16,     6,     8,    20,    52,    64,    65,
      67,    69,    96,   109,   110,    56,    57,    58,    59,    60,
      66,    70,   105,   107,   111,   112,    66,     7,    33,    35,
      66,    66,    41,    75,     0,     3,   123,    66,    66,     8,
      66,    66,   110,   110,    22,    68,    69,    70,    71,    32,
      20,    35,    22,   113,    66,    66,    38,    44,    42,    20,
      39,    66,    39,    21,   109,   110,   110,   110,   110,    66,
      22,    66,    70,   106,    66,   112,    34,    36,   116,    22,
      66,    99,    96,    67,    66,    90,    66,    39,    66,    66,
      32,   106,   106,    21,    18,    22,   114,   113,    20,    96,
     112,   117,   118,    66,    44,   116,    33,    26,    27,    28,
      29,    93,    22,    89,    20,    66,    32,   106,    66,    19,
      66,   116,    96,    44,    45,    46,    47,    48,    49,    50,
      51,    53,    54,    55,   119,    53,   119,    37,    44,    20,
      96,     6,    20,    51,    52,    91,    90,    21,    66,    20,
      66,   106,    66,   114,    62,   101,    22,    95,    96,    50,
      54,    55,    51,    52,    20,    96,   112,    51,    52,    20,
      96,   112,   117,    20,    96,   100,    99,    66,    64,    92,
      52,    89,    22,    86,    66,   106,    39,   115,    63,    96,
      21,    95,    52,    95,   100,    52,    95,   100,   100,    99,
      21,    21,    66,    21,    86,   118,   114,    66,   102,    95,
      21,    21,    21,    21,    21,    99,    91,    86,    21,    37,
      11,    32,    61,   104,    22,   102,   103,    99,   117,    66,
     102,   103,   104,   103
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    73,    74,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    85,    86,    86,    87,    88,    89,    89,
      90,    90,    91,    91,    91,    92,    93,    93,    93,    93,
      94,    95,    95,    95,    96,    96,    96,    96,    97,    98,
      99,    99,    99,    99,    99,   100,   101,   101,   102,   102,
     103,   103,   103,   104,   104,   104,   105,   105,   106,   106,
     106,   106,   106,   106,   107,   107,   107,   107,   107,   108,
     109,   109,   110,   110,   110,   110,   110,   110,   110,   111,
     111,   111,   112,   112,   112,   113,   113,   114,   114,   114,
     115,   115,   115,   116,   116,   117,   117,   117,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   120,   121,   122,   123,   123
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     9,    10,     0,     3,     5,     7,     0,     3,
       6,     3,     0,     1,     2,     1,     1,     1,     1,     1,
       8,     0,     2,     3,     1,     1,     1,     1,     4,     5,
       0,     6,     7,     4,     5,     7,     0,     4,     2,     4,
       0,     2,     3,     0,     1,     1,     0,     4,     0,     2,
       2,     3,     4,     5,     1,     1,     1,     1,     1,     2,
       1,     3,     3,     3,     3,     3,     3,     2,     1,     0,
       1,     2,     1,     3,     1,     0,     3,     0,     3,     5,
       0,     2,     4,     0,     2,     0,     1,     3,     3,     3,
       3,     3,     3,     4,     3,     4,     5,     5,     5,     5,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     2,     7,     2,     4,     0,     1
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
#line 215 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1785 "yacc_sql.cpp"
    break;

  case 23:
#line 245 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1794 "yacc_sql.cpp"
    break;

  case 24:
#line 251 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1802 "yacc_sql.cpp"
    break;

  case 25:
#line 256 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1810 "yacc_sql.cpp"
    break;

  case 26:
#line 262 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1818 "yacc_sql.cpp"
    break;

  case 27:
#line 268 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1826 "yacc_sql.cpp"
    break;

  case 28:
#line 274 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1834 "yacc_sql.cpp"
    break;

  case 29:
#line 280 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1844 "yacc_sql.cpp"
    break;

  case 30:
#line 287 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1852 "yacc_sql.cpp"
    break;

  case 31:
#line 293 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1862 "yacc_sql.cpp"
    break;

  case 32:
#line 302 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      // create_index.attribute_name = $7;
      create_index.unique = 0;
      if ((yyvsp[-1].index_attribute_names) != nullptr) {
        create_index.attribute_names.swap(*(yyvsp[-1].index_attribute_names));
      }
      create_index.attribute_names.push_back((yyvsp[-2].string));
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 1882 "yacc_sql.cpp"
    break;

  case 33:
#line 317 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      create_index.unique = 1;
      if ((yyvsp[-1].index_attribute_names) != nullptr) {
        create_index.attribute_names.swap(*(yyvsp[-1].index_attribute_names));
      }
      create_index.attribute_names.push_back((yyvsp[-2].string));
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 1901 "yacc_sql.cpp"
    break;

  case 34:
#line 334 "yacc_sql.y"
                {
        (yyval.index_attribute_names) = nullptr;
    }
#line 1909 "yacc_sql.cpp"
    break;

  case 35:
#line 337 "yacc_sql.y"
                         {
        if((yyvsp[0].index_attribute_names) == nullptr){
            (yyval.index_attribute_names) = new std::vector<std::string>();
        } else {
            (yyval.index_attribute_names) = (yyvsp[0].index_attribute_names);
        }
        (yyval.index_attribute_names)->push_back((yyvsp[-1].string));
        free((yyvsp[-1].string));
    }
#line 1923 "yacc_sql.cpp"
    break;

  case 36:
#line 350 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1935 "yacc_sql.cpp"
    break;

  case 37:
#line 360 "yacc_sql.y"
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
#line 1955 "yacc_sql.cpp"
    break;

  case 38:
#line 378 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1963 "yacc_sql.cpp"
    break;

  case 39:
#line 382 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1977 "yacc_sql.cpp"
    break;

  case 40:
#line 395 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->allowNull = (yyvsp[0].number);
      free((yyvsp[-5].string));
    }
#line 1990 "yacc_sql.cpp"
    break;

  case 41:
#line 404 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->allowNull = (yyvsp[0].number);
      free((yyvsp[-2].string));
    }
#line 2003 "yacc_sql.cpp"
    break;

  case 42:
#line 415 "yacc_sql.y"
        {
        (yyval.number) = 1;
    }
#line 2011 "yacc_sql.cpp"
    break;

  case 43:
#line 418 "yacc_sql.y"
             {
        (yyval.number) = 1;
    }
#line 2019 "yacc_sql.cpp"
    break;

  case 44:
#line 421 "yacc_sql.y"
                 {
        (yyval.number) = 0;
    }
#line 2027 "yacc_sql.cpp"
    break;

  case 45:
#line 426 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2033 "yacc_sql.cpp"
    break;

  case 46:
#line 429 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2039 "yacc_sql.cpp"
    break;

  case 47:
#line 430 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2045 "yacc_sql.cpp"
    break;

  case 48:
#line 431 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2051 "yacc_sql.cpp"
    break;

  case 49:
#line 432 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2057 "yacc_sql.cpp"
    break;

  case 50:
#line 436 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 2073 "yacc_sql.cpp"
    break;

  case 51:
#line 451 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2081 "yacc_sql.cpp"
    break;

  case 52:
#line 454 "yacc_sql.y"
                       {
        if ((yyvsp[0].value_list) != nullptr) {
            (yyval.value_list) = (yyvsp[0].value_list);
        } else {
            (yyval.value_list) = new std::vector<Value>;
        }
        (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
        delete (yyvsp[-1].value);
    }
#line 2095 "yacc_sql.cpp"
    break;

  case 53:
#line 463 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2109 "yacc_sql.cpp"
    break;

  case 54:
#line 474 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2118 "yacc_sql.cpp"
    break;

  case 55:
#line 478 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2127 "yacc_sql.cpp"
    break;

  case 56:
#line 482 "yacc_sql.y"
            {
      (yyval.value) = new Value(0);
      (yyval.value) -> set_isNull(true);
    }
#line 2136 "yacc_sql.cpp"
    break;

  case 57:
#line 486 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2146 "yacc_sql.cpp"
    break;

  case 58:
#line 495 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2160 "yacc_sql.cpp"
    break;

  case 59:
#line 507 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);

      if ((yyvsp[-1].update_list) != nullptr) {
        for (std::pair<std::string,UpdateValueNode>& pair_node : *(yyvsp[-1].update_list)) {
          (yyval.sql_node)->update.attribute_name.push_back(pair_node.first);
          (yyval.sql_node)->update.value.push_back(pair_node.second);
        }
      }
    
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-3].string));
      free((yyvsp[-1].update_list));
    }
#line 2183 "yacc_sql.cpp"
    break;

  case 60:
#line 529 "yacc_sql.y"
    {
        (yyval.update_list) = nullptr;
    }
#line 2191 "yacc_sql.cpp"
    break;

  case 61:
#line 532 "yacc_sql.y"
                                                       {
        if((yyvsp[0].update_list) == nullptr) {
            (yyval.update_list) = new std::vector<std::pair<std::string,UpdateValueNode>>();
        } else {
            (yyval.update_list) = (yyvsp[0].update_list);
        }
        UpdateValueNode updNode;
        updNode.isSubQuery = 1;
        updNode.select = (yyvsp[-2].sql_node)->selection;
        (yyval.update_list)->emplace_back((yyvsp[-5].string), updNode);
        free((yyvsp[-5].string));
        free((yyvsp[-2].sql_node));
    }
#line 2209 "yacc_sql.cpp"
    break;

  case 62:
#line 545 "yacc_sql.y"
                                                            {
        if((yyvsp[0].update_list) == nullptr) {
            (yyval.update_list) = new std::vector<std::pair<std::string,UpdateValueNode>>();
        } else {
            (yyval.update_list) = (yyvsp[0].update_list);
        }
        UpdateValueNode updNode;
        updNode.isSubQuery = 1;
        updNode.select = (yyvsp[-2].sql_node)->selection;
        (yyval.update_list)->emplace_back((yyvsp[-5].string), updNode);
        free((yyvsp[-5].string));
        free((yyvsp[-2].sql_node));
    }
#line 2227 "yacc_sql.cpp"
    break;

  case 63:
#line 558 "yacc_sql.y"
                                   {
        if((yyvsp[0].update_list) == nullptr) {
            (yyval.update_list) = new std::vector<std::pair<std::string,UpdateValueNode>>();
        } else {
            (yyval.update_list) = (yyvsp[0].update_list);
        }
        UpdateValueNode updNode;
        updNode.isSubQuery = 0;
        updNode.value = *(yyvsp[-1].value);
        (yyval.update_list)->emplace_back((yyvsp[-3].string),updNode);
        free((yyvsp[-3].string));
        free((yyvsp[-1].value));
    }
#line 2245 "yacc_sql.cpp"
    break;

  case 64:
#line 571 "yacc_sql.y"
                                         {
        if((yyvsp[0].update_list) == nullptr){
            (yyval.update_list) = new std::vector<std::pair<std::string,UpdateValueNode>>();
        } else {
            (yyval.update_list) = (yyvsp[0].update_list);
        }
        UpdateValueNode updNode;
        updNode.isSubQuery = 0;
        updNode.value = *(yyvsp[-1].value);
        (yyval.update_list)->emplace_back((yyvsp[-3].string),updNode);
        free((yyvsp[-3].string));
        free((yyvsp[-1].value));
    }
#line 2263 "yacc_sql.cpp"
    break;

  case 65:
#line 589 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-5].rel_attr_list) != nullptr) {
        std::vector<RelAttrSqlNode> realAttr;
        std::vector<AggrNode> aggrs;
        for (RelAttrSqlNode& relAttrSqlNode : *(yyvsp[-5].rel_attr_list)) {
            if(relAttrSqlNode.is_aggr){
                aggrs.push_back(relAttrSqlNode.aggrNode);
            }else{
                realAttr.push_back(relAttrSqlNode);
            }
        }
        (yyval.sql_node)->selection.attributes.swap(realAttr);
        reverse(aggrs.begin(),aggrs.end());
        (yyval.sql_node)->selection.aggrs.swap(aggrs);
        delete (yyvsp[-5].rel_attr_list);
      }
      
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-3].string));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }
      if ((yyvsp[0].orderby_list) != nullptr) {
        (yyval.sql_node)->selection.order_bys.swap(*(yyvsp[0].orderby_list));
        delete (yyvsp[0].orderby_list);
      }
      if ((yyvsp[-2].relation_list) != nullptr){
        for (JoinSqlNode& join_node : *(yyvsp[-2].relation_list)) {
          (yyval.sql_node)->selection.relations.push_back(join_node.table_name);
          for(ConditionSqlNode& condition: join_node.conditions){
              (yyval.sql_node)->selection.inner_join_conditions.push_back(condition);
          }
        }
      }
      free((yyvsp[-3].string));
    }
#line 2307 "yacc_sql.cpp"
    break;

  case 66:
#line 631 "yacc_sql.y"
                {
        (yyval.orderby_list) = nullptr;
    }
#line 2315 "yacc_sql.cpp"
    break;

  case 67:
#line 634 "yacc_sql.y"
                                          {
        if ((yyvsp[0].orderby_list) == nullptr){
            (yyval.orderby_list) = new std::vector<OrderBySqlNode>();
        }else {
            (yyval.orderby_list) = (yyvsp[0].orderby_list);
        }
        std::reverse((yyval.orderby_list)->begin(),(yyval.orderby_list)->end());
        (yyval.orderby_list)->insert((yyval.orderby_list)->begin(), *(yyvsp[-1].order_node));
        //$$ -> push_back(*$3);
        free((yyvsp[-1].order_node));
    }
#line 2331 "yacc_sql.cpp"
    break;

  case 68:
#line 648 "yacc_sql.y"
                    {
        OrderBySqlNode* order_by = new OrderBySqlNode;
        order_by->relation = "";
        order_by->attribute = (yyvsp[-1].string);
        order_by->orderPolicy = (yyvsp[0].order_policy);
        free((yyvsp[-1].string));
        (yyval.order_node) = order_by;
    }
#line 2344 "yacc_sql.cpp"
    break;

  case 69:
#line 656 "yacc_sql.y"
                             {
        OrderBySqlNode* order_by = new OrderBySqlNode;
        order_by->relation = (yyvsp[-3].string);
        order_by->attribute = (yyvsp[-1].string);
        order_by->orderPolicy = (yyvsp[0].order_policy);
        free((yyvsp[-3].string));
        free((yyvsp[-1].string));
        (yyval.order_node) = order_by;
    }
#line 2358 "yacc_sql.cpp"
    break;

  case 70:
#line 668 "yacc_sql.y"
                {
        (yyval.orderby_list) = nullptr;
    }
#line 2366 "yacc_sql.cpp"
    break;

  case 71:
#line 671 "yacc_sql.y"
                                 {
        if ((yyvsp[0].orderby_list) == nullptr) {
            (yyval.orderby_list) = new std::vector<OrderBySqlNode>();
        } else {
            (yyval.orderby_list) = (yyvsp[0].orderby_list);
        }
        (yyval.orderby_list) -> push_back(*(yyvsp[-1].order_node));
    }
#line 2379 "yacc_sql.cpp"
    break;

  case 72:
#line 679 "yacc_sql.y"
                                      {
        if((yyvsp[0].orderby_list) == nullptr) {
            (yyval.orderby_list) = new std::vector<OrderBySqlNode>();
        }else {
            (yyval.orderby_list) = (yyvsp[0].orderby_list);
        }
        (yyval.orderby_list) -> push_back(*(yyvsp[-1].order_node));
    }
#line 2392 "yacc_sql.cpp"
    break;

  case 73:
#line 690 "yacc_sql.y"
                {
        (yyval.order_policy) = ORDER_ASC;
    }
#line 2400 "yacc_sql.cpp"
    break;

  case 74:
#line 693 "yacc_sql.y"
          {
        (yyval.order_policy) = ORDER_ASC;
    }
#line 2408 "yacc_sql.cpp"
    break;

  case 75:
#line 696 "yacc_sql.y"
           {
        (yyval.order_policy) = ORDER_DESC;
    }
#line 2416 "yacc_sql.cpp"
    break;

  case 76:
#line 746 "yacc_sql.y"
         {
        (yyval.aggr_node) = nullptr;
    }
#line 2424 "yacc_sql.cpp"
    break;

  case 77:
#line 749 "yacc_sql.y"
                                             {
        (yyval.aggr_node) = new AggrNode();
        (yyval.aggr_node)->relation = "";
        (yyval.aggr_node)->attributes.swap(*(yyvsp[-1].aggr_attribute_names));
        (yyval.aggr_node)->type = (yyvsp[-3].aggr_type);
    }
#line 2435 "yacc_sql.cpp"
    break;

  case 78:
#line 758 "yacc_sql.y"
          {
        (yyval.aggr_attribute_names) = new std::vector<std::string>();
    }
#line 2443 "yacc_sql.cpp"
    break;

  case 79:
#line 761 "yacc_sql.y"
                        {
        if((yyvsp[0].aggr_attribute_names)==nullptr){
            (yyval.aggr_attribute_names) = new std::vector<std::string>();
        }else{
            (yyval.aggr_attribute_names) = (yyvsp[0].aggr_attribute_names);
        }
        
        (yyval.aggr_attribute_names)->push_back((yyvsp[-1].string));
    }
#line 2457 "yacc_sql.cpp"
    break;

  case 80:
#line 770 "yacc_sql.y"
                         {
        if((yyvsp[0].aggr_attribute_names)==nullptr){
            (yyval.aggr_attribute_names) = new std::vector<std::string>();
        }else{
            (yyval.aggr_attribute_names) = (yyvsp[0].aggr_attribute_names);
        }
        (yyval.aggr_attribute_names)->push_back("*");
    }
#line 2470 "yacc_sql.cpp"
    break;

  case 81:
#line 778 "yacc_sql.y"
                              {
        if((yyvsp[0].aggr_attribute_names) != nullptr) {
            (yyval.aggr_attribute_names) = (yyvsp[0].aggr_attribute_names);
        }else{
            (yyval.aggr_attribute_names) = new std::vector<std::string>();
        }
        (yyval.aggr_attribute_names)->push_back((yyvsp[-1].string));
        free((yyvsp[-1].string));
    }
#line 2484 "yacc_sql.cpp"
    break;

  case 82:
#line 787 "yacc_sql.y"
                               {
        if((yyvsp[0].aggr_attribute_names) != nullptr) {
            (yyval.aggr_attribute_names) = (yyvsp[0].aggr_attribute_names);
        }else{
            (yyval.aggr_attribute_names) = new std::vector<std::string>();
        }
        std::string str = std::string((yyvsp[-3].string)) + "." + std::string((yyvsp[-1].string));
        (yyval.aggr_attribute_names)->push_back(str);
        free((yyvsp[-3].string));
        free((yyvsp[-1].string));
    }
#line 2500 "yacc_sql.cpp"
    break;

  case 83:
#line 798 "yacc_sql.y"
                                     {
        if ((yyvsp[0].aggr_attribute_names) != nullptr) {
            (yyval.aggr_attribute_names) = (yyvsp[0].aggr_attribute_names);
        }else {
            (yyval.aggr_attribute_names) = new std::vector<std::string>();
        }
        std::string str = std::string((yyvsp[-3].string)) + "." + std::string((yyvsp[-1].string));
        (yyval.aggr_attribute_names)->push_back(str);
        free((yyvsp[-3].string));
        free((yyvsp[-1].string));
    }
#line 2516 "yacc_sql.cpp"
    break;

  case 84:
#line 812 "yacc_sql.y"
            { (yyval.aggr_type) = MAXS; }
#line 2522 "yacc_sql.cpp"
    break;

  case 85:
#line 813 "yacc_sql.y"
            { (yyval.aggr_type) = MINS; }
#line 2528 "yacc_sql.cpp"
    break;

  case 86:
#line 814 "yacc_sql.y"
            { (yyval.aggr_type) = AVGS; }
#line 2534 "yacc_sql.cpp"
    break;

  case 87:
#line 815 "yacc_sql.y"
            { (yyval.aggr_type) = SUMS; }
#line 2540 "yacc_sql.cpp"
    break;

  case 88:
#line 816 "yacc_sql.y"
            { (yyval.aggr_type) = COUNTS; }
#line 2546 "yacc_sql.cpp"
    break;

  case 89:
#line 821 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2557 "yacc_sql.cpp"
    break;

  case 90:
#line 831 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2566 "yacc_sql.cpp"
    break;

  case 91:
#line 836 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2579 "yacc_sql.cpp"
    break;

  case 92:
#line 846 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2587 "yacc_sql.cpp"
    break;

  case 93:
#line 849 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2595 "yacc_sql.cpp"
    break;

  case 94:
#line 852 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2603 "yacc_sql.cpp"
    break;

  case 95:
#line 855 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2611 "yacc_sql.cpp"
    break;

  case 96:
#line 858 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 97:
#line 862 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 98:
#line 865 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2638 "yacc_sql.cpp"
    break;

  case 99:
#line 873 "yacc_sql.y"
          {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2646 "yacc_sql.cpp"
    break;

  case 100:
#line 876 "yacc_sql.y"
         {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2658 "yacc_sql.cpp"
    break;

  case 101:
#line 883 "yacc_sql.y"
                         {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2672 "yacc_sql.cpp"
    break;

  case 102:
#line 895 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2682 "yacc_sql.cpp"
    break;

  case 103:
#line 900 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 104:
#line 907 "yacc_sql.y"
               {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr) -> is_aggr = 1;
      (yyval.rel_attr) -> aggrNode = *(yyvsp[0].aggr_node);
      free((yyvsp[0].aggr_node));
    }
#line 2705 "yacc_sql.cpp"
    break;

  case 105:
#line 917 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2713 "yacc_sql.cpp"
    break;

  case 106:
#line 920 "yacc_sql.y"
                               {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2728 "yacc_sql.cpp"
    break;

  case 107:
#line 934 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2736 "yacc_sql.cpp"
    break;

  case 108:
#line 937 "yacc_sql.y"
                        {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<JoinSqlNode>;
      }

      (yyval.relation_list)->emplace_back((yyvsp[-1].string), std::vector<ConditionSqlNode>());
      free((yyvsp[-1].string));
    }
#line 2751 "yacc_sql.cpp"
    break;

  case 109:
#line 947 "yacc_sql.y"
                                                   {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<JoinSqlNode>;
      }

      (yyval.relation_list)->emplace_back((yyvsp[-2].string),*(yyvsp[-1].condition_list));
      free((yyvsp[-2].string));
    }
#line 2766 "yacc_sql.cpp"
    break;

  case 110:
#line 960 "yacc_sql.y"
                    {
        (yyval.condition_list) = nullptr; // 或者可以使用一个空的条件列表
    }
#line 2774 "yacc_sql.cpp"
    break;

  case 111:
#line 963 "yacc_sql.y"
                       {
        (yyval.condition_list) = new std::vector<ConditionSqlNode>; // 创建一个条件列表
        (yyval.condition_list)->emplace_back(*(yyvsp[0].condition)); // 将条件添加到列表中
	}
#line 2783 "yacc_sql.cpp"
    break;

  case 112:
#line 967 "yacc_sql.y"
                                          {
        if ((yyvsp[0].condition_list) != nullptr) {
            (yyval.condition_list) = (yyvsp[0].condition_list);
        } else {
            (yyval.condition_list) = new std::vector<ConditionSqlNode>;
        }
        (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
        delete (yyvsp[-2].condition);
    }
#line 2797 "yacc_sql.cpp"
    break;

  case 113:
#line 981 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2805 "yacc_sql.cpp"
    break;

  case 114:
#line 984 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2813 "yacc_sql.cpp"
    break;

  case 115:
#line 990 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2821 "yacc_sql.cpp"
    break;

  case 116:
#line 993 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2831 "yacc_sql.cpp"
    break;

  case 117:
#line 998 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2841 "yacc_sql.cpp"
    break;

  case 118:
#line 1006 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2857 "yacc_sql.cpp"
    break;

  case 119:
#line 1018 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 2873 "yacc_sql.cpp"
    break;

  case 120:
#line 1030 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 2889 "yacc_sql.cpp"
    break;

  case 121:
#line 1042 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].rel_attr);
    }
#line 2905 "yacc_sql.cpp"
    break;

  case 122:
#line 1054 "yacc_sql.y"
    {
        (yyval.condition) = new ConditionSqlNode;
        (yyval.condition)->left_is_attr = 1;
        (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
        (yyval.condition)->right_is_attr = 0;
        (yyval.condition)->right_value = Value();
        (yyval.condition)->right_value.set_isNull(true);
        (yyval.condition)->comp = IS_COM;

        delete (yyvsp[-2].rel_attr);
    }
#line 2921 "yacc_sql.cpp"
    break;

  case 123:
#line 1066 "yacc_sql.y"
    {
        (yyval.condition) = new ConditionSqlNode;
        (yyval.condition)->left_is_attr = 1;
        (yyval.condition)->left_attr = *(yyvsp[-3].rel_attr);
        (yyval.condition)->right_is_attr = 0;
        (yyval.condition)->right_value = Value();
        (yyval.condition)->right_value.set_isNull(true);
        (yyval.condition)->comp = ISNOT_COM;

        delete (yyvsp[-3].rel_attr);
    }
#line 2937 "yacc_sql.cpp"
    break;

  case 124:
#line 1078 "yacc_sql.y"
    {
        (yyval.condition) = new ConditionSqlNode;
        (yyval.condition)->left_is_attr = 0;
        (yyval.condition)->left_value = *(yyvsp[-2].value);
        (yyval.condition)->right_is_attr = 0;
        (yyval.condition)->right_value = Value();
        (yyval.condition)->right_value.set_isNull(true);
        (yyval.condition)->comp = IS_COM;

        delete (yyvsp[-2].value);
    }
#line 2953 "yacc_sql.cpp"
    break;

  case 125:
#line 1090 "yacc_sql.y"
    {
        (yyval.condition) = new ConditionSqlNode;
        (yyval.condition)->left_is_attr = 0;
        (yyval.condition)->left_value = *(yyvsp[-3].value);
        (yyval.condition)->right_is_attr = 0;
        (yyval.condition)->right_value = Value();
        (yyval.condition)->right_value.set_isNull(true);
        (yyval.condition)->comp = ISNOT_COM;

        delete (yyvsp[-3].value);
    }
#line 2969 "yacc_sql.cpp"
    break;

  case 126:
#line 1101 "yacc_sql.y"
                                             {
        (yyval.condition) = new ConditionSqlNode;
        (yyval.condition) -> left_is_attr = 0;
        (yyval.condition) -> left_value = *(yyvsp[-4].value);
        (yyval.condition) -> right_is_attr = 0;
        (yyval.condition) -> right_is_subselect = 1;
        (yyval.condition) -> in_values.swap(*(yyvsp[-1].value_list));
        (yyval.condition) -> comp = (yyvsp[-3].comp);

        delete (yyvsp[-4].value);
    }
#line 2985 "yacc_sql.cpp"
    break;

  case 127:
#line 1112 "yacc_sql.y"
                                              {
        (yyval.condition) = new ConditionSqlNode;
        (yyval.condition) -> left_is_attr = 0;
        (yyval.condition) -> left_value = *(yyvsp[-4].value);
        (yyval.condition) -> right_is_attr = 0;
        (yyval.condition) -> right_is_subselect = 2;
        (yyval.condition) -> select = &((yyvsp[-1].sql_node) -> selection);
        (yyval.condition) -> comp = (yyvsp[-3].comp);

        delete (yyvsp[-4].value);
    }
#line 3001 "yacc_sql.cpp"
    break;

  case 128:
#line 1123 "yacc_sql.y"
                                                {
        (yyval.condition) = new ConditionSqlNode;
        (yyval.condition)->left_is_attr = 1;
        (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
        (yyval.condition)->right_is_attr = 0;
        (yyval.condition)->right_is_subselect = 1;
        (yyval.condition)->in_values.swap(*(yyvsp[-1].value_list));
        (yyval.condition)->comp = (yyvsp[-3].comp);

        delete (yyvsp[-4].rel_attr);
    }
#line 3017 "yacc_sql.cpp"
    break;

  case 129:
#line 1134 "yacc_sql.y"
                                                 {
        (yyval.condition) = new ConditionSqlNode;
        (yyval.condition) -> left_is_attr = 1;
        (yyval.condition) -> left_attr = *(yyvsp[-4].rel_attr);
        (yyval.condition) -> right_is_attr = 0;
        (yyval.condition) -> right_is_subselect = 2;
        (yyval.condition) -> select = &((yyvsp[-1].sql_node) -> selection);
        (yyval.condition) -> comp = (yyvsp[-3].comp);

        delete (yyvsp[-4].rel_attr);
    }
#line 3033 "yacc_sql.cpp"
    break;

  case 130:
#line 1148 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3039 "yacc_sql.cpp"
    break;

  case 131:
#line 1149 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3045 "yacc_sql.cpp"
    break;

  case 132:
#line 1150 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3051 "yacc_sql.cpp"
    break;

  case 133:
#line 1151 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3057 "yacc_sql.cpp"
    break;

  case 134:
#line 1152 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3063 "yacc_sql.cpp"
    break;

  case 135:
#line 1153 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3069 "yacc_sql.cpp"
    break;

  case 136:
#line 1154 "yacc_sql.y"
           { (yyval.comp) = STR_LIKE; }
#line 3075 "yacc_sql.cpp"
    break;

  case 137:
#line 1155 "yacc_sql.y"
               { (yyval.comp) = STR_NOT_LIKE; }
#line 3081 "yacc_sql.cpp"
    break;

  case 138:
#line 1156 "yacc_sql.y"
          { (yyval.comp) = IN; }
#line 3087 "yacc_sql.cpp"
    break;

  case 139:
#line 1157 "yacc_sql.y"
              { (yyval.comp) = NOT_IN; }
#line 3093 "yacc_sql.cpp"
    break;

  case 140:
#line 1158 "yacc_sql.y"
              { (yyval.comp) = EXISTS; }
#line 3099 "yacc_sql.cpp"
    break;

  case 141:
#line 1159 "yacc_sql.y"
                  { (yyval.comp) = NOT_EXISTS; }
#line 3105 "yacc_sql.cpp"
    break;

  case 142:
#line 1164 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3119 "yacc_sql.cpp"
    break;

  case 143:
#line 1177 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3128 "yacc_sql.cpp"
    break;

  case 144:
#line 1185 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3140 "yacc_sql.cpp"
    break;


#line 3144 "yacc_sql.cpp"

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
#line 1197 "yacc_sql.y"

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
