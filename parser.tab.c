/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

	#include <stdio.h>
	extern "C" void yyerror (char *s);
	extern int yylex(void);
	extern int yylineno;
	Symbol_Table *local_symbol_table, *global_symbol_table, *formal_param_table;
	int param_number = 0;
	string curr_proc_name = "";
	string dummy_param_name = "";
	// is_main = false;
	Data_Type my_get_data_type(int type){
		Data_Type dt = void_data_type;
		if(type == 1){
			dt = int_data_type;
		}
		else if(type == 2){
			dt = double_data_type;
		}
		return dt;
	}

#line 88 "parser.tab.c" /* yacc.c:339  */

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
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    INTEGER = 258,
    FLOAT = 259,
    ASSIGN = 260,
    VOID = 261,
    NAME = 262,
    INTEGER_NUMBER = 263,
    DOUBLE_NUMBER = 264,
    IF = 265,
    ELSE = 266,
    DO = 267,
    WHILE = 268,
    LESS_THAN = 269,
    LESS_THAN_EQUAL = 270,
    GREATER_THAN = 271,
    GREATER_THAN_EQUAL = 272,
    EQUAL = 273,
    NOT_EQUAL = 274,
    AND = 275,
    OR = 276,
    NOT = 277,
    UMINUS = 278,
    PRINT = 279,
    RETURN = 280,
    NO_ELSE = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 35 "parser.y" /* yacc.c:355  */

	int integer_value;
	double double_value;
	std::string * string_value;
	list<Ast *> * ast_list;
	Ast * ast;
	Symbol_Table * symbol_table;
	Symbol_Table_Entry * symbol_entry;
	list<Symbol_Table_Entry *> * symbol_list;
	Procedure * procedure;

#line 167 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 184 "parser.tab.c" /* yacc.c:358  */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   232

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  148

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

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
      33,    34,    30,    28,    38,    29,     2,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    27,    35,
       2,     2,     2,    26,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
      25,    32
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    75,    75,    75,   104,   108,   114,   113,   124,   128,
     135,   157,   170,   168,   226,   230,   236,   243,   260,   279,
     295,   314,   319,   325,   330,   339,   360,   365,   370,   377,
     387,   400,   405,   414,   429,   435,   439,   443,   447,   451,
     455,   459,   465,   470,   480,   489,   498,   505,   517,   524,
     530,   544,   560,   566,   572,   578,   582,   589,   596,   602,
     608,   614,   620,   628,   650,   654,   659,   665,   672,   678,
     685,   692,   699,   706,   713,   718,   723,   730,   768,   774
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "FLOAT", "ASSIGN", "VOID",
  "NAME", "INTEGER_NUMBER", "DOUBLE_NUMBER", "IF", "ELSE", "DO", "WHILE",
  "LESS_THAN", "LESS_THAN_EQUAL", "GREATER_THAN", "GREATER_THAN_EQUAL",
  "EQUAL", "NOT_EQUAL", "AND", "OR", "NOT", "UMINUS", "PRINT", "RETURN",
  "'?'", "':'", "'+'", "'-'", "'*'", "'/'", "NO_ELSE", "'('", "')'", "';'",
  "'{'", "'}'", "','", "$accept", "Prog", "$@1", "All_List", "$@2",
  "Proc_Def_List", "Proc_Init", "Proc_Dec", "Proc_Def", "$@3",
  "Param_List", "Param_Type_List", "Param_List1", "Var_Dec_List",
  "Var_Dec_List1", "Var_Dec", "Type", "Var_List", "Stmt_List",
  "Stmt_block", "Single_Stmt", "If_block", "Do_While_block", "While_block",
  "Assng_stmt", "Prnt_stmt", "Call_stmt", "Retr_stmt", "Log_Expr",
  "Rel_Expr", "Call_expr", "Expr_List", "Expr_List1", "Expr", "Var",
  "Const", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    63,    58,    43,    45,
      42,    47,   281,    40,    41,    59,   123,   125,    44
};
# endif

#define YYPACT_NINF -56

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-56)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -56,    13,    78,   -56,   -56,   -56,   -56,   -56,   -56,    -6,
      78,    78,   -56,     3,   -56,    78,   -56,   -56,   -20,    16,
      78,    -2,   -32,   -56,    78,   -56,    27,    -2,   -56,    78,
     -56,    35,   -56,   -56,   -56,    14,     9,    11,    44,   -56,
      63,   -56,    78,    78,   -56,    34,    50,    99,    52,    61,
      17,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,
     -56,   -56,    42,    81,   -56,    82,   107,   107,    79,   107,
     -56,    56,   -56,   -56,   107,   107,   107,   -56,    12,   -56,
     128,   -56,   -56,    83,   -56,   119,   -56,    64,    75,   185,
      45,   185,    68,    84,   -56,   -56,   -56,   191,   158,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   -56,   -56,    67,   150,   -56,   107,    99,   107,
      99,   -56,   -56,   -56,    97,   179,   185,   185,   185,   185,
     185,   185,    10,    10,   -56,   -56,   -56,   -56,   185,   110,
     198,   -56,   107,    99,    87,   185,   -56,   -56
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,    27,    28,    26,     3,     4,     0,
       0,     8,     6,     0,    11,    21,     5,     9,     0,     0,
       0,    29,     0,    12,    22,    23,     0,     0,     7,    14,
      25,     0,    31,    24,    29,     0,    15,    16,    17,    30,
       0,    10,     0,     0,    19,    77,     0,     0,     0,     0,
       0,    31,    13,    32,    34,    35,    37,    36,    38,    39,
      40,    41,     0,     0,    18,     0,    64,     0,     0,     0,
      77,     0,    78,    79,     0,     0,     0,    51,     0,    56,
       0,    75,    76,     0,    49,     0,    20,     0,    65,    66,
       0,     0,     0,     0,    48,    54,    73,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    33,     0,     0,    63,     0,     0,     0,
       0,    55,    74,    53,    52,     0,    57,    58,    59,    60,
      61,    62,    69,    70,    71,    72,    47,    46,    67,    42,
       0,    45,     0,     0,     0,    68,    43,    44
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -56,   -56,   -56,    -5,   -56,   114,   120,   -56,   -56,   -56,
     -56,   -56,   -56,   -56,   -56,    -4,    -7,   -56,    86,   -46,
     -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   -55,   -56,
      47,   -56,   -56,   -48,   -40,   -56
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     7,    20,     8,     9,    10,    11,    32,
      35,    36,    37,    23,    24,    12,    13,    22,    40,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    78,    79,
      62,    87,    88,    91,    81,    82
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      63,    68,    80,    30,    19,    16,    31,    63,    26,    71,
      21,    25,    90,     3,    93,    28,    15,    26,    89,    95,
      33,    97,    38,    27,    70,    72,    73,    96,    98,    14,
      15,    29,    99,   100,    34,    64,    65,   115,   101,    74,
     110,   111,    39,    63,   123,   124,    75,    42,    41,    43,
      76,    44,    77,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   140,    99,   100,    66,    70,   138,
      45,   101,   139,    46,   141,    47,    48,    84,    63,   118,
      63,     4,     5,    67,     6,    69,    85,    49,    50,    86,
      45,    94,    92,    46,   145,    47,    48,   146,   116,    51,
      52,   119,   136,    63,    99,   100,    45,    49,    50,    46,
     101,    47,    48,   117,    70,    72,    73,    99,   120,    51,
     113,   143,   147,    49,    50,    17,    45,    72,    73,    74,
       0,    18,   114,     0,     0,    51,    75,    83,     0,     0,
      76,    74,   102,   103,   104,   105,   106,   107,    75,     0,
       0,     0,    76,     0,     0,     0,   108,   109,   110,   111,
       0,     0,     0,   112,   102,   103,   104,   105,   106,   107,
       0,     0,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,     0,     0,     0,   137,   108,   109,   110,   111,
       0,     0,   122,   102,   103,   104,   105,   106,   107,   102,
     103,   104,   105,   106,   107,     0,   142,   108,   109,   110,
     111,    99,   100,   108,   109,   110,   111,   101,    99,   100,
       0,     0,     0,     0,   101,   121,     0,     0,     0,     0,
       0,     0,   144
};

static const yytype_int16 yycheck[] =
{
      40,    47,    50,    35,    11,    10,    38,    47,    15,    49,
       7,    15,    67,     0,    69,    20,    36,    24,    66,    74,
      24,    76,    29,     7,     7,     8,     9,    75,    76,    35,
      36,    33,    20,    21,     7,    42,    43,    85,    26,    22,
      30,    31,     7,    83,    99,   100,    29,    38,    34,    38,
      33,     7,    35,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   119,    20,    21,    33,     7,   117,
       7,    26,   118,    10,   120,    12,    13,    35,   118,    34,
     120,     3,     4,    33,     6,    33,     5,    24,    25,     7,
       7,    35,    13,    10,   142,    12,    13,   143,    34,    36,
      37,    33,    35,   143,    20,    21,     7,    24,    25,    10,
      26,    12,    13,    38,     7,     8,     9,    20,    34,    36,
      37,    11,    35,    24,    25,    11,     7,     8,     9,    22,
      -1,    11,    85,    -1,    -1,    36,    29,    51,    -1,    -1,
      33,    22,    14,    15,    16,    17,    18,    19,    29,    -1,
      -1,    -1,    33,    -1,    -1,    -1,    28,    29,    30,    31,
      -1,    -1,    -1,    35,    14,    15,    16,    17,    18,    19,
      -1,    -1,    14,    15,    16,    17,    18,    19,    28,    29,
      30,    31,    -1,    -1,    -1,    35,    28,    29,    30,    31,
      -1,    -1,    34,    14,    15,    16,    17,    18,    19,    14,
      15,    16,    17,    18,    19,    -1,    27,    28,    29,    30,
      31,    20,    21,    28,    29,    30,    31,    26,    20,    21,
      -1,    -1,    -1,    -1,    26,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    40,    41,     0,     3,     4,     6,    42,    44,    45,
      46,    47,    54,    55,    35,    36,    42,    44,    45,    55,
      43,     7,    56,    52,    53,    54,    55,     7,    42,    33,
      35,    38,    48,    54,     7,    49,    50,    51,    55,     7,
      57,    34,    38,    38,     7,     7,    10,    12,    13,    24,
      25,    36,    37,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    69,    73,    55,    55,    33,    33,    58,    33,
       7,    73,     8,     9,    22,    29,    33,    35,    67,    68,
      72,    73,    74,    57,    35,     5,     7,    70,    71,    72,
      67,    72,    13,    67,    35,    67,    72,    67,    72,    20,
      21,    26,    14,    15,    16,    17,    18,    19,    28,    29,
      30,    31,    35,    37,    69,    72,    34,    38,    34,    33,
      34,    34,    34,    67,    67,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    35,    35,    72,    58,
      67,    58,    27,    11,    34,    72,    58,    35
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    41,    40,    42,    42,    43,    42,    44,    44,
      45,    46,    48,    47,    49,    49,    49,    50,    50,    51,
      51,    52,    52,    53,    53,    54,    55,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    59,    59,    59,    59,
      59,    59,    60,    60,    61,    62,    63,    63,    64,    65,
      66,    66,    67,    67,    67,    67,    67,    68,    68,    68,
      68,    68,    68,    69,    70,    70,    71,    71,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    73,    74,    74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     0,     3,     1,     2,
       5,     2,     0,     6,     0,     1,     1,     1,     3,     2,
       4,     0,     1,     1,     2,     3,     1,     1,     1,     1,
       3,     0,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     7,     7,     5,     4,     4,     3,     2,
       3,     2,     3,     3,     2,     3,     1,     3,     3,     3,
       3,     3,     3,     4,     0,     1,     1,     3,     5,     3,
       3,     3,     3,     2,     3,     1,     1,     1,     1,     1
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
#line 75 "parser.y" /* yacc.c:1646  */
    {
				global_symbol_table = new Symbol_Table();
			}
#line 1383 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 79 "parser.y" /* yacc.c:1646  */
    {
				// printf("Prog\n");
				string main_name = "main";
				if(program_object.is_procedure_exists(main_name)){
					Procedure * procedure = program_object.get_procedure_prototype(main_name);
					if(!procedure->get_return_type() == void_data_type){
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Main should be defined and it's type should be void", yylineno);
						yyerror(err);
						exit(-1);	
					}
				}
				else{
					char err[100];
					sprintf(err, "cs316: Error: Line: %d: Main should be defined and it's type should be void", yylineno);
					yyerror(err);
					exit(-1);
				}
				// cout<<"Here111111"<<endl;
				global_symbol_table->set_table_scope(global);
				program_object.set_global_table(*global_symbol_table);
				// cout<<"Here222222"<<endl;
			}
#line 1411 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 105 "parser.y" /* yacc.c:1646  */
    {
					// printf("All_List-1\n");
				}
#line 1419 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 110 "parser.y" /* yacc.c:1646  */
    {
					// printf("All_List-2\n");
				}
#line 1427 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 114 "parser.y" /* yacc.c:1646  */
    {
					// printf("All_List-3-1/2\n");
					global_symbol_table->append_list(*(yyvsp[0].symbol_table), yylineno);
				}
#line 1436 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 119 "parser.y" /* yacc.c:1646  */
    {
					// printf("All_List-3\n");
				}
#line 1444 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 125 "parser.y" /* yacc.c:1646  */
    {
						/*Nothing Required*/
					}
#line 1452 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 130 "parser.y" /* yacc.c:1646  */
    {
						/*Nothing Required*/
					}
#line 1460 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 136 "parser.y" /* yacc.c:1646  */
    {
					Data_Type return_type = my_get_data_type((yyvsp[-4].integer_value));
					std::string name = *(yyvsp[-3].string_value);
					if(name == "main"){
						// is_main = true;
					}
					else{
						name += "_";
					}
					if(global_symbol_table->variable_in_symbol_list_check(name)){
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Procedure name cannot be same as global variable", yylineno);
						yyerror(err);
						exit(-1);
					}
					curr_proc_name = name;
					Procedure * procedure = new Procedure(return_type, name, yylineno);
					formal_param_table = (yyvsp[-1].symbol_table);
					(yyval.procedure) = procedure;
				}
#line 1485 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 158 "parser.y" /* yacc.c:1646  */
    {
					Procedure *procedure = (yyvsp[-1].procedure);
					string proc_name = procedure->get_proc_name();
					formal_param_table->set_table_scope(formal);
					procedure->set_formal_param_list(*formal_param_table);
					program_object.set_proc_to_map(proc_name, procedure);
					(yyval.procedure) = procedure;
				}
#line 1498 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 170 "parser.y" /* yacc.c:1646  */
    {
					// printf("Proc_Def-1/2\n");
					Procedure *procedure = (yyvsp[-2].procedure);
					// cout<<"here11111"<<endl;
					string proc_name = procedure->get_proc_name();
					if(program_object.is_procedure_exists(proc_name)){
						// cout<<"here22222"<<endl;
						procedure = program_object.get_procedure_prototype(proc_name);
						if(procedure->is_proc_defined()){
							char err[100];
							sprintf(err, "cs316: Error: Line: %d: Current procedure already defined", yylineno);
							yyerror(err);
							exit(-1);
						}
						else{
							if(procedure->get_return_type() != (yyvsp[-2].procedure)->get_return_type()){
								char err[100];
								sprintf(err, "cs316: Error: Line: %d: return type in declaration and definition not matching", yylineno);
								yyerror(err);
								exit(-1);
							}
							procedure->set_proc_is_defined();
							if(formal_param_table->is_empty()){
								formal_param_table = &(procedure->get_formal_param_list());
							}
							string param1 = dummy_param_name+"1_";
							if(formal_param_table->variable_in_symbol_list_check(param1)){
								char err[100];
								sprintf(err, "cs316: Error: Line: %d: Variable name missing in parameter list", yylineno);
								yyerror(err);
								exit(-1);
							}
						}
						(yyvsp[-2].procedure) = procedure;
					}
					else{
						program_object.set_proc_to_map(proc_name, procedure);
					}
					formal_param_table->set_table_scope(formal);
					procedure->set_formal_param_list(*formal_param_table);
					local_symbol_table = (yyvsp[0].symbol_table);
					local_symbol_table->set_table_scope(local);
					procedure->set_local_list(*local_symbol_table);
					// cout<<"here444444"<<endl;
				}
#line 1548 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 217 "parser.y" /* yacc.c:1646  */
    {
					// printf("Proc_Def\n");
					Procedure *procedure = (yyvsp[-5].procedure);
					procedure->set_ast_list(*(yyvsp[-1].ast_list));
					(yyval.procedure) = procedure;
				}
#line 1559 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 226 "parser.y" /* yacc.c:1646  */
    {
					// printf("Param_List-1\n");
					(yyval.symbol_table) = new Symbol_Table();
				}
#line 1568 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 231 "parser.y" /* yacc.c:1646  */
    {
					// printf("Param_List-2\n");
					(yyval.symbol_table) = (yyvsp[0].symbol_table);
					param_number = 0;
				}
#line 1578 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 237 "parser.y" /* yacc.c:1646  */
    {
					// printf("Param_List-3\n");
					(yyval.symbol_table) = (yyvsp[0].symbol_table);
				}
#line 1587 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 244 "parser.y" /* yacc.c:1646  */
    {
						// printf("Param_Type_List-1\n");
						param_number++;
						Data_Type param_type = my_get_data_type((yyvsp[0].integer_value));
						if(param_type == void_data_type){
							char err[100];
							sprintf(err, "cs316: Error: Line: %d: Variable data type cannot be void", yylineno);
							yyerror(err);
							exit(-1);
						}
						string name = dummy_param_name + to_string(param_number) + "_";
						Symbol_Table_Entry *var = new Symbol_Table_Entry(name, param_type, yylineno);
						Symbol_Table * sym_tbl = new Symbol_Table();
						sym_tbl->push_symbol(var);
						(yyval.symbol_table) = sym_tbl;
					}
#line 1608 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 261 "parser.y" /* yacc.c:1646  */
    {
						// printf("Param_Type_List-2\n");
						param_number++;
						Data_Type param_type = my_get_data_type((yyvsp[0].integer_value));
						if(param_type == void_data_type){
							char err[100];
							sprintf(err, "cs316: Error: Line: %d: Variable data type cannot be void", yylineno);
							yyerror(err);
							exit(-1);
						}
						string name = dummy_param_name + to_string(param_number) + "_";
						Symbol_Table_Entry *var = new Symbol_Table_Entry(name, param_type, yylineno);
						Symbol_Table * sym_tbl = (yyvsp[-2].symbol_table);
						sym_tbl->push_symbol(var);
						(yyval.symbol_table) = sym_tbl;
					}
#line 1629 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 280 "parser.y" /* yacc.c:1646  */
    {
					// printf("Param_List1-1\n");
					Data_Type param_type = my_get_data_type((yyvsp[-1].integer_value));
					if(param_type == void_data_type){
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Variable data type cannot be void", yylineno);
						yyerror(err);
						exit(-1);
					}
					string name = *(yyvsp[0].string_value) + "_";
					Symbol_Table_Entry *var = new Symbol_Table_Entry(name, param_type, yylineno);
					Symbol_Table * sym_tbl = new Symbol_Table();
					sym_tbl->push_symbol(var);
					(yyval.symbol_table) = sym_tbl;
				}
#line 1649 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 296 "parser.y" /* yacc.c:1646  */
    {
					// printf("Param_List1-2\n");
					Data_Type param_type = my_get_data_type((yyvsp[-1].integer_value));
					if(param_type == void_data_type){
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Variable data type cannot be void", yylineno);
						yyerror(err);
						exit(-1);
					}
					string name = *(yyvsp[0].string_value) + "_";
					Symbol_Table_Entry *var = new Symbol_Table_Entry(name, param_type, yylineno);
					Symbol_Table * sym_tbl = (yyvsp[-3].symbol_table);
					sym_tbl->push_symbol(var);
					(yyval.symbol_table) = sym_tbl;
				}
#line 1669 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 314 "parser.y" /* yacc.c:1646  */
    {
						// printf("Var_Dec_List-1\n");
						Symbol_Table * sym_tbl = new Symbol_Table();
						(yyval.symbol_table) = sym_tbl;
					}
#line 1679 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 320 "parser.y" /* yacc.c:1646  */
    {
						(yyval.symbol_table) = (yyvsp[0].symbol_table);
					}
#line 1687 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 326 "parser.y" /* yacc.c:1646  */
    {
						//printf("Var_Dec_List-1\n");
						(yyval.symbol_table) = (yyvsp[0].symbol_table);
					}
#line 1696 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 332 "parser.y" /* yacc.c:1646  */
    {
						//printf("Var_Dec_List-2\n");
						(yyvsp[-1].symbol_table)->append_list(*(yyvsp[0].symbol_table),yylineno);
						(yyval.symbol_table) = (yyvsp[-1].symbol_table);
					}
#line 1706 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 340 "parser.y" /* yacc.c:1646  */
    {
					//printf("Dec-1\n");
					list<Symbol_Table_Entry*> *var_sym_list = (yyvsp[-1].symbol_list);
					// var_sym_list->reverse();
					Data_Type var_type = my_get_data_type((yyvsp[-2].integer_value));
					if(var_type == void_data_type){
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Variable data type cannot be void", yylineno);
						yyerror(err);
						exit(-1);
					}
					Symbol_Table * sym_tbl = new Symbol_Table();
					for (list<Symbol_Table_Entry*>::iterator it = var_sym_list->begin(); it !=var_sym_list->end(); ++it){
						(*it)->set_data_type(var_type);
						sym_tbl->push_symbol(*it);
					}
					(yyval.symbol_table) = sym_tbl;
				}
#line 1729 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 361 "parser.y" /* yacc.c:1646  */
    {
				// printf("Type-1\n");
				(yyval.integer_value) = 0;
			}
#line 1738 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 366 "parser.y" /* yacc.c:1646  */
    {
				// printf("Type-2\n");
				(yyval.integer_value) = 1;
			}
#line 1747 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 371 "parser.y" /* yacc.c:1646  */
    {
				// printf("Type-3\n");
				(yyval.integer_value) = 2;
			}
#line 1756 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 378 "parser.y" /* yacc.c:1646  */
    {
					// printf("Var_List-1\n");
					// string name = *$1;
					string name = *(yyvsp[0].string_value) + "_";
					Symbol_Table_Entry *var = new Symbol_Table_Entry(name, void_data_type, yylineno);
					list<Symbol_Table_Entry*> *var_sym_list = new list<Symbol_Table_Entry*>();
					var_sym_list->push_back(var);
					(yyval.symbol_list) = var_sym_list;
				}
#line 1770 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 388 "parser.y" /* yacc.c:1646  */
    {
					// printf("Var_List-2\n");
					list<Symbol_Table_Entry*> *var_sym_list = (yyvsp[-2].symbol_list);
					// string name = *$3;
					string name = *(yyvsp[0].string_value) + "_";
					Symbol_Table_Entry *var = new Symbol_Table_Entry(name, void_data_type, yylineno);
					var_sym_list->push_back(var);
					(yyval.symbol_list) = var_sym_list;
				}
#line 1784 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 400 "parser.y" /* yacc.c:1646  */
    {
					// printf("Stmt_List-1\n");
					list<Ast*> *ast = new list<Ast*>();
					(yyval.ast_list) = ast;
				}
#line 1794 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 406 "parser.y" /* yacc.c:1646  */
    {
					// printf("Stmt_List-2\n");
					(yyvsp[-1].ast_list)->push_back((yyvsp[0].ast));
					(yyval.ast_list) = (yyvsp[-1].ast_list);
				}
#line 1804 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 415 "parser.y" /* yacc.c:1646  */
    {
					Sequence_Ast *seq_ast = new Sequence_Ast(yylineno);
					list<Ast*> *stmt_list = (yyvsp[-1].ast_list);
					if(stmt_list->empty()){
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: BLock of statements cannot be empty", yylineno);
						yyerror(err);
						exit(-1);
					}
					for (list<Ast*>::iterator it = stmt_list->begin(); it !=stmt_list->end(); ++it){
						seq_ast->ast_push_back(*it);
					}
					(yyval.ast) = seq_ast;
				}
#line 1823 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 430 "parser.y" /* yacc.c:1646  */
    {
					(yyval.ast) = (yyvsp[0].ast);
				}
#line 1831 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 436 "parser.y" /* yacc.c:1646  */
    {
						(yyval.ast) = (yyvsp[0].ast);
					}
#line 1839 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 440 "parser.y" /* yacc.c:1646  */
    {
						(yyval.ast) = (yyvsp[0].ast);
					}
#line 1847 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 444 "parser.y" /* yacc.c:1646  */
    {
						(yyval.ast) = (yyvsp[0].ast);
					}
#line 1855 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 448 "parser.y" /* yacc.c:1646  */
    {
						(yyval.ast) = (yyvsp[0].ast);	
					}
#line 1863 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 452 "parser.y" /* yacc.c:1646  */
    {
						(yyval.ast) = (yyvsp[0].ast);
					}
#line 1871 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 456 "parser.y" /* yacc.c:1646  */
    {
						(yyval.ast) = (yyvsp[0].ast);
					}
#line 1879 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 460 "parser.y" /* yacc.c:1646  */
    {
						(yyval.ast) = (yyvsp[0].ast);
					}
#line 1887 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 466 "parser.y" /* yacc.c:1646  */
    {
					Selection_Statement_Ast *if_ast = new Selection_Statement_Ast((yyvsp[-2].ast), (yyvsp[0].ast), NULL, yylineno);
					(yyval.ast) = if_ast;
				}
#line 1896 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 474 "parser.y" /* yacc.c:1646  */
    {
					Selection_Statement_Ast *if_else_ast = new Selection_Statement_Ast((yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast), yylineno);
					(yyval.ast) = if_else_ast;
				}
#line 1905 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 483 "parser.y" /* yacc.c:1646  */
    {
						Iteration_Statement_Ast *do_whl_ast = new Iteration_Statement_Ast((yyvsp[-2].ast), (yyvsp[-5].ast), yylineno, true);
						(yyval.ast) = do_whl_ast;
					}
#line 1914 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 491 "parser.y" /* yacc.c:1646  */
    {
						Iteration_Statement_Ast *whl_ast = new Iteration_Statement_Ast((yyvsp[-2].ast), (yyvsp[0].ast), yylineno, false);
						(yyval.ast) = whl_ast;
					}
#line 1923 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 499 "parser.y" /* yacc.c:1646  */
    {
					// printf("Assng_stmt\n");
					Assignment_Ast *assign_ast = new Assignment_Ast((yyvsp[-3].ast), (yyvsp[-1].ast), yylineno);
					assign_ast->check_ast();
					(yyval.ast) = assign_ast;
				}
#line 1934 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 506 "parser.y" /* yacc.c:1646  */
    {
					// printf("Assng_stmt\n");
					Call_Ast *call_ast = (Call_Ast*)(yyvsp[-1].ast);
					Register_Descriptor *ret_reg = new Register_Descriptor();
					call_ast->set_register(ret_reg);
					Assignment_Ast *assign_ast = new Assignment_Ast((yyvsp[-3].ast), call_ast, yylineno);
					assign_ast->check_ast();
					(yyval.ast) = assign_ast;
				}
#line 1948 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 518 "parser.y" /* yacc.c:1646  */
    {
					Print_Ast *prnt_ast = new Print_Ast((yyvsp[-1].ast), yylineno);
					(yyval.ast) = prnt_ast;
				}
#line 1957 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 525 "parser.y" /* yacc.c:1646  */
    {
					(yyval.ast) = (yyvsp[-1].ast);
				}
#line 1965 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 531 "parser.y" /* yacc.c:1646  */
    {
					Procedure *procedure = program_object.get_procedure_prototype(curr_proc_name);
					if(procedure->get_return_type() == (yyvsp[-1].ast)->get_data_type()){
						Return_Ast *retr_ast = new Return_Ast((yyvsp[-1].ast),curr_proc_name, yylineno);
						(yyval.ast) = retr_ast;
					}
					else{
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Return type not matching", yylineno);
						yyerror(err);
						exit(-1);
					}
				}
#line 1983 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 545 "parser.y" /* yacc.c:1646  */
    {
					Procedure *procedure = program_object.get_procedure_prototype(curr_proc_name);
					if(procedure->get_return_type() == void_data_type){
						Ast *ast = NULL;
						Return_Ast *retr_ast = new Return_Ast(ast, curr_proc_name, yylineno);
						(yyval.ast) = retr_ast;
					}
					else{
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Return type not matching", yylineno);
						yyerror(err);
						exit(-1);
					}
				}
#line 2002 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 561 "parser.y" /* yacc.c:1646  */
    {
					Logical_Expr_Ast *and_ast = new Logical_Expr_Ast((yyvsp[-2].ast), _logical_or, (yyvsp[0].ast), yylineno);
					and_ast->check_ast();
					(yyval.ast) = and_ast;
				}
#line 2012 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 567 "parser.y" /* yacc.c:1646  */
    {
					Logical_Expr_Ast *or_ast = new Logical_Expr_Ast((yyvsp[-2].ast), _logical_and, (yyvsp[0].ast), yylineno);
					or_ast->check_ast();
					(yyval.ast) = or_ast;
				}
#line 2022 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 573 "parser.y" /* yacc.c:1646  */
    {
					Logical_Expr_Ast *not_ast = new Logical_Expr_Ast(NULL, _logical_not, (yyvsp[0].ast), yylineno);
					not_ast->check_ast();
					(yyval.ast) = not_ast;
				}
#line 2032 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 579 "parser.y" /* yacc.c:1646  */
    {
					(yyval.ast) = (yyvsp[-1].ast);
				}
#line 2040 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 583 "parser.y" /* yacc.c:1646  */
    {
					// printf("Log_Expr_b-2\n");
					(yyval.ast) = (yyvsp[0].ast);
				}
#line 2049 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 590 "parser.y" /* yacc.c:1646  */
    {
					// printf("Rel_Expr-1\n");
					Relational_Expr_Ast *lt_ast = new Relational_Expr_Ast((yyvsp[-2].ast), less_than, (yyvsp[0].ast), yylineno);
					lt_ast->check_ast();
					(yyval.ast) = lt_ast;
				}
#line 2060 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 597 "parser.y" /* yacc.c:1646  */
    {
					Relational_Expr_Ast *lte_ast = new Relational_Expr_Ast((yyvsp[-2].ast), less_equalto, (yyvsp[0].ast), yylineno);
					lte_ast->check_ast();
					(yyval.ast) = lte_ast;
				}
#line 2070 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 603 "parser.y" /* yacc.c:1646  */
    {
					Relational_Expr_Ast *gt_ast = new Relational_Expr_Ast((yyvsp[-2].ast), greater_than, (yyvsp[0].ast), yylineno);
					gt_ast->check_ast();
					(yyval.ast) = gt_ast;
				}
#line 2080 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 609 "parser.y" /* yacc.c:1646  */
    {
					Relational_Expr_Ast *gte_ast = new Relational_Expr_Ast((yyvsp[-2].ast), greater_equalto, (yyvsp[0].ast), yylineno);
					gte_ast->check_ast();
					(yyval.ast) = gte_ast;
				}
#line 2090 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 615 "parser.y" /* yacc.c:1646  */
    {
					Relational_Expr_Ast *e_ast = new Relational_Expr_Ast((yyvsp[-2].ast), equalto, (yyvsp[0].ast), yylineno);
					e_ast->check_ast();
					(yyval.ast) = e_ast;	
				}
#line 2100 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 621 "parser.y" /* yacc.c:1646  */
    {
					Relational_Expr_Ast *ne_ast = new Relational_Expr_Ast((yyvsp[-2].ast), not_equalto, (yyvsp[0].ast), yylineno);
					ne_ast->check_ast();
					(yyval.ast) = ne_ast;
				}
#line 2110 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 629 "parser.y" /* yacc.c:1646  */
    {
					string proc_name = *(yyvsp[-3].string_value) + "_";
					if(program_object.is_procedure_exists(proc_name)){
						Procedure *procedure = program_object.get_procedure_prototype(proc_name);
						procedure->set_proc_is_called();
						Symbol_Table *formal_param_list = &(procedure->get_formal_param_list());
						Call_Ast *call_ast = new Call_Ast(proc_name, yylineno);
						call_ast->set_actual_param_list(*(yyvsp[-1].ast_list));
						call_ast->check_actual_formal_param(*formal_param_list);
						(yyval.ast) = call_ast;
					}
					else{
						char err[100];
						sprintf(err, "cs316: Error: Line: %d: Called procedure does not exist", yylineno);
						yyerror(err);
						exit(-1);
					}
				}
#line 2133 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 650 "parser.y" /* yacc.c:1646  */
    {
					list<Ast*> *list_ast = new list<Ast*>();
					(yyval.ast_list) = list_ast;
				}
#line 2142 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 655 "parser.y" /* yacc.c:1646  */
    {
					(yyval.ast_list) = (yyvsp[0].ast_list);
				}
#line 2150 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 660 "parser.y" /* yacc.c:1646  */
    {
					list<Ast*> *list_ast = new list<Ast*>();
					list_ast->push_back((yyvsp[0].ast));
					(yyval.ast_list) = list_ast;
				}
#line 2160 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 666 "parser.y" /* yacc.c:1646  */
    {
					(yyvsp[-2].ast_list)->push_back((yyvsp[0].ast));
					(yyval.ast_list) = (yyvsp[-2].ast_list);
				}
#line 2169 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 673 "parser.y" /* yacc.c:1646  */
    {
				Conditional_Expression_Ast *cond_ast = new Conditional_Expression_Ast((yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast), yylineno);
				cond_ast->check_ast();
				(yyval.ast) = cond_ast;
			}
#line 2179 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 679 "parser.y" /* yacc.c:1646  */
    {
				// printf("Expr-1\n");
				Plus_Ast *plus_ast = new Plus_Ast((yyvsp[-2].ast), (yyvsp[0].ast), yylineno);
				plus_ast->check_ast();
				(yyval.ast) = plus_ast;
			}
#line 2190 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 686 "parser.y" /* yacc.c:1646  */
    {
				// printf("Expr-2\n");
				Minus_Ast *minus_ast = new Minus_Ast((yyvsp[-2].ast), (yyvsp[0].ast), yylineno);
				minus_ast->check_ast();
				(yyval.ast) = minus_ast;
			}
#line 2201 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 693 "parser.y" /* yacc.c:1646  */
    {
				// printf("Expr_a-1\n");
				Mult_Ast *mult_ast = new Mult_Ast((yyvsp[-2].ast), (yyvsp[0].ast), yylineno);
				mult_ast->check_ast();
				(yyval.ast) = mult_ast;
			}
#line 2212 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 700 "parser.y" /* yacc.c:1646  */
    {
				// printf("Expr_a-2\n");
				Divide_Ast *divide_ast = new Divide_Ast((yyvsp[-2].ast), (yyvsp[0].ast), yylineno);
				divide_ast->check_ast();
				(yyval.ast) = divide_ast;
			}
#line 2223 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 707 "parser.y" /* yacc.c:1646  */
    {
				// printf("Expr_b-1\n");
				UMinus_Ast *uminus_ast = new UMinus_Ast((yyvsp[0].ast), NULL, yylineno);
				uminus_ast->check_ast();
				(yyval.ast) = uminus_ast;
			}
#line 2234 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 714 "parser.y" /* yacc.c:1646  */
    {
				// printf("Expr_d-1\n");
				(yyval.ast) = (yyvsp[-1].ast);
			}
#line 2243 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 719 "parser.y" /* yacc.c:1646  */
    {
				// printf("Expr_d-2\n");
				(yyval.ast) = (yyvsp[0].ast);
			}
#line 2252 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 724 "parser.y" /* yacc.c:1646  */
    {
				// printf("Expr_d-3\n");
				(yyval.ast) = (yyvsp[0].ast);
			}
#line 2261 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 731 "parser.y" /* yacc.c:1646  */
    {
				// printf("Var\n");
				// string var = *$1;
				string var = *(yyvsp[0].string_value) + "_";
				Symbol_Table_Entry *var_sym_entry;
				int err =0;
				// cout<<"here11111"<<endl;
				if(local_symbol_table->variable_in_symbol_list_check(var)){
					// cout<<"here22222"<<endl;
					var_sym_entry = &(local_symbol_table->get_symbol_table_entry(var));
				}
				else if(formal_param_table->variable_in_symbol_list_check(var)){
					// cout<<"here33333"<<endl;
					var_sym_entry = &(formal_param_table->get_symbol_table_entry(var));
				}
				else if(global_symbol_table->variable_in_symbol_list_check(var)){
					// cout<<"here44444"<<endl;
					var_sym_entry = &(global_symbol_table->get_symbol_table_entry(var));
				}
				else{
					// cout<<"here55555"<<endl;
					err = 1;
				}
				if(err){
					char err[100];
					sprintf(err, "cs316: Error: Line: %d: Variable has not been declared", yylineno);
					yyerror(err);
					exit(-1);
				}
				else{
					Name_Ast *name_ast = new Name_Ast(var, *var_sym_entry, yylineno);
					(yyval.ast) = name_ast;
				}
				// printf("exit Var\n");
			}
#line 2301 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 769 "parser.y" /* yacc.c:1646  */
    {
				// printf("Const-1\n");
				Number_Ast<int> *int_ast = new Number_Ast<int>((yyvsp[0].integer_value), int_data_type, yylineno);
				(yyval.ast) = int_ast;
			}
#line 2311 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 775 "parser.y" /* yacc.c:1646  */
    {
				// printf("Const-2\n");
				Number_Ast<double> *float_ast = new Number_Ast<double>((yyvsp[0].double_value), double_data_type, yylineno);
				(yyval.ast) = float_ast;
			}
#line 2321 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2325 "parser.tab.c" /* yacc.c:1646  */
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
#line 781 "parser.y" /* yacc.c:1906  */

