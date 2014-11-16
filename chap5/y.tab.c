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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "tiger.grm" /* yacc.c:339  */

#include <stdio.h>
#include "util.h"
#include "errormsg.h"
#include "table.h"
#include "symbol.h"
#include "absyn.h"
#include "prabsyn.h"
#include "types.h"
#include "env.h"
#include "semant.h"

int yylex(void); /* function prototype */

void yyerror(char *s)
{
 EM_error(EM_tokPos, "%s", s);
}

#line 86 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    ID = 258,
    STRING = 259,
    INT = 260,
    COMMA = 261,
    COLON = 262,
    SEMICOLON = 263,
    LPAREN = 264,
    RPAREN = 265,
    LBRACK = 266,
    RBRACK = 267,
    LBRACE = 268,
    RBRACE = 269,
    DOT = 270,
    ASSIGN = 271,
    ARRAY = 272,
    IF = 273,
    THEN = 274,
    ELSE = 275,
    WHILE = 276,
    FOR = 277,
    TO = 278,
    LET = 279,
    IN = 280,
    END = 281,
    OF = 282,
    DO = 283,
    BREAK = 284,
    NIL = 285,
    FUNCTION = 286,
    VAR = 287,
    TYPE = 288,
    EXCLAMATION = 289,
    OR = 290,
    AND = 291,
    EQ = 292,
    NEQ = 293,
    LT = 294,
    LE = 295,
    GT = 296,
    GE = 297,
    PLUS = 298,
    MINUS = 299,
    TIMES = 300,
    DIVIDE = 301,
    UMINUS = 302
  };
#endif
/* Tokens.  */
#define ID 258
#define STRING 259
#define INT 260
#define COMMA 261
#define COLON 262
#define SEMICOLON 263
#define LPAREN 264
#define RPAREN 265
#define LBRACK 266
#define RBRACK 267
#define LBRACE 268
#define RBRACE 269
#define DOT 270
#define ASSIGN 271
#define ARRAY 272
#define IF 273
#define THEN 274
#define ELSE 275
#define WHILE 276
#define FOR 277
#define TO 278
#define LET 279
#define IN 280
#define END 281
#define OF 282
#define DO 283
#define BREAK 284
#define NIL 285
#define FUNCTION 286
#define VAR 287
#define TYPE 288
#define EXCLAMATION 289
#define OR 290
#define AND 291
#define EQ 292
#define NEQ 293
#define LT 294
#define LE 295
#define GT 296
#define GE 297
#define PLUS 298
#define MINUS 299
#define TIMES 300
#define DIVIDE 301
#define UMINUS 302

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 22 "tiger.grm" /* yacc.c:355  */

	int			pos;
	int			ival;
	string		sval;
	A_var		var;
	A_exp		exp;
	A_expList	expList;
	A_decList	decList;
	A_dec		dec;
	A_ty		ty;
	A_namety	namety;
	A_nametyList	nametyList;
	A_fundec	funcdec;
	A_fundecList	funcdecList;
	A_field		field;
	A_fieldList fieldList;
	A_efield	efield; 
	A_efieldList	efieldList;
	

#line 241 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 256 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  53
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   277

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  160

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    82,    82,    90,    94,    98,   105,   109,   113,   117,
     121,   125,   129,   133,   137,   141,   145,   149,   153,   157,
     161,   165,   171,   175,   179,   183,   188,   194,   197,   203,
     206,   212,   216,   220,   224,   228,   232,   236,   240,   244,
     248,   252,   256,   262,   267,   271,   276,   279,   284,   287,
     293,   298,   301,   305,   309,   315,   320,   324,   330,   335,
     339,   343,   349,   354,   359,   364,   368,   373,   379,   384,
     388,   392,   396,   402,   407,   413,   417,   421,   425,   429,
     433,   438,   443,   446,   451,   454
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRING", "INT", "COMMA", "COLON",
  "SEMICOLON", "LPAREN", "RPAREN", "LBRACK", "RBRACK", "LBRACE", "RBRACE",
  "DOT", "ASSIGN", "ARRAY", "IF", "THEN", "ELSE", "WHILE", "FOR", "TO",
  "LET", "IN", "END", "OF", "DO", "BREAK", "NIL", "FUNCTION", "VAR",
  "TYPE", "EXCLAMATION", "OR", "AND", "EQ", "NEQ", "LT", "LE", "GT", "GE",
  "PLUS", "MINUS", "TIMES", "DIVIDE", "UMINUS", "$accept", "program",
  "lvalue", "exp", "varExp", "nilExp", "intExp", "stringExp", "callExp",
  "argList", "argList_", "binaryOpExp", "unaryOpExp", "recordCreateExp",
  "efield", "efieldList", "efieldList_", "seqExp", "seqList_", "seqList",
  "assignExp", "ifExp", "whileExp", "forExp", "breakExp", "letExp",
  "arrayCreateExp", "decs", "dec", "funcdec", "funcdecList", "funcdec_",
  "vardec", "tydec", "nametyList", "namety", "field", "fieldList",
  "fieldList_", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

#define YYPACT_NINF -46

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-46)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -2,    24,   -46,   -46,    -2,    -2,    -2,    10,   -23,   -46,
     -46,    -2,    26,     2,   211,   -46,   -46,   -46,   -46,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,
     -46,    -2,    -2,    36,    90,    30,   -46,    50,   180,    25,
      67,    68,    69,    48,   -23,   -46,   -46,    43,   -46,   -46,
     -46,    42,   -46,   -46,    73,    -2,    -2,    -2,    -2,    -2,
      -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,     8,
      70,   125,    44,    76,    83,    -2,   -46,    -2,    -2,    -2,
      74,     5,    47,    -2,   -46,   -46,   -46,   -46,   211,   211,
     149,   221,   231,   231,   231,   231,   231,   231,   -22,   -22,
     -46,   -46,    -2,   -46,   -46,    72,    -2,    36,   -46,   -46,
     -46,   137,   211,   161,    97,    98,    -2,    12,    77,     8,
      -2,   211,    76,    -2,    -2,   100,    99,    94,    92,   211,
     -46,    97,    82,   -46,   -46,   211,   -46,   211,   199,   107,
      97,   -46,    -3,    -2,   101,   108,    -2,   -46,    99,   109,
      -2,   211,   -46,   -46,   211,   -46,    80,   211,    -2,   211
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,    25,    24,    51,     0,     0,     0,     0,    60,
      23,     0,     0,    22,     2,     6,     7,     8,     9,    12,
      10,    11,    15,    13,    14,    17,    18,    19,    20,    21,
      16,    27,     0,    46,    53,     0,    52,     0,     0,     0,
       0,     0,     0,     0,    63,    65,    68,    69,    66,    67,
      75,    76,    43,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
       0,     0,     0,    48,     0,     0,    50,     0,     0,     0,
       0,     0,     0,     0,    64,    70,    77,     4,    55,     5,
      42,    41,    35,    36,    37,    38,    39,    40,    31,    32,
      33,    34,     0,    28,    26,     0,     0,     0,    47,    44,
      54,    57,    58,     0,    82,     0,     0,     0,     0,    29,
       0,    45,    48,     0,     0,     0,    84,     0,     0,    73,
      78,    82,     0,    61,    30,    62,    49,    56,     0,     0,
       0,    83,     0,     0,     0,     0,     0,    81,    84,     0,
       0,    74,    79,    80,    59,    85,     0,    72,     0,    71
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -46,   -46,   -46,     0,   -46,   -46,   -46,   -46,   -46,   -46,
      -6,   -46,   -46,   -46,     7,   -46,    -4,   -46,   -46,   -45,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,    75,   -46,   -46,
      91,   -46,   -46,   -46,    71,   -46,   -19,     9,    -9
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    12,    13,    34,    15,    16,    17,    18,    19,    70,
     103,    20,    21,    22,    73,    74,   108,    23,    35,    36,
      24,    25,    26,    27,    28,    29,    30,    43,    44,    45,
      46,    47,    48,    49,    50,    51,   126,   127,   141
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,     1,     2,     3,   149,    37,    38,     4,    40,    41,
      42,    52,   115,    39,   102,   130,     5,    54,    55,     6,
       7,   116,     8,    67,    68,   131,    53,     9,    10,   132,
     110,    69,    71,    31,   150,    32,    56,    33,   118,    72,
      76,    79,    11,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,    77,
      80,    81,    82,    83,    40,    42,    87,   111,   112,   113,
     104,   106,   107,   114,   117,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,   109,    75,   120,
     125,   128,   119,   133,   142,   140,   121,   139,   143,   145,
     147,   153,   156,   134,   122,   152,   129,   158,   136,    84,
     135,   148,    86,   137,   138,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,   105,    85,   155,
     144,     0,     0,   151,     0,     0,   154,     0,     0,     0,
     157,     0,     0,     0,     0,     0,     0,   123,   159,     0,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,   124,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    78,     0,
       0,     0,     0,     0,     0,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,   146,     0,     0,
       0,     0,     0,     0,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68
};

static const yytype_int16 yycheck[] =
{
       0,     3,     4,     5,     7,     5,     6,     9,    31,    32,
      33,    11,     7,     3,     6,     3,    18,    15,    16,    21,
      22,    16,    24,    45,    46,    13,     0,    29,    30,    17,
      75,    31,    32,     9,    37,    11,    34,    13,    83,     3,
      10,    16,    44,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    19,
       3,     3,     3,    25,    31,    33,     3,    77,    78,    79,
      10,    37,     6,     9,    37,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    14,     8,    27,
       3,     3,   102,    26,    10,     6,   106,     7,    16,    27,
       3,     3,     3,   119,   107,    14,   116,    37,   122,    44,
     120,   140,    51,   123,   124,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    12,    47,   148,
     131,    -1,    -1,   143,    -1,    -1,   146,    -1,    -1,    -1,
     150,    -1,    -1,    -1,    -1,    -1,    -1,    20,   158,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    23,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     9,    18,    21,    22,    24,    29,
      30,    44,    49,    50,    51,    52,    53,    54,    55,    56,
      59,    60,    61,    65,    68,    69,    70,    71,    72,    73,
      74,     9,    11,    13,    51,    66,    67,    51,    51,     3,
      31,    32,    33,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    51,     0,    15,    16,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    51,
      57,    51,     3,    62,    63,     8,    10,    19,    28,    16,
       3,     3,     3,    25,    75,    78,    82,     3,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,     6,    58,    10,    12,    37,     6,    64,    14,
      67,    51,    51,    51,     9,     7,    16,    37,    67,    51,
      27,    51,    62,    20,    23,     3,    84,    85,     3,    51,
       3,    13,    17,    26,    58,    51,    64,    51,    51,     7,
       6,    86,    10,    16,    85,    27,    28,     3,    84,     7,
      37,    51,    14,     3,    51,    86,     3,    51,    37,    51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    50,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    52,    53,    54,    55,    56,    57,    57,    58,
      58,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    60,    61,    62,    63,    63,    64,    64,
      65,    66,    66,    67,    67,    68,    69,    69,    70,    71,
      72,    73,    74,    75,    75,    76,    76,    76,    77,    78,
      78,    79,    79,    80,    80,    81,    82,    82,    83,    83,
      83,    84,    85,    85,    86,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     0,     2,     0,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     4,     3,     0,     2,     0,     3,
       3,     0,     1,     1,     3,     3,     6,     4,     4,     8,
       1,     5,     6,     1,     2,     1,     1,     1,     1,     1,
       2,     9,     7,     4,     6,     1,     1,     2,     4,     6,
       6,     3,     0,     2,     0,     3
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




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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
      yychar = yylex ();
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
#line 83 "tiger.grm" /* yacc.c:1646  */
    {
        pr_exp(stdout,(yyvsp[0].exp),4);
        SEM_transProg((yyvsp[0].exp));
        (yyval.exp) = (yyvsp[0].exp);
}
#line 1474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 91 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.var) = A_SimpleVar(EM_tokPos,S_Symbol((yyvsp[0].sval)));
}
#line 1482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 95 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.var) = A_FieldVar(EM_tokPos,(yyvsp[-2].var),S_Symbol((yyvsp[0].sval)));
}
#line 1490 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 99 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.var) = A_SubscriptVar(EM_tokPos,(yyvsp[-2].var),(yyvsp[0].exp));
}
#line 1498 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 106 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 110 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 114 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 118 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 122 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 126 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 130 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 134 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 138 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 142 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 146 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1586 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 150 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 154 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 158 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1610 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 162 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 166 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = (yyvsp[0].exp);
}
#line 1626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 172 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_VarExp(EM_tokPos,(yyvsp[0].var));
}
#line 1634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 176 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_NilExp(EM_tokPos);
}
#line 1642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 180 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_IntExp(EM_tokPos,(yyvsp[0].ival));
}
#line 1650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 184 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_StringExp(EM_tokPos,(yyvsp[0].sval));
}
#line 1658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 189 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_CallExp(EM_tokPos,S_Symbol((yyvsp[-3].sval)),(yyvsp[-1].expList));
}
#line 1666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 194 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.expList) = NULL;
}
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 198 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.expList) = A_ExpList((yyvsp[-1].exp),(yyvsp[0].expList));
}
#line 1682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 203 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.expList) = NULL;
}
#line 1690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 207 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.expList) = A_ExpList((yyvsp[-1].exp),(yyvsp[0].expList));
}
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 213 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_OpExp(EM_tokPos,A_plusOp,(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 217 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_OpExp(EM_tokPos,A_minusOp,(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1714 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 221 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_OpExp(EM_tokPos,A_timesOp,(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 225 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_OpExp(EM_tokPos,A_divideOp,(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1730 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 229 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_OpExp(EM_tokPos,A_eqOp,(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 233 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_OpExp(EM_tokPos,A_neqOp,(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 237 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_OpExp(EM_tokPos,A_ltOp,(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 241 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_OpExp(EM_tokPos,A_leOp,(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 245 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_OpExp(EM_tokPos,A_gtOp,(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 249 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_OpExp(EM_tokPos,A_geOp,(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 253 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_OpExp(EM_tokPos,A_andOp,(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 257 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_OpExp(EM_tokPos,A_orOp,(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 263 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_OpExp(EM_tokPos,A_orOp,A_IntExp(EM_tokPos,0),(yyvsp[0].exp));
}
#line 1802 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 268 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_RecordExp(EM_tokPos,S_Symbol((yyvsp[-3].sval)),(yyvsp[-1].efieldList));
}
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 272 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.efield) = A_Efield(S_Symbol((yyvsp[-2].sval)),(yyvsp[0].exp));
}
#line 1818 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 276 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.efieldList) = NULL;
}
#line 1826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 280 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.efieldList) = A_EfieldList((yyvsp[-1].efield),(yyvsp[0].efieldList));
}
#line 1834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 284 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.efieldList) = NULL;
}
#line 1842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 288 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.efieldList) = A_EfieldList((yyvsp[-1].efield),(yyvsp[0].efieldList));
}
#line 1850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 294 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_SeqExp(EM_tokPos,(yyvsp[-1].expList));
}
#line 1858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 298 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.expList) = NULL;
}
#line 1866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 302 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.expList) = (yyvsp[0].expList);
}
#line 1874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 306 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.expList) = A_ExpList((yyvsp[0].exp),NULL);
}
#line 1882 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 310 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.expList) = A_ExpList((yyvsp[-2].exp),(yyvsp[0].expList));
}
#line 1890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 316 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_AssignExp(EM_tokPos,(yyvsp[-2].var),(yyvsp[0].exp));
}
#line 1898 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 321 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_IfExp(EM_tokPos,(yyvsp[-4].exp),(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1906 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 325 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_IfExp(EM_tokPos,(yyvsp[-2].exp),(yyvsp[0].exp),NULL);
}
#line 1914 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 331 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_WhileExp(EM_tokPos,(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1922 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 336 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_ForExp(EM_tokPos,S_Symbol((yyvsp[-6].sval)),(yyvsp[-4].exp),(yyvsp[-2].exp),(yyvsp[0].exp));
}
#line 1930 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 340 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_BreakExp(EM_tokPos);
}
#line 1938 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 344 "tiger.grm" /* yacc.c:1646  */
    {

(yyval.exp) = A_LetExp(EM_tokPos,(yyvsp[-3].decList),(yyvsp[-1].expList));
}
#line 1947 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 350 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.exp) = A_ArrayExp(EM_tokPos,S_Symbol((yyvsp[-5].sval)),(yyvsp[-3].exp),(yyvsp[0].exp));
}
#line 1955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 355 "tiger.grm" /* yacc.c:1646  */
    {

(yyval.decList) = A_DecList((yyvsp[0].dec),NULL);
}
#line 1964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 360 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.decList) = A_DecList((yyvsp[-1].dec),(yyvsp[0].decList));
}
#line 1972 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 365 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.dec) = (yyvsp[0].dec);
}
#line 1980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 369 "tiger.grm" /* yacc.c:1646  */
    {

(yyval.dec) = (yyvsp[0].dec);
}
#line 1989 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 374 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.dec) = (yyvsp[0].dec);
}
#line 1997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 380 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.dec) = A_FunctionDec(EM_tokPos,(yyvsp[0].funcdecList));
}
#line 2005 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 385 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.funcdecList) = A_FundecList((yyvsp[0].funcdec),NULL);
}
#line 2013 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 389 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.funcdecList) = A_FundecList((yyvsp[-1].funcdec),(yyvsp[0].funcdecList));
}
#line 2021 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 393 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.funcdec) = A_Fundec(EM_tokPos,S_Symbol((yyvsp[-7].sval)),(yyvsp[-5].fieldList),S_Symbol((yyvsp[-2].sval)),(yyvsp[0].exp));
}
#line 2029 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 397 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.funcdec) = A_Fundec(EM_tokPos,S_Symbol((yyvsp[-5].sval)),(yyvsp[-3].fieldList),NULL,(yyvsp[0].exp));
}
#line 2037 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 403 "tiger.grm" /* yacc.c:1646  */
    {

(yyval.dec) = A_VarDec(EM_tokPos,S_Symbol((yyvsp[-2].sval)),NULL,(yyvsp[0].exp));
}
#line 2046 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 408 "tiger.grm" /* yacc.c:1646  */
    {

(yyval.dec) = A_VarDec(EM_tokPos,S_Symbol((yyvsp[-4].sval)),S_Symbol((yyvsp[-2].sval)),(yyvsp[0].exp));
}
#line 2055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 414 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.dec) = A_TypeDec(EM_tokPos,(yyvsp[0].nametyList));
}
#line 2063 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 418 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.nametyList) = A_NametyList((yyvsp[0].namety),NULL);
}
#line 2071 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 422 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.nametyList) = A_NametyList((yyvsp[-1].namety),(yyvsp[0].nametyList));
}
#line 2079 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 426 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.namety) = A_Namety(S_Symbol((yyvsp[-2].sval)),A_NameTy(EM_tokPos,S_Symbol((yyvsp[0].sval))));
}
#line 2087 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 430 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.namety) = A_Namety(S_Symbol((yyvsp[-4].sval)),A_RecordTy(EM_tokPos,(yyvsp[-1].fieldList)));
}
#line 2095 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 434 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.namety) = A_Namety(S_Symbol((yyvsp[-4].sval)),A_ArrayTy(EM_tokPos,S_Symbol((yyvsp[0].sval))));
}
#line 2103 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 439 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.field) = A_Field(EM_tokPos,S_Symbol((yyvsp[-2].sval)),S_Symbol((yyvsp[0].sval)));
}
#line 2111 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 443 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.fieldList) = NULL;
}
#line 2119 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 447 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.fieldList) = A_FieldList((yyvsp[-1].field),(yyvsp[0].fieldList));
}
#line 2127 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 451 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.fieldList) = NULL;
}
#line 2135 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 455 "tiger.grm" /* yacc.c:1646  */
    {
(yyval.fieldList) = A_FieldList((yyvsp[-1].field),(yyvsp[0].fieldList));
}
#line 2143 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2147 "y.tab.c" /* yacc.c:1646  */
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
