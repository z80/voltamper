/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         slice_parse
#define yylex           slice_lex
#define yyerror         slice_error
#define yydebug         slice_debug
#define yynerrs         slice_nerrs


/* Copy the first part of user declarations.  */
#line 1 "../Slice/Grammar.y" /* yacc.c:339  */


// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Slice/GrammarUtil.h>
#include <IceUtil/UUID.h>
#include <cstring>

#ifdef _MSC_VER
// I get these warnings from some bison versions:
// warning C4102: 'yyoverflowlab' : unreferenced label
#   pragma warning( disable : 4102 )
// warning C4065: switch statement contains 'default' but no 'case' labels
#   pragma warning( disable : 4065 )
#endif

using namespace std;
using namespace Slice;

void
slice_error(const char* s)
{
    // yacc and recent versions of Bison use "syntax error" instead
    // of "parse error".

    if (strcmp(s, "parse error") == 0)
    {
	unit->error("syntax error");
    }
    else
    {
	unit->error(s);
    }
}


#line 116 "Grammar.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "Grammar.tab.h".  */
#ifndef YY_SLICE_GRAMMAR_TAB_H_INCLUDED
# define YY_SLICE_GRAMMAR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int slice_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ICE_MODULE = 258,
    ICE_CLASS = 259,
    ICE_INTERFACE = 260,
    ICE_EXCEPTION = 261,
    ICE_STRUCT = 262,
    ICE_SEQUENCE = 263,
    ICE_DICTIONARY = 264,
    ICE_ENUM = 265,
    ICE_OUT = 266,
    ICE_EXTENDS = 267,
    ICE_IMPLEMENTS = 268,
    ICE_THROWS = 269,
    ICE_VOID = 270,
    ICE_BYTE = 271,
    ICE_BOOL = 272,
    ICE_SHORT = 273,
    ICE_INT = 274,
    ICE_LONG = 275,
    ICE_FLOAT = 276,
    ICE_DOUBLE = 277,
    ICE_STRING = 278,
    ICE_OBJECT = 279,
    ICE_LOCAL_OBJECT = 280,
    ICE_LOCAL = 281,
    ICE_CONST = 282,
    ICE_FALSE = 283,
    ICE_TRUE = 284,
    ICE_NONMUTATING = 285,
    ICE_IDEMPOTENT = 286,
    ICE_SCOPE_DELIMITER = 287,
    ICE_IDENTIFIER = 288,
    ICE_STRING_LITERAL = 289,
    ICE_INTEGER_LITERAL = 290,
    ICE_FLOATING_POINT_LITERAL = 291,
    ICE_IDENT_OP = 292,
    ICE_KEYWORD_OP = 293,
    ICE_METADATA_OPEN = 294,
    ICE_METADATA_CLOSE = 295,
    ICE_GLOBAL_METADATA_OPEN = 296,
    ICE_GLOBAL_METADATA_CLOSE = 297,
    BAD_CHAR = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int slice_parse (void);

#endif /* !YY_SLICE_GRAMMAR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 210 "Grammar.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   775

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  184
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  269

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,    51,     2,    48,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    44,
      49,    52,    50,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    46,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   113,   122,   127,   136,   135,   145,   144,
     156,   155,   160,   165,   172,   176,   180,   184,   188,   192,
     196,   200,   204,   208,   212,   216,   220,   230,   229,   262,
     266,   277,   288,   287,   314,   323,   331,   340,   343,   348,
     355,   368,   374,   378,   389,   400,   399,   435,   444,   447,
     452,   459,   465,   469,   480,   494,   493,   533,   568,   576,
     581,   589,   598,   601,   606,   613,   636,   658,   684,   685,
     694,   718,   759,   783,   807,   831,   861,   860,   883,   882,
     905,   906,   912,   916,   927,   942,   941,   976,  1011,  1046,
    1056,  1061,  1069,  1078,  1081,  1086,  1093,  1099,  1106,  1118,
    1130,  1141,  1150,  1165,  1176,  1193,  1197,  1209,  1208,  1232,
    1247,  1253,  1261,  1273,  1281,  1290,  1297,  1308,  1310,  1328,
    1346,  1358,  1370,  1381,  1397,  1402,  1410,  1413,  1419,  1432,
    1436,  1440,  1444,  1448,  1452,  1456,  1460,  1464,  1468,  1472,
    1476,  1495,  1536,  1542,  1550,  1557,  1569,  1576,  1586,  1599,
    1612,  1647,  1658,  1669,  1685,  1694,  1709,  1712,  1715,  1718,
    1721,  1724,  1727,  1730,  1733,  1736,  1739,  1742,  1745,  1748,
    1751,  1754,  1757,  1760,  1763,  1766,  1769,  1772,  1775,  1778,
    1781,  1784,  1787,  1790,  1793
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ICE_MODULE", "ICE_CLASS",
  "ICE_INTERFACE", "ICE_EXCEPTION", "ICE_STRUCT", "ICE_SEQUENCE",
  "ICE_DICTIONARY", "ICE_ENUM", "ICE_OUT", "ICE_EXTENDS", "ICE_IMPLEMENTS",
  "ICE_THROWS", "ICE_VOID", "ICE_BYTE", "ICE_BOOL", "ICE_SHORT", "ICE_INT",
  "ICE_LONG", "ICE_FLOAT", "ICE_DOUBLE", "ICE_STRING", "ICE_OBJECT",
  "ICE_LOCAL_OBJECT", "ICE_LOCAL", "ICE_CONST", "ICE_FALSE", "ICE_TRUE",
  "ICE_NONMUTATING", "ICE_IDEMPOTENT", "ICE_SCOPE_DELIMITER",
  "ICE_IDENTIFIER", "ICE_STRING_LITERAL", "ICE_INTEGER_LITERAL",
  "ICE_FLOATING_POINT_LITERAL", "ICE_IDENT_OP", "ICE_KEYWORD_OP",
  "ICE_METADATA_OPEN", "ICE_METADATA_CLOSE", "ICE_GLOBAL_METADATA_OPEN",
  "ICE_GLOBAL_METADATA_CLOSE", "BAD_CHAR", "';'", "'{'", "'}'", "')'",
  "','", "'<'", "'>'", "'*'", "'='", "$accept", "start",
  "global_meta_data", "meta_data", "definitions", "$@1", "$@2", "$@3",
  "definition", "module_def", "@4", "exception_id", "exception_decl",
  "exception_def", "@5", "exception_extends", "exception_exports",
  "type_id", "exception_export", "struct_id", "struct_decl", "struct_def",
  "@6", "struct_exports", "struct_export", "class_id", "class_decl",
  "class_def", "@7", "class_extends", "implements", "class_exports",
  "data_member", "return_type", "operation_preamble", "operation", "@8",
  "@9", "class_export", "interface_id", "interface_decl", "interface_def",
  "@10", "interface_list", "interface_extends", "interface_exports",
  "interface_export", "exception_list", "exception", "sequence_def",
  "dictionary_def", "enum_id", "enum_def", "@11", "enumerator_list",
  "enumerator", "out_qualifier", "parameters", "throws", "scoped_name",
  "type", "string_literal", "string_list", "local_qualifier",
  "const_initializer", "const_def", "keyword", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,    59,   123,   125,    41,    44,    60,
      62,    42,    61
};
# endif

#define YYPACT_NINF -192

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-192)))

#define YYTABLE_NINF -118

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     400,   -26,    -9,    -9,    27,  -192,    62,  -192,  -192,    -9,
    -192,    18,    20,  -192,    77,    30,  -192,    35,    58,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,
    -192,   130,  -192,    77,  -192,  -192,    -9,  -192,  -192,  -192,
     186,    78,   506,   537,   568,   599,    75,    79,   366,   -11,
      34,     9,    11,  -192,  -192,  -192,    61,  -192,  -192,  -192,
    -192,  -192,  -192,  -192,  -192,    76,  -192,    96,  -192,   -15,
      38,    77,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,    35,
      35,  -192,   630,  -192,    -2,  -192,   103,    -2,   128,    93,
    -192,   107,   104,  -192,  -192,   116,  -192,   101,   156,  -192,
     186,   186,  -192,   108,   109,  -192,   123,   114,   289,   123,
      93,  -192,  -192,  -192,    -8,   115,   630,   117,  -192,   156,
    -192,  -192,  -192,  -192,  -192,   123,  -192,   118,   121,  -192,
     630,   322,   120,   186,   119,  -192,   125,    93,   223,   127,
    -192,  -192,   661,    35,  -192,   122,   186,   129,   289,  -192,
     133,  -192,   692,  -192,   256,  -192,   134,   398,   137,  -192,
    -192,  -192,   186,   322,   135,  -192,  -192,  -192,   289,  -192,
    -192,   136,   398,   140,   223,  -192,   742,   742,    32,    28,
    -192,   149,  -192,  -192,   124,  -192,   322,  -192,   256,  -192,
    -192,   151,   439,  -192,  -192,    57,    59,  -192,  -192,   150,
    -192,    35,    51,   223,   723,  -192,  -192,   256,  -192,  -192,
    -192,  -192,  -192,   186,  -192,   160,  -192,  -192,  -192,  -192,
     182,  -192,   692,   182,    35,   475,  -192,  -192,  -192,   186,
    -192,   152,   123,  -192,  -192,   692,   475,  -192,  -192
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,   147,     2,    10,   143,
     145,     0,     0,     1,     0,     0,   146,     5,    12,    14,
      19,    20,    21,    22,    15,    16,    17,    18,    23,    24,
      25,     0,    26,     0,   142,     4,     0,     3,     7,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
      44,    54,    84,   107,    11,   144,     0,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   139,     0,   126,   140,
       0,     0,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,    52,    53,    82,    83,    29,    30,    42,    43,     5,
       5,   105,   114,   106,     0,    32,     0,     0,    60,     0,
      85,     0,     0,   138,   127,     0,   141,     0,     0,     9,
       0,     0,   112,     0,   111,   113,    34,     0,     0,    57,
       0,    55,    89,    90,    88,     0,   114,     0,   128,     0,
     152,   153,   151,   148,   149,   150,   155,     0,     0,   109,
     114,     0,     0,     0,     0,    59,     0,     0,     0,     0,
      28,   154,     0,     5,   110,     0,     0,     0,     0,    65,
      49,    51,    67,    46,     0,    87,     0,     0,     0,   108,
     101,   102,     0,     0,    38,    41,    33,    48,     0,    40,
      66,     0,     0,     0,     0,    69,     0,     0,     0,     0,
      96,    94,    68,    86,     0,    37,     0,    47,     0,    80,
      81,    63,    67,    56,    93,     0,     0,    70,    73,     0,
     115,     5,     0,     0,     0,    36,    62,     0,    71,    74,
      72,    75,    78,     0,    76,   116,    92,   103,   104,    61,
     125,   118,   122,   125,     5,     0,    79,   120,    77,     0,
     124,    98,    99,   100,   119,   123,     0,   121,    97
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -192,  -192,  -192,   -17,    -7,  -192,  -192,  -192,  -192,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,  -179,  -186,  -192,  -192,
    -192,  -192,  -192,  -163,  -192,  -192,  -192,  -192,  -192,  -192,
    -192,  -146,  -164,   -87,  -192,    -4,  -192,  -192,  -192,  -192,
    -192,  -192,  -192,  -124,  -192,  -191,  -192,   -49,  -192,  -192,
    -192,  -192,  -192,  -192,  -127,  -192,   -24,  -192,   -31,  -108,
     -30,    19,   220,  -192,    81,  -192,   -40
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    14,    41,    33,    18,    19,
      56,    49,    20,    21,   137,   115,   177,   179,   194,    50,
      22,    23,   116,   164,   180,    51,    24,    25,   166,   118,
     141,   203,   181,   208,   209,   210,   253,   250,   221,    52,
      26,    27,   145,   143,   120,   188,   211,   260,   261,    28,
      29,    53,    30,   121,   133,   134,   231,   232,   256,    69,
     212,    10,    11,    31,   156,    32,   135
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      40,   114,   102,   104,   106,   108,   136,    38,   113,   139,
      70,   144,   195,   224,   215,   197,   165,   125,     8,   169,
     155,   117,   -58,   119,   125,     9,    54,    13,    34,   229,
      67,    68,   144,   174,   -35,   217,   126,   235,   219,   230,
     167,   155,   246,   185,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,  -116,  -116,   -58,    55,   -91,   251,    35,   144,
    -116,  -116,    37,    39,   129,    15,    36,  -116,    36,   227,
     228,   127,   236,   264,     2,  -117,  -117,   -13,     1,   -45,
      -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    16,    17,
     128,   249,   130,   131,   238,   239,   240,   241,   244,   245,
     157,   158,    -8,    -5,    -5,     1,   122,    -5,    -5,    -5,
      -5,    -5,    -5,    -5,    -5,   147,     2,   142,     3,   225,
     226,   163,    71,   -13,   109,    67,    68,   123,   110,   124,
      -5,    -5,   191,   182,    42,    43,    44,    45,    46,    47,
      48,   140,   200,     2,   176,     3,   182,   262,   138,   148,
     -13,   187,   146,   149,   159,   125,   192,   160,   262,   161,
     168,   163,   214,   170,   178,   183,   193,   202,   172,   173,
     184,   230,   222,   189,   234,   196,   176,   198,   204,   216,
     218,   163,   200,   213,   150,   151,   223,   187,    67,    68,
     152,   153,   154,   233,   248,   237,   255,   242,   220,   176,
     266,   202,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,   257,   252,   243,   263,   187,   268,    67,    68,
     202,   254,   258,    12,   186,   267,   263,     0,     0,   265,
     171,     0,     0,     0,     0,     0,     0,   259,    -5,    -5,
      -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,     0,
       0,     0,     0,    -5,    -5,    -5,    -5,   201,     0,     0,
       0,     0,     2,     0,     0,     0,     0,     0,     0,   -95,
       0,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,     0,     0,     0,     0,    -5,    -5,    -5,    -5,
     162,     0,     0,     0,     0,     2,     0,     0,     0,     0,
       0,     0,   -64,     0,     0,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,    -5,    -5,    -5,     0,     0,     0,     0,     0,
       0,    -5,    -5,   175,     0,     0,     0,     0,     2,     0,
       0,     0,     0,     0,     0,   -50,     0,     0,    -5,    -5,
      -5,    -5,    -5,    -5,    -5,    -5,    -5,    -5,     0,     0,
       0,     0,     0,     0,    -5,    -5,     0,     0,     0,     0,
       0,     2,     0,     0,     0,     0,     0,     0,   -39,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,     0,   111,
     -13,     1,     0,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
      -5,   112,     0,   205,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,     0,     0,    -5,    -5,   206,   207,
      67,    68,     0,     0,     0,     0,     0,     0,     0,     2,
       0,     3,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,     0,   199,     0,     0,     0,   -68,   -68,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,    67,    68,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,     0,   101,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,     0,
     103,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
       0,   105,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,     0,   107,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,     0,   132,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,     0,   190,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,     0,   199,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,     0,   247,   205,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,     0,     0,
       0,     0,     0,     0,    67,    68
};

static const yytype_int16 yycheck[] =
{
      17,    12,    42,    43,    44,    45,   114,    14,    48,   117,
      40,   119,   176,   204,   193,   178,   140,    32,    44,   146,
     128,    12,    13,    12,    32,    34,    33,     0,     9,     1,
      32,    33,   140,   160,    45,   198,    51,   216,   202,    11,
      48,   149,   233,   167,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    45,    36,    45,   243,    40,   167,
      32,    33,    42,    33,    71,     3,    48,    39,    48,    37,
      38,    33,   218,   259,    39,    47,    48,     0,     1,    45,
       3,     4,     5,     6,     7,     8,     9,    10,    26,    27,
      52,   237,   109,   110,    37,    38,    37,    38,    47,    48,
     130,   131,    44,    26,    27,     1,    45,     3,     4,     5,
       6,     7,     8,     9,    10,   122,    39,    24,    41,   206,
     207,   138,    44,    46,    49,    32,    33,    51,    49,    33,
      26,    27,   172,   163,     4,     5,     6,     7,     8,     9,
      10,    13,   182,    39,   161,    41,   176,   255,    45,    33,
      46,   168,    45,    52,    46,    32,   173,    48,   266,    45,
      45,   178,   192,    46,    44,    46,    44,   184,    50,    48,
      45,    11,   202,    46,    50,    46,   193,    44,    44,    44,
      44,   198,   222,    46,    28,    29,    46,   204,    32,    33,
      34,    35,    36,    44,   234,    44,    14,    47,   202,   216,
      48,   218,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,   252,   243,   231,   255,   233,   266,    32,    33,
     237,   245,   253,     3,     1,   265,   266,    -1,    -1,   259,
     149,    -1,    -1,    -1,    -1,    -1,    -1,   254,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,     1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
       1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,     1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
       0,     1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    45,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    26,    27,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    41,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,    -1,    -1,    -1,    37,    38,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    33,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    33,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    33,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    39,    41,    54,    55,    56,    57,    44,    34,
     114,   115,   115,     0,    58,     3,    26,    27,    61,    62,
      65,    66,    73,    74,    79,    80,    93,    94,   102,   103,
     105,   116,   118,    60,   114,    40,    48,    42,    57,    33,
      56,    59,     4,     5,     6,     7,     8,     9,    10,    64,
      72,    78,    92,   104,    57,   114,    63,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    32,    33,   112,
     113,    44,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    33,   119,    33,   119,    33,   119,    33,   119,    49,
      49,    33,    45,   119,    12,    68,    75,    12,    82,    12,
      97,   106,    45,    51,    33,    32,    51,    33,    52,    57,
      56,    56,    33,   107,   108,   119,   112,    67,    45,   112,
      13,    83,    24,    96,   112,    95,    45,    57,    33,    52,
      28,    29,    34,    35,    36,   112,   117,   113,   113,    46,
      48,    45,     1,    56,    76,    96,    81,    48,    45,   107,
      46,   117,    50,    48,   107,     1,    56,    69,    44,    70,
      77,    85,   113,    46,    45,    96,     1,    56,    98,    46,
      33,   119,    56,    44,    71,    85,    46,    76,    44,    33,
     119,     1,    56,    84,    44,    15,    30,    31,    86,    87,
      88,    99,   113,    46,   113,    69,    44,    76,    44,    85,
      88,    91,   113,    46,    98,    86,    86,    37,    38,     1,
      11,   109,   110,    44,    50,    69,    84,    44,    37,    38,
      37,    38,    47,    56,    47,    48,    98,    33,   119,    84,
      90,    70,   113,    89,   109,    14,   111,   119,   111,    56,
     100,   101,   112,   119,    70,   113,    48,   119,   100
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    55,    56,    56,    58,    57,    59,    57,
      60,    57,    57,    57,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    63,    62,    64,
      64,    65,    67,    66,    68,    68,    69,    69,    69,    69,
      70,    71,    72,    72,    73,    75,    74,    76,    76,    76,
      76,    77,    78,    78,    79,    81,    80,    82,    82,    83,
      83,    84,    84,    84,    84,    85,    85,    85,    86,    86,
      87,    87,    87,    87,    87,    87,    89,    88,    90,    88,
      91,    91,    92,    92,    93,    95,    94,    96,    96,    96,
      97,    97,    98,    98,    98,    98,    99,   100,   100,   101,
     101,   102,   102,   103,   103,   104,   104,   106,   105,   105,
     107,   107,   108,   108,   108,   109,   109,   110,   110,   110,
     110,   110,   110,   110,   111,   111,   112,   112,   112,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   114,   114,   115,   115,   116,   116,   117,   117,
     117,   117,   117,   117,   118,   118,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     3,     0,     0,     3,     0,     5,
       0,     4,     2,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     2,
       2,     2,     0,     7,     2,     0,     4,     3,     2,     0,
       2,     1,     2,     2,     2,     0,     6,     4,     3,     2,
       0,     1,     2,     2,     2,     0,     8,     2,     0,     2,
       0,     4,     3,     2,     0,     1,     2,     1,     1,     1,
       2,     3,     3,     2,     3,     3,     0,     5,     0,     5,
       1,     1,     2,     2,     2,     0,     7,     3,     1,     1,
       2,     0,     4,     3,     2,     0,     1,     3,     1,     1,
       1,     7,     7,    10,    10,     2,     2,     0,     6,     5,
       3,     1,     1,     1,     0,     1,     0,     0,     3,     5,
       4,     6,     3,     5,     2,     0,     1,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     2,     2,     1,     3,     1,     1,     0,     1,     1,
       1,     1,     1,     1,     6,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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
yyparse (void)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      yychar = yylex (&yylval);
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 106 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 1611 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 114 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[-1]);
}
#line 1619 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 123 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[-1]);
}
#line 1627 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 127 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = new StringListTok;
}
#line 1635 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 136 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast((yyvsp[0]));
    if(!metaData->v.empty())
    {
        unit->addGlobalMetaData(metaData->v);
    }
}
#line 1647 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 145 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast((yyvsp[-1]));
    ContainedPtr contained = ContainedPtr::dynamicCast((yyvsp[0]));
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
    unit->setSeenDefinition();
}
#line 1661 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 156 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    yyerrok;
}
#line 1669 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 161 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    unit->error("`;' missing after definition");
}
#line 1677 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 165 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 1684 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 173 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    assert((yyvsp[0]) == 0 || ModulePtr::dynamicCast((yyvsp[0])));
}
#line 1692 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 177 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    assert((yyvsp[0]) == 0 || ClassDeclPtr::dynamicCast((yyvsp[0])));
}
#line 1700 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 181 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    assert((yyvsp[0]) == 0 || ClassDefPtr::dynamicCast((yyvsp[0])));
}
#line 1708 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 185 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    assert((yyvsp[0]) == 0 || ClassDeclPtr::dynamicCast((yyvsp[0])));
}
#line 1716 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 189 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    assert((yyvsp[0]) == 0 || ClassDefPtr::dynamicCast((yyvsp[0])));
}
#line 1724 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 193 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    assert((yyvsp[0]) == 0);
}
#line 1732 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 197 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    assert((yyvsp[0]) == 0 || ExceptionPtr::dynamicCast((yyvsp[0])));
}
#line 1740 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 201 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    assert((yyvsp[0]) == 0);
}
#line 1748 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 205 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    assert((yyvsp[0]) == 0 || StructPtr::dynamicCast((yyvsp[0])));
}
#line 1756 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 209 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    assert((yyvsp[0]) == 0 || SequencePtr::dynamicCast((yyvsp[0])));
}
#line 1764 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 213 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    assert((yyvsp[0]) == 0 || DictionaryPtr::dynamicCast((yyvsp[0])));
}
#line 1772 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 217 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    assert((yyvsp[0]) == 0 || EnumPtr::dynamicCast((yyvsp[0])));
}
#line 1780 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 221 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    assert((yyvsp[0]) == 0 || ConstPtr::dynamicCast((yyvsp[0])));
}
#line 1788 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 230 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    ContainerPtr cont = unit->currentContainer();
    ModulePtr module = cont->createModule(ident->v);
    if(module)
    {
	cont->checkIntroduced(ident->v, module);
	unit->pushContainer(module);
	(yyval) = module;
    }
    else
    {
        (yyval) = 0;
    }
}
#line 1808 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 246 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    if((yyvsp[-3]))
    {
	unit->popContainer();
	(yyval) = (yyvsp[-3]);
    }
    else
    {
        (yyval) = 0;
    }
}
#line 1824 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 263 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 1832 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 267 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    unit->error("keyword `" + ident->v + "' cannot be used as exception name");
    (yyval) = (yyvsp[0]); // Dummy
}
#line 1842 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 278 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    unit->error("exceptions cannot be forward declared");
    (yyval) = 0;
}
#line 1851 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 288 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast((yyvsp[-2]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[-1]));
    ExceptionPtr base = ExceptionPtr::dynamicCast((yyvsp[0]));
    ContainerPtr cont = unit->currentContainer();
    ExceptionPtr ex = cont->createException(ident->v, base, local->v);
    if(ex)
    {
	cont->checkIntroduced(ident->v, ex);
	unit->pushContainer(ex);
    }
    (yyval) = ex;
}
#line 1869 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 302 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    if((yyvsp[-3]))
    {
	unit->popContainer();
    }
    (yyval) = (yyvsp[-3]);
}
#line 1881 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 315 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast((yyvsp[0]));
    ContainerPtr cont = unit->currentContainer();
    ContainedPtr contained = cont->lookupException(scoped->v);
    cont->checkIntroduced(scoped->v);
    (yyval) = contained;
}
#line 1893 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 323 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = 0;
}
#line 1901 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 332 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast((yyvsp[-3]));
    ContainedPtr contained = ContainedPtr::dynamicCast((yyvsp[-2]));
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
}
#line 1914 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 341 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 1921 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 344 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    unit->error("`;' missing after definition");
}
#line 1929 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 348 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 1936 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 356 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    TypePtr type = TypePtr::dynamicCast((yyvsp[-1]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    TypeStringTokPtr typestring = new TypeStringTok;
    typestring->v = make_pair(type, ident->v);
    (yyval) = typestring;
}
#line 1948 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 375 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 1956 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 379 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    unit->error("keyword `" + ident->v + "' cannot be used as struct name");
    (yyval) = (yyvsp[0]); // Dummy
}
#line 1966 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 390 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    unit->error("structs cannot be forward declared");
    (yyval) = 0; // Dummy
}
#line 1975 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 400 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast((yyvsp[-1]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    ContainerPtr cont = unit->currentContainer();
    StructPtr st = cont->createStruct(ident->v, local->v);
    if(st)
    {
	cont->checkIntroduced(ident->v, st);
	unit->pushContainer(st);
    }
    (yyval) = st;
}
#line 1992 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 413 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    if((yyvsp[-3]))
    {
	unit->popContainer();
    }
    (yyval) = (yyvsp[-3]);

    //
    // Empty structures are not allowed
    //
    StructPtr st = StructPtr::dynamicCast((yyval));
    assert(st);
    if(st->dataMembers().empty())
    {
    	unit->error("struct `" + st->name() + "' must have at least one member"); // $$ is a dummy
    }
}
#line 2014 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 436 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast((yyvsp[-3]));
    ContainedPtr contained = ContainedPtr::dynamicCast((yyvsp[-2]));
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
}
#line 2027 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 445 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 2034 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 448 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    unit->error("`;' missing after definition");
}
#line 2042 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 452 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 2049 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 466 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2057 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 470 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    unit->error("keyword `" + ident->v + "' cannot be used as class name");
    (yyval) = (yyvsp[0]); // Dummy
}
#line 2067 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 481 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast((yyvsp[-1]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    ContainerPtr cont = unit->currentContainer();
    ClassDeclPtr cl = cont->createClassDecl(ident->v, false, local->v);
    (yyval) = cl;
}
#line 2079 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 494 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast((yyvsp[-3]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[-2]));
    ContainerPtr cont = unit->currentContainer();
    ClassDefPtr base = ClassDefPtr::dynamicCast((yyvsp[-1]));
    ClassListTokPtr bases = ClassListTokPtr::dynamicCast((yyvsp[0]));
    if(base)
    {
	bases->v.push_front(base);
    }
    ClassDefPtr cl = cont->createClassDef(ident->v, false, bases->v, local->v);
    if(cl)
    {
	cont->checkIntroduced(ident->v, cl);
	unit->pushContainer(cl);
	(yyval) = cl;
    }
    else
    {
        (yyval) = 0;
    }
}
#line 2106 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 517 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    if((yyvsp[-3]))
    {
	unit->popContainer();
	(yyval) = (yyvsp[-3]);
    }
    else
    {
        (yyval) = 0;
    }
}
#line 2122 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 534 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast((yyvsp[0]));
    ContainerPtr cont = unit->currentContainer();
    TypeList types = cont->lookupType(scoped->v);
    (yyval) = 0;
    if(!types.empty())
    {
	ClassDeclPtr cl = ClassDeclPtr::dynamicCast(types.front());
	if(!cl || cl->isInterface())
	{
	    string msg = "`";
	    msg += scoped->v;
	    msg += "' is not a class";
	    unit->error(msg);
	}
	else
	{
	    ClassDefPtr def = cl->definition();
	    if(!def)
	    {
		string msg = "`";
		msg += scoped->v;
		msg += "' has been declared but not defined";
		unit->error(msg);
	    }
	    else
	    {
	    	cont->checkIntroduced(scoped->v);
		(yyval) = def;
	    }
	}
    }
}
#line 2160 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 568 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = 0;
}
#line 2168 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 577 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2176 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 581 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = new ClassListTok;
}
#line 2184 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 590 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast((yyvsp[-3]));
    ContainedPtr contained = ContainedPtr::dynamicCast((yyvsp[-2]));
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
}
#line 2197 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 599 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 2204 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 602 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    unit->error("`;' missing after definition");
}
#line 2212 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 606 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 2219 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 614 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    TypePtr type = TypeStringTokPtr::dynamicCast((yyvsp[0]))->v.first;
    string name = TypeStringTokPtr::dynamicCast((yyvsp[0]))->v.second;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    DataMemberPtr dm;
    if(cl)
    {
	dm = cl->createDataMember(name, type);
    }
    StructPtr st = StructPtr::dynamicCast(unit->currentContainer());
    if(st)
    {
	dm = st->createDataMember(name, type);
    }
    ExceptionPtr ex = ExceptionPtr::dynamicCast(unit->currentContainer());
    if(ex)
    {
	dm = ex->createDataMember(name, type);
    }
    unit->currentContainer()->checkIntroduced(name, dm);
    (yyval) = dm;
}
#line 2246 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 637 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    TypePtr type = TypePtr::dynamicCast((yyvsp[-1]));
    string name = StringTokPtr::dynamicCast((yyvsp[0]))->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
	(yyval) = cl->createDataMember(name, type); // Dummy
    }
    StructPtr st = StructPtr::dynamicCast(unit->currentContainer());
    if(st)
    {
	(yyval) = st->createDataMember(name, type); // Dummy
    }
    ExceptionPtr ex = ExceptionPtr::dynamicCast(unit->currentContainer());
    if(ex)
    {
	(yyval) = ex->createDataMember(name, type); // Dummy
    }
    assert((yyval));
    unit->error("keyword `" + name + "' cannot be used as data member name");
}
#line 2272 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 659 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    TypePtr type = TypePtr::dynamicCast((yyvsp[0]));
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
        (yyval) = cl->createDataMember(IceUtil::generateUUID(), type); // Dummy
    }
    StructPtr st = StructPtr::dynamicCast(unit->currentContainer());
    if(st)
    {
	(yyval) = st->createDataMember(IceUtil::generateUUID(), type); // Dummy
    }
    ExceptionPtr ex = ExceptionPtr::dynamicCast(unit->currentContainer());
    if(ex)
    {
	(yyval) = ex->createDataMember(IceUtil::generateUUID(), type); // Dummy
    }
    assert((yyval));
    unit->error("missing data member name");
}
#line 2297 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 686 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = 0;
}
#line 2305 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 695 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    TypePtr returnType = TypePtr::dynamicCast((yyvsp[-1]));
    string name = StringTokPtr::dynamicCast((yyvsp[0]))->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
	OperationPtr op = cl->createOperation(name, returnType);
	if(op)
	{
	    cl->checkIntroduced(name, op);
	    unit->pushContainer(op);
	    (yyval) = op;
	}
	else
	{
	    (yyval) = 0;
	}
    }
    else
    {
        (yyval) = 0;
    }
}
#line 2333 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 719 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    TypePtr returnType = TypePtr::dynamicCast((yyvsp[-1]));
    string name = StringTokPtr::dynamicCast((yyvsp[0]))->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
	OperationPtr op = cl->createOperation(name, returnType, Operation::Nonmutating);
	if(op)
	{
	    cl->checkIntroduced(name, op);
	    unit->pushContainer(op);
	    static bool firstWarning = true;  
	    
	    string msg = "the keyword 'nonmutating' is deprecated";
	    if(firstWarning)
	    {
		msg += ";\n";
		msg += "You should use instead 'idempotent' plus:\n";
		msg += " - Freeze metadata ([\"freeze:read\"], [\"freeze:write\"]) if you implement your objects with a Freeze evictor\n";
		msg += " - [\"nonmutating\"], if you need to maintain compatibility with operations that expect ";
		msg += "'Nonmutating' as operation-mode. With this metadata, the generated code sends ";
		msg += "'Nonmutating' instead of 'Idempotent'\n";
		msg += " - [\"cpp:const\"], to get a const member function on the generated C++ servant base class";

		firstWarning = false;
	    }
	    
	    unit->warning(msg); 
	    (yyval) = op;
	}
	else
	{
	    (yyval) = 0;
	}
    }
    else
    {
        (yyval) = 0;
    }
}
#line 2378 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 760 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    TypePtr returnType = TypePtr::dynamicCast((yyvsp[-1]));
    string name = StringTokPtr::dynamicCast((yyvsp[0]))->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
	OperationPtr op = cl->createOperation(name, returnType, Operation::Idempotent);
	if(op)
	{
	    cl->checkIntroduced(name, op);
	    unit->pushContainer(op);
	    (yyval) = op;
	}
	else
	{
	    (yyval) = 0;
	}
    }
    else
    {
        (yyval) = 0;
    }
}
#line 2406 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 784 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    TypePtr returnType = TypePtr::dynamicCast((yyvsp[-1]));
    string name = StringTokPtr::dynamicCast((yyvsp[0]))->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
	OperationPtr op = cl->createOperation(name, returnType);
	if(op)
	{
	    unit->pushContainer(op);
	    unit->error("keyword `" + name + "' cannot be used as operation name");
	    (yyval) = op; // Dummy
	}
	else
	{
	    (yyval) = 0;
	}
    }
    else
    {
        (yyval) = 0;
    }
}
#line 2434 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 808 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    TypePtr returnType = TypePtr::dynamicCast((yyvsp[-1]));
    string name = StringTokPtr::dynamicCast((yyvsp[0]))->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
	OperationPtr op = cl->createOperation(name, returnType, Operation::Nonmutating);
	if(op)
	{
	    unit->pushContainer(op);
	    unit->error("keyword `" + name + "' cannot be used as operation name");
	    (yyval) = op; // Dummy
	}
	else
	{
	    (yyval) = 0;
	}
    }
    else
    {
    	(yyval) = 0;
    }
}
#line 2462 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 832 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    TypePtr returnType = TypePtr::dynamicCast((yyvsp[-1]));
    string name = StringTokPtr::dynamicCast((yyvsp[0]))->v;
    ClassDefPtr cl = ClassDefPtr::dynamicCast(unit->currentContainer());
    if(cl)
    {
	OperationPtr op = cl->createOperation(name, returnType, Operation::Idempotent);
	if(op)
	{
	    unit->pushContainer(op);
	    unit->error("keyword `" + name + "' cannot be used as operation name");
	    (yyval) = op; // Dummy
	}
	else
	{
	    return 0;
	}
    }
    else
    {
    	(yyval) = 0;
    }
}
#line 2490 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 861 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    if((yyvsp[-2]))
    {
	unit->popContainer();
	(yyval) = (yyvsp[-2]);
    }
    else
    {
        (yyval) = 0;
    }
}
#line 2506 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 873 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    OperationPtr op = OperationPtr::dynamicCast((yyvsp[-1]));
    ExceptionListTokPtr el = ExceptionListTokPtr::dynamicCast((yyvsp[0]));
    assert(el);
    if(op)
    {
        op->setExceptionList(el->v);
    }
}
#line 2520 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 883 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    if((yyvsp[-2]))
    {
	unit->popContainer();
    }
    yyerrok;
}
#line 2532 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 891 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    OperationPtr op = OperationPtr::dynamicCast((yyvsp[-1]));
    ExceptionListTokPtr el = ExceptionListTokPtr::dynamicCast((yyvsp[0]));
    assert(el);
    if(op)
    {
        op->setExceptionList(el->v); // Dummy
    }
}
#line 2546 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 913 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2554 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 917 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    unit->error("keyword `" + ident->v + "' cannot be used as interface name");
    (yyval) = (yyvsp[0]); // Dummy
}
#line 2564 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 928 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast((yyvsp[-1]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    ContainerPtr cont = unit->currentContainer();
    ClassDeclPtr cl = cont->createClassDecl(ident->v, true, local->v);
    cont->checkIntroduced(ident->v, cl);
    (yyval) = cl;
}
#line 2577 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 942 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast((yyvsp[-2]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[-1]));
    ContainerPtr cont = unit->currentContainer();
    ClassListTokPtr bases = ClassListTokPtr::dynamicCast((yyvsp[0]));
    ClassDefPtr cl = cont->createClassDef(ident->v, true, bases->v, local->v);
    if(cl)
    {
	cont->checkIntroduced(ident->v, cl);
	unit->pushContainer(cl);
	(yyval) = cl;
    }
    else
    {
        (yyval) = 0;
    }
}
#line 2599 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 960 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    if((yyvsp[-3]))
    {
	unit->popContainer();
	(yyval) = (yyvsp[-3]);
    }
    else
    {
	(yyval) = 0;
    }
}
#line 2615 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 977 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    ClassListTokPtr intfs = ClassListTokPtr::dynamicCast((yyvsp[0]));
    StringTokPtr scoped = StringTokPtr::dynamicCast((yyvsp[-2]));
    ContainerPtr cont = unit->currentContainer();
    TypeList types = cont->lookupType(scoped->v);
    if(!types.empty())
    {
	ClassDeclPtr cl = ClassDeclPtr::dynamicCast(types.front());
	if(!cl || !cl->isInterface())
	{
	    string msg = "`";
	    msg += scoped->v;
	    msg += "' is not an interface";
	    unit->error(msg);
	}
	else
	{
	    ClassDefPtr def = cl->definition();
	    if(!def)
	    {
		string msg = "`";
		msg += scoped->v;
		msg += "' has been declared but not defined";
		unit->error(msg);
	    }
	    else
	    {
	    	cont->checkIntroduced(scoped->v);
		intfs->v.push_front(def);
	    }
	}
    }
    (yyval) = intfs;
}
#line 2654 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1012 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    ClassListTokPtr intfs = new ClassListTok;
    StringTokPtr scoped = StringTokPtr::dynamicCast((yyvsp[0]));
    ContainerPtr cont = unit->currentContainer();
    TypeList types = cont->lookupType(scoped->v);
    if(!types.empty())
    {
	ClassDeclPtr cl = ClassDeclPtr::dynamicCast(types.front());
	if(!cl || !cl->isInterface())
	{
	    string msg = "`";
	    msg += scoped->v;
	    msg += "' is not an interface";
	    unit->error(msg); // $$ is a dummy
	}
	else
	{
	    ClassDefPtr def = cl->definition();
	    if(!def)
	    {
		string msg = "`";
		msg += scoped->v;
		msg += "' has been declared but not defined";
		unit->error(msg); // $$ is a dummy
	    }
	    else
	    {
	    	cont->checkIntroduced(scoped->v);
		intfs->v.push_front(def);
	    }
	}
    }
    (yyval) = intfs;
}
#line 2693 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1047 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    unit->error("illegal inheritance from type Object");
    (yyval) = new ClassListTok; // Dummy
}
#line 2702 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1057 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2710 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1061 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = new ClassListTok;
}
#line 2718 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1070 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast((yyvsp[-3]));
    ContainedPtr contained = ContainedPtr::dynamicCast((yyvsp[-2]));
    if(contained && !metaData->v.empty())
    {
	contained->setMetaData(metaData->v);
    }
}
#line 2731 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1079 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 2738 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1082 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    unit->error("`;' missing after definition");
}
#line 2746 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1086 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 2753 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1100 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    ExceptionPtr exception = ExceptionPtr::dynamicCast((yyvsp[-2]));
    ExceptionListTokPtr exceptionList = ExceptionListTokPtr::dynamicCast((yyvsp[0]));
    exceptionList->v.push_front(exception);
    (yyval) = exceptionList;
}
#line 2764 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1107 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    ExceptionPtr exception = ExceptionPtr::dynamicCast((yyvsp[0]));
    ExceptionListTokPtr exceptionList = new ExceptionListTok;
    exceptionList->v.push_front(exception);
    (yyval) = exceptionList;
}
#line 2775 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1119 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast((yyvsp[0]));
    ContainerPtr cont = unit->currentContainer();
    ExceptionPtr exception = cont->lookupException(scoped->v);
    if(!exception)
    {
	exception = cont->createException(IceUtil::generateUUID(), 0, false, Dummy); // Dummy
    }
    cont->checkIntroduced(scoped->v, exception);
    (yyval) = exception;
}
#line 2791 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1131 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    unit->error("keyword `" + ident->v + "' cannot be used as exception name");
    (yyval) = unit->currentContainer()->createException(IceUtil::generateUUID(), 0, false, Dummy); // Dummy
}
#line 2801 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1142 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast((yyvsp[-6]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    StringListTokPtr metaData = StringListTokPtr::dynamicCast((yyvsp[-3]));
    TypePtr type = TypePtr::dynamicCast((yyvsp[-2]));
    ContainerPtr cont = unit->currentContainer();
    (yyval) = cont->createSequence(ident->v, type, metaData->v, local->v);
}
#line 2814 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1151 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast((yyvsp[-6]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    StringListTokPtr metaData = StringListTokPtr::dynamicCast((yyvsp[-3]));
    TypePtr type = TypePtr::dynamicCast((yyvsp[-2]));
    ContainerPtr cont = unit->currentContainer();
    (yyval) = cont->createSequence(ident->v, type, metaData->v, local->v); // Dummy
    unit->error("keyword `" + ident->v + "' cannot be used as sequence name");
}
#line 2828 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1166 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast((yyvsp[-9]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    StringListTokPtr keyMetaData = StringListTokPtr::dynamicCast((yyvsp[-6]));
    TypePtr keyType = TypePtr::dynamicCast((yyvsp[-5]));
    StringListTokPtr valueMetaData = StringListTokPtr::dynamicCast((yyvsp[-3]));
    TypePtr valueType = TypePtr::dynamicCast((yyvsp[-2]));
    ContainerPtr cont = unit->currentContainer();
    (yyval) = cont->createDictionary(ident->v, keyType, keyMetaData->v, valueType, valueMetaData->v, local->v);
}
#line 2843 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1177 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast((yyvsp[-9]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    StringListTokPtr keyMetaData = StringListTokPtr::dynamicCast((yyvsp[-6]));
    TypePtr keyType = TypePtr::dynamicCast((yyvsp[-5]));
    StringListTokPtr valueMetaData = StringListTokPtr::dynamicCast((yyvsp[-3]));
    TypePtr valueType = TypePtr::dynamicCast((yyvsp[-2]));
    ContainerPtr cont = unit->currentContainer();
    (yyval) = cont->createDictionary(ident->v, keyType, keyMetaData->v, valueType, valueMetaData->v, local->v); // Dummy
    unit->error("keyword `" + ident->v + "' cannot be used as dictionary name");
}
#line 2859 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1194 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 2867 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1198 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    unit->error("keyword `" + ident->v + "' cannot be used as enumeration name");
    (yyval) = (yyvsp[0]); // Dummy
}
#line 2877 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1209 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr local = BoolTokPtr::dynamicCast((yyvsp[-1]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    ContainerPtr cont = unit->currentContainer();
    EnumPtr en = cont->createEnum(ident->v, local->v);
    cont->checkIntroduced(ident->v, en);
    (yyval) = en;
}
#line 2890 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1218 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    EnumPtr en = EnumPtr::dynamicCast((yyvsp[-3]));
    if(en)
    {
	EnumeratorListTokPtr enumerators = EnumeratorListTokPtr::dynamicCast((yyvsp[-1]));
	if(enumerators->v.empty())
	{
	    unit->error("enum `" + en->name() + "' must have at least one enumerator");
	}
	en->setEnumerators(enumerators->v); // Dummy
    }
    (yyval) = (yyvsp[-3]);
}
#line 2908 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1233 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    unit->error("missing enumeration name");
    BoolTokPtr local = BoolTokPtr::dynamicCast((yyvsp[-4]));
    ContainerPtr cont = unit->currentContainer();
    EnumPtr en = cont->createEnum(IceUtil::generateUUID(), local->v, Dummy); // Dummy
    EnumeratorListTokPtr enumerators = EnumeratorListTokPtr::dynamicCast((yyvsp[-1]));
    en->setEnumerators(enumerators->v); // Dummy
    (yyval) = en;
}
#line 2922 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1248 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    EnumeratorListTokPtr ens = EnumeratorListTokPtr::dynamicCast((yyvsp[-2]));
    ens->v.splice(ens->v.end(), EnumeratorListTokPtr::dynamicCast((yyvsp[0]))->v);
    (yyval) = ens;
}
#line 2932 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1254 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 2939 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1262 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    EnumeratorListTokPtr ens = new EnumeratorListTok;
    ContainerPtr cont = unit->currentContainer();
    EnumeratorPtr en = cont->createEnumerator(ident->v);
    if(en)
    {
	ens->v.push_front(en);
    }
    (yyval) = ens;
}
#line 2955 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1274 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    unit->error("keyword `" + ident->v + "' cannot be used as enumerator");
    EnumeratorListTokPtr ens = new EnumeratorListTok; // Dummy
    (yyval) = ens;
}
#line 2966 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1281 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    EnumeratorListTokPtr ens = new EnumeratorListTok;
    (yyval) = ens; // Dummy
}
#line 2975 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1291 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr out = new BoolTok;
    out->v = true;
    (yyval) = out;
}
#line 2985 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1297 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr out = new BoolTok;
    out->v = false;
    (yyval) = out;
}
#line 2995 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1308 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3002 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1311 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast((yyvsp[-2]));
    TypeStringTokPtr tsp = TypeStringTokPtr::dynamicCast((yyvsp[0]));
    TypePtr type = tsp->v.first;
    string ident = tsp->v.second;
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	ParamDeclPtr pd = op->createParamDecl(ident, type, isOutParam->v);
	unit->currentContainer()->checkIntroduced(ident, pd);
        StringListTokPtr metaData = StringListTokPtr::dynamicCast((yyvsp[-1]));
        if(!metaData->v.empty())
        {
            pd->setMetaData(metaData->v);
        }
    }
}
#line 3024 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1329 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast((yyvsp[-2]));
    TypeStringTokPtr tsp = TypeStringTokPtr::dynamicCast((yyvsp[0]));
    TypePtr type = tsp->v.first;
    string ident = tsp->v.second;
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	ParamDeclPtr pd = op->createParamDecl(ident, type, isOutParam->v);
	unit->currentContainer()->checkIntroduced(ident, pd);
        StringListTokPtr metaData = StringListTokPtr::dynamicCast((yyvsp[-1]));
        if(!metaData->v.empty())
        {
            pd->setMetaData(metaData->v);
        }
    }
}
#line 3046 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1347 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast((yyvsp[-3]));
    TypePtr type = TypePtr::dynamicCast((yyvsp[-1]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	op->createParamDecl(ident->v, type, isOutParam->v); // Dummy
	unit->error("keyword `" + ident->v + "' cannot be used as parameter name");
    }
}
#line 3062 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1359 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast((yyvsp[-3]));
    TypePtr type = TypePtr::dynamicCast((yyvsp[-1]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	op->createParamDecl(ident->v, type, isOutParam->v); // Dummy
	unit->error("keyword `" + ident->v + "' cannot be used as parameter name");
    }
}
#line 3078 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1371 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast((yyvsp[-2]));
    TypePtr type = TypePtr::dynamicCast((yyvsp[0]));
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	op->createParamDecl(IceUtil::generateUUID(), type, isOutParam->v); // Dummy
	unit->error("missing parameter name");
    }
}
#line 3093 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1382 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr isOutParam = BoolTokPtr::dynamicCast((yyvsp[-2]));
    TypePtr type = TypePtr::dynamicCast((yyvsp[0]));
    OperationPtr op = OperationPtr::dynamicCast(unit->currentContainer());
    if(op)
    {
	op->createParamDecl(IceUtil::generateUUID(), type, isOutParam->v); // Dummy
	unit->error("missing parameter name");
    }
}
#line 3108 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1398 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = (yyvsp[0]);
}
#line 3116 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1402 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = new ExceptionListTok;
}
#line 3124 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1411 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3131 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1414 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    ident->v = "::" + ident->v;
    (yyval) = ident;
}
#line 3141 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1420 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast((yyvsp[-2]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[0]));
    scoped->v += "::";
    scoped->v += ident->v;
    (yyval) = scoped;
}
#line 3153 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1433 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = unit->builtin(Builtin::KindByte);
}
#line 3161 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1437 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = unit->builtin(Builtin::KindBool);
}
#line 3169 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1441 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = unit->builtin(Builtin::KindShort);
}
#line 3177 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1445 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = unit->builtin(Builtin::KindInt);
}
#line 3185 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1449 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = unit->builtin(Builtin::KindLong);
}
#line 3193 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1453 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = unit->builtin(Builtin::KindFloat);
}
#line 3201 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1457 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = unit->builtin(Builtin::KindDouble);
}
#line 3209 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1461 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = unit->builtin(Builtin::KindString);
}
#line 3217 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1465 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = unit->builtin(Builtin::KindObject);
}
#line 3225 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1469 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = unit->builtin(Builtin::KindObjectProxy);
}
#line 3233 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1473 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    (yyval) = unit->builtin(Builtin::KindLocalObject);
}
#line 3241 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1477 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast((yyvsp[0]));
    ContainerPtr cont = unit->currentContainer();
    if(cont)
    {
	TypeList types = cont->lookupType(scoped->v);
	if(types.empty())
	{
	    YYERROR; // Can't continue, jump to next yyerrok
	}
	cont->checkIntroduced(scoped->v);
	(yyval) = types.front();
    }
    else
    {
        (yyval) = 0;
    }
}
#line 3264 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1496 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast((yyvsp[-1]));
    ContainerPtr cont = unit->currentContainer();
    if(cont)
    {
	TypeList types = cont->lookupType(scoped->v);
	if(types.empty())
	{
	    YYERROR; // Can't continue, jump to next yyerrok
	}
	for(TypeList::iterator p = types.begin(); p != types.end(); ++p)
	{
	    ClassDeclPtr cl = ClassDeclPtr::dynamicCast(*p);
	    if(!cl)
	    {
		string msg = "`";
		msg += scoped->v;
		msg += "' must be class or interface";
		unit->error(msg);
		YYERROR; // Can't continue, jump to next yyerrok
	    }
	    cont->checkIntroduced(scoped->v);
	    if(cl->isLocal())
	    {
		unit->error("cannot create proxy for " + cl->kindOf() + " `" + cl->name() + "'"); // $$ is dummy
	    }
	    *p = new Proxy(cl);
	}
	(yyval) = types.front();
    }
    else
    {
        (yyval) = 0;
    }
}
#line 3304 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1537 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr str1 = StringTokPtr::dynamicCast((yyvsp[-1]));
    StringTokPtr str2 = StringTokPtr::dynamicCast((yyvsp[0]));
    str1->v += str2->v;
}
#line 3314 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1543 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3321 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1551 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr str = StringTokPtr::dynamicCast((yyvsp[0]));
    StringListTokPtr stringList = StringListTokPtr::dynamicCast((yyvsp[-2]));
    stringList->v.push_back(str->v);
    (yyval) = stringList;
}
#line 3332 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1558 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr str = StringTokPtr::dynamicCast((yyvsp[0]));
    StringListTokPtr stringList = new StringListTok;
    stringList->v.push_back(str->v);
    (yyval) = stringList;
}
#line 3343 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1570 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr local = new BoolTok;
    local->v = true;
    (yyval) = local;
}
#line 3353 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1576 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BoolTokPtr local = new BoolTok;
    local->v = false;
    (yyval) = local;
}
#line 3363 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1587 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BuiltinPtr type = unit->builtin(Builtin::KindLong);
    IntegerTokPtr intVal = IntegerTokPtr::dynamicCast((yyvsp[0]));
    ostringstream sstr;
    sstr << intVal->v;
    ConstDefTokPtr def = new ConstDefTok;
    def->v.type = type;
    def->v.value = type;
    def->v.valueAsString = sstr.str();
    def->v.valueAsLiteral = intVal->literal;
    (yyval) = def;
}
#line 3380 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1600 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BuiltinPtr type = unit->builtin(Builtin::KindDouble);
    FloatingTokPtr floatVal = FloatingTokPtr::dynamicCast((yyvsp[0]));
    ostringstream sstr;
    sstr << floatVal->v;
    ConstDefTokPtr def = new ConstDefTok;
    def->v.type = type;
    def->v.value = type;
    def->v.valueAsString = sstr.str();
    def->v.valueAsLiteral = floatVal->literal;
    (yyval) = def;
}
#line 3397 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1613 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringTokPtr scoped = StringTokPtr::dynamicCast((yyvsp[0]));
    ConstDefTokPtr def = new ConstDefTok;
    ContainedList cl = unit->currentContainer()->lookupContained(scoped->v);
    if(cl.empty())
    {
        def->v.type = TypePtr(0);
        def->v.value = TypePtr(0);
        def->v.valueAsString = scoped->v;
        def->v.valueAsLiteral = scoped->v;
    }
    else
    {
	EnumeratorPtr enumerator = EnumeratorPtr::dynamicCast(cl.front());
	if(!enumerator)
	{
	    string msg = "illegal initializer: `" + scoped->v + "' is a";
	    static const string vowels = "aeiou";
	    string kindOf = cl.front()->kindOf();
	    if(vowels.find_first_of(kindOf[0]) != string::npos)
	    {
	    	msg += "n";
	    }
	    msg += " " + kindOf;
	    unit->error(msg); // $$ is dummy
	}
	unit->currentContainer()->checkIntroduced(scoped->v, enumerator);
        def->v.type = enumerator->type();
        def->v.value = enumerator;
        def->v.valueAsString = scoped->v;
        def->v.valueAsLiteral = scoped->v;
    }
    (yyval) = def;
}
#line 3436 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1648 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BuiltinPtr type = unit->builtin(Builtin::KindString);
    StringTokPtr literal = StringTokPtr::dynamicCast((yyvsp[0]));
    ConstDefTokPtr def = new ConstDefTok;
    def->v.type = type;
    def->v.value = type;
    def->v.valueAsString = literal->v;
    def->v.valueAsLiteral = literal->literal;
    (yyval) = def;
}
#line 3451 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1659 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BuiltinPtr type = unit->builtin(Builtin::KindBool);
    StringTokPtr literal = StringTokPtr::dynamicCast((yyvsp[0]));
    ConstDefTokPtr def = new ConstDefTok;
    def->v.type = type;
    def->v.value = type;
    def->v.valueAsString = literal->v;
    def->v.valueAsLiteral = "false";
    (yyval) = def;
}
#line 3466 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1670 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    BuiltinPtr type = unit->builtin(Builtin::KindBool);
    StringTokPtr literal = StringTokPtr::dynamicCast((yyvsp[0]));
    ConstDefTokPtr def = new ConstDefTok;
    def->v.type = type;
    def->v.value = type;
    def->v.valueAsString = literal->v;
    def->v.valueAsLiteral = "true";
    (yyval) = def;
}
#line 3481 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1686 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast((yyvsp[-4]));
    TypePtr const_type = TypePtr::dynamicCast((yyvsp[-3]));
    StringTokPtr ident = StringTokPtr::dynamicCast((yyvsp[-2]));
    ConstDefTokPtr value = ConstDefTokPtr::dynamicCast((yyvsp[0]));
    (yyval) = unit->currentContainer()->createConst(ident->v, const_type, metaData->v,
                                               value->v.value, value->v.valueAsString, value->v.valueAsLiteral);
}
#line 3494 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1695 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
    StringListTokPtr metaData = StringListTokPtr::dynamicCast((yyvsp[-3]));
    TypePtr const_type = TypePtr::dynamicCast((yyvsp[-2]));
    ConstDefTokPtr value = ConstDefTokPtr::dynamicCast((yyvsp[0]));
    unit->error("missing constant name");
    (yyval) = unit->currentContainer()->createConst(IceUtil::generateUUID(), const_type, metaData->v,
                                               value->v.value, value->v.valueAsString,
                                               value->v.valueAsLiteral, Dummy); // Dummy
}
#line 3508 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1710 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3515 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1713 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3522 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1716 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3529 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1719 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3536 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1722 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3543 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1725 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3550 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1728 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3557 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1731 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3564 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1734 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3571 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1737 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3578 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1740 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3585 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1743 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3592 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1746 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3599 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1749 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3606 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1752 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3613 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1755 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3620 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1758 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3627 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1761 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3634 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1764 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3641 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1767 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3648 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1770 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3655 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1773 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3662 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1776 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3669 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1779 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3676 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1782 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3683 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1785 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3690 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1788 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3697 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1791 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3704 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1794 "../Slice/Grammar.y" /* yacc.c:1646  */
    {
}
#line 3711 "Grammar.tab.c" /* yacc.c:1646  */
    break;


#line 3715 "Grammar.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
      yyerror (YY_("syntax error"));
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
#line 1798 "../Slice/Grammar.y" /* yacc.c:1906  */

