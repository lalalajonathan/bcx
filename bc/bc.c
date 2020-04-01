/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ENDOFLINE = 258,
     AND = 259,
     OR = 260,
     NOT = 261,
     STRING = 262,
     NAME = 263,
     NUMBER = 264,
     ASSIGN_OP = 265,
     REL_OP = 266,
     INCR_DECR = 267,
     Define = 268,
     Break = 269,
     Quit = 270,
     Length = 271,
     Powmod = 272,
     Factorial = 273,
     Permutation = 274,
     Combination = 275,
     Return = 276,
     For = 277,
     If = 278,
     While = 279,
     Sqrt = 280,
     Else = 281,
     Scale = 282,
     Ibase = 283,
     Obase = 284,
     Auto = 285,
     Read = 286,
     Random = 287,
     Warranty = 288,
     Halt = 289,
     Last = 290,
     Continue = 291,
     Print = 292,
     Limits = 293,
     UNARY_MINUS = 294,
     HistoryVar = 295,
     Void = 296
   };
#endif
/* Tokens.  */
#define ENDOFLINE 258
#define AND 259
#define OR 260
#define NOT 261
#define STRING 262
#define NAME 263
#define NUMBER 264
#define ASSIGN_OP 265
#define REL_OP 266
#define INCR_DECR 267
#define Define 268
#define Break 269
#define Quit 270
#define Length 271
#define Powmod 272
#define Factorial 273
#define Permutation 274
#define Combination 275
#define Return 276
#define For 277
#define If 278
#define While 279
#define Sqrt 280
#define Else 281
#define Scale 282
#define Ibase 283
#define Obase 284
#define Auto 285
#define Read 286
#define Random 287
#define Warranty 288
#define Halt 289
#define Last 290
#define Continue 291
#define Print 292
#define Limits 293
#define UNARY_MINUS 294
#define HistoryVar 295
#define Void 296




/* Copy the first part of user declarations.  */
#line 31 "bc.y"


#include "bcdefs.h"
#include "global.h"
#include "proto.h"

/* current function number. */
int cur_func = -1;

/* Expression encoded information -- See comment at expression rules. */
#define EX_ASSGN 0 
#define EX_REG   1
#define EX_COMP  2
#define EX_PAREN 4
#define EX_VOID  8 
#define EX_EMPTY 16



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 52 "bc.y"
{
	char	 *s_value;
	char	  c_value;
	int	  i_value;
	arg_list *a_value;
       }
/* Line 193 of yacc.c.  */
#line 204 "bc.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 217 "bc.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   924

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNRULES -- Number of states.  */
#define YYNSTATES  222

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    46,    56,     2,
      49,    50,    44,    42,    53,    43,     2,    45,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    48,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    55,    47,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    12,    15,    16,    18,
      19,    21,    25,    28,    29,    31,    34,    38,    41,    45,
      47,    50,    52,    54,    56,    58,    60,    62,    64,    66,
      69,    70,    71,    72,    73,    88,    89,    98,    99,   100,
     109,   113,   114,   118,   120,   124,   126,   128,   129,   130,
     135,   136,   150,   151,   153,   154,   156,   157,   161,   165,
     167,   171,   176,   181,   185,   191,   198,   205,   206,   208,
     210,   214,   218,   224,   225,   227,   228,   230,   231,   236,
     237,   242,   243,   248,   251,   255,   259,   263,   267,   271,
     275,   279,   282,   284,   286,   290,   295,   298,   301,   306,
     315,   320,   327,   334,   339,   344,   348,   352,   354,   359,
     361,   363,   365,   367,   369,   370,   372
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      58,     0,    -1,    -1,    58,    59,    -1,    61,     3,    -1,
      77,    -1,     1,     3,    -1,    -1,     3,    -1,    -1,    63,
      -1,    61,    48,    63,    -1,    61,    48,    -1,    -1,    63,
      -1,    62,     3,    -1,    62,     3,    63,    -1,    62,    48,
      -1,    62,    48,    64,    -1,    64,    -1,     1,    64,    -1,
      33,    -1,    38,    -1,    87,    -1,     7,    -1,    14,    -1,
      36,    -1,    15,    -1,    34,    -1,    21,    86,    -1,    -1,
      -1,    -1,    -1,    22,    65,    49,    85,    48,    66,    85,
      48,    67,    85,    50,    68,    60,    64,    -1,    -1,    23,
      49,    87,    50,    69,    60,    64,    75,    -1,    -1,    -1,
      24,    70,    49,    87,    71,    50,    60,    64,    -1,    51,
      62,    52,    -1,    -1,    37,    72,    73,    -1,    74,    -1,
      74,    53,    73,    -1,     7,    -1,    87,    -1,    -1,    -1,
      26,    76,    60,    64,    -1,    -1,    13,    79,     8,    49,
      80,    50,    60,    51,    92,    81,    78,    62,    52,    -1,
      -1,    41,    -1,    -1,    82,    -1,    -1,    30,    82,     3,
      -1,    30,    82,    48,    -1,     8,    -1,     8,    54,    55,
      -1,    44,     8,    54,    55,    -1,    56,     8,    54,    55,
      -1,    82,    53,     8,    -1,    82,    53,     8,    54,    55,
      -1,    82,    53,    44,     8,    54,    55,    -1,    82,    53,
      56,     8,    54,    55,    -1,    -1,    84,    -1,    87,    -1,
       8,    54,    55,    -1,    84,    53,    87,    -1,    84,    53,
       8,    54,    55,    -1,    -1,    87,    -1,    -1,    87,    -1,
      -1,    91,    10,    88,    87,    -1,    -1,    87,     4,    89,
      87,    -1,    -1,    87,     5,    90,    87,    -1,     6,    87,
      -1,    87,    11,    87,    -1,    87,    42,    87,    -1,    87,
      43,    87,    -1,    87,    44,    87,    -1,    87,    45,    87,
      -1,    87,    46,    87,    -1,    87,    47,    87,    -1,    43,
      87,    -1,    91,    -1,     9,    -1,    49,    87,    50,    -1,
       8,    49,    83,    50,    -1,    12,    91,    -1,    91,    12,
      -1,    16,    49,    87,    50,    -1,    17,    49,    87,    53,
      87,    53,    87,    50,    -1,    18,    49,    87,    50,    -1,
      19,    49,    87,    53,    87,    50,    -1,    20,    49,    87,
      53,    87,    50,    -1,    25,    49,    87,    50,    -1,    27,
      49,    87,    50,    -1,    31,    49,    50,    -1,    32,    49,
      50,    -1,     8,    -1,     8,    54,    87,    55,    -1,    28,
      -1,    29,    -1,    27,    -1,    40,    -1,    35,    -1,    -1,
       3,    -1,    92,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   123,   123,   131,   133,   135,   137,   143,   144,   148,
     149,   150,   151,   154,   155,   156,   157,   158,   159,   161,
     162,   165,   167,   169,   178,   185,   196,   208,   210,   212,
     215,   220,   232,   247,   214,   267,   266,   282,   290,   281,
     306,   309,   308,   312,   313,   315,   321,   328,   330,   329,
     342,   340,   367,   368,   375,   376,   379,   380,   382,   385,
     387,   389,   393,   397,   399,   401,   405,   411,   412,   414,
     422,   429,   437,   456,   460,   463,   469,   484,   483,   513,
     512,   528,   527,   545,   553,   584,   591,   598,   605,   612,
     619,   626,   633,   642,   658,   664,   684,   703,   726,   734,
     741,   748,   755,   763,   770,   777,   783,   790,   792,   800,
     802,   804,   806,   810,   817,   818,   819
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ENDOFLINE", "AND", "OR", "NOT",
  "STRING", "NAME", "NUMBER", "ASSIGN_OP", "REL_OP", "INCR_DECR", "Define",
  "Break", "Quit", "Length", "Powmod", "Factorial", "Permutation",
  "Combination", "Return", "For", "If", "While", "Sqrt", "Else", "Scale",
  "Ibase", "Obase", "Auto", "Read", "Random", "Warranty", "Halt", "Last",
  "Continue", "Print", "Limits", "UNARY_MINUS", "HistoryVar", "Void",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "';'", "'('", "')'", "'{'",
  "'}'", "','", "'['", "']'", "'&'", "$accept", "program", "input_item",
  "opt_newline", "semicolon_list", "statement_list", "statement_or_error",
  "statement", "@1", "@2", "@3", "@4", "@5", "@6", "@7", "@8",
  "print_list", "print_element", "opt_else", "@9", "function", "@10",
  "opt_void", "opt_parameter_list", "opt_auto_define_list", "define_list",
  "opt_argument_list", "argument_list", "opt_expression",
  "return_expression", "expression", "@11", "@12", "@13",
  "named_expression", "required_eol", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,    43,    45,    42,    47,    37,    94,    59,    40,
      41,   123,   125,    44,    91,    93,    38
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    58,    59,    59,    59,    60,    60,    61,
      61,    61,    61,    62,    62,    62,    62,    62,    62,    63,
      63,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      65,    66,    67,    68,    64,    69,    64,    70,    71,    64,
      64,    72,    64,    73,    73,    74,    74,    75,    76,    75,
      78,    77,    79,    79,    80,    80,    81,    81,    81,    82,
      82,    82,    82,    82,    82,    82,    82,    83,    83,    84,
      84,    84,    84,    85,    85,    86,    86,    88,    87,    89,
      87,    90,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    91,    91,    91,
      91,    91,    91,    91,    92,    92,    92
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     2,     0,     1,     0,
       1,     3,     2,     0,     1,     2,     3,     2,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       0,     0,     0,     0,    14,     0,     8,     0,     0,     8,
       3,     0,     3,     1,     3,     1,     1,     0,     0,     4,
       0,    13,     0,     1,     0,     1,     0,     3,     3,     1,
       3,     4,     4,     3,     5,     6,     6,     0,     1,     1,
       3,     3,     5,     0,     1,     0,     1,     0,     4,     0,
       4,     0,     4,     2,     3,     3,     3,     3,     3,     3,
       3,     2,     1,     1,     3,     4,     2,     2,     4,     8,
       4,     6,     6,     4,     4,     3,     3,     1,     4,     1,
       1,     1,     1,     1,     0,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    24,   107,    93,     0,    52,
      25,    27,     0,     0,     0,     0,     0,    75,    30,     0,
      37,     0,   111,   109,   110,     0,     0,    21,    28,   113,
      26,    41,    22,   112,     0,     0,     0,     3,     0,    10,
      19,     5,    23,    92,     6,    20,    83,    67,     0,   107,
     111,    96,    53,     0,     0,     0,     0,     0,     0,    29,
      76,     0,     0,     0,     0,     0,     0,     0,     0,    91,
       0,     0,     0,    14,     4,     0,    79,    81,     0,     0,
       0,     0,     0,     0,     0,    77,    97,   107,     0,    68,
      69,     0,     0,     0,     0,     0,     0,     0,    73,     0,
       0,     0,     0,   105,   106,    45,    42,    43,    46,    94,
       0,    17,    40,    11,     0,     0,    84,    85,    86,    87,
      88,    89,    90,     0,     0,    95,     0,   108,    54,    98,
       0,   100,     0,     0,     0,    74,    35,    38,   103,   104,
       0,    16,    18,    80,    82,    78,    70,   107,    71,    59,
       0,     0,     0,    55,     0,     0,     0,    31,     7,     0,
      44,     0,     0,     0,     0,     7,     0,     0,   101,   102,
      73,     8,     0,     7,    72,    60,     0,     0,     0,    63,
       0,     0,     0,     0,    47,     0,    61,    62,   114,     0,
       0,     0,    99,    32,    48,    36,    39,   115,    56,    64,
       0,     0,    73,     7,   116,     0,    50,    65,    66,     0,
       0,     0,     0,    33,    49,    57,    58,     0,     7,    51,
       0,    34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    37,   172,    38,    72,    73,    40,    61,   170,
     202,   218,   158,    63,   159,    68,   106,   107,   195,   203,
      41,   212,    53,   152,   206,   153,    88,    89,   134,    59,
      42,   123,   114,   115,    43,   198
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -165
static const yytype_int16 yypact[] =
{
    -165,   212,  -165,   486,   786,  -165,   -41,  -165,     1,   -31,
    -165,  -165,   -35,   -22,   -12,    -6,    -1,   786,  -165,    12,
    -165,    38,    50,  -165,  -165,    51,    52,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,   786,   786,   250,  -165,     2,  -165,
    -165,  -165,   868,    85,  -165,  -165,    47,   822,   786,   -10,
    -165,  -165,  -165,    15,   786,   786,   786,   786,   786,  -165,
     868,    62,   786,    65,   786,   786,    59,    66,   750,  -165,
     523,   712,    21,  -165,  -165,   354,  -165,  -165,   786,   786,
     786,   786,   786,   786,   786,  -165,  -165,   -23,    67,    -4,
     868,    60,    69,   534,   150,   543,   411,   425,   786,   552,
     786,   596,   605,  -165,  -165,  -165,  -165,    35,   868,  -165,
     302,   712,  -165,  -165,   786,   786,   -26,    39,    39,    72,
      72,    72,    72,   786,   117,  -165,   858,  -165,    -5,  -165,
     786,  -165,   786,   786,    79,   868,  -165,   868,  -165,  -165,
     750,  -165,  -165,    47,   877,   -26,  -165,   -14,   868,    78,
     112,   131,    90,    88,   438,   614,   623,  -165,   140,    97,
    -165,   392,    95,    99,   102,   140,     3,   786,  -165,  -165,
     786,  -165,   712,   140,  -165,  -165,    96,   103,   111,   109,
     156,   159,   667,   122,   145,   712,  -165,  -165,   170,   119,
     121,   123,  -165,  -165,  -165,  -165,  -165,  -165,     4,  -165,
     124,   125,   786,   140,  -165,    -5,  -165,  -165,  -165,   126,
     712,    19,   250,  -165,  -165,  -165,  -165,    22,   140,  -165,
     712,  -165
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -165,  -165,  -165,  -161,  -165,   -34,     0,    -3,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,    41,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,   -21,  -165,  -165,  -164,  -165,
      -2,  -165,  -165,  -165,   175,  -165
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -16
static const yytype_int16 yytable[] =
{
      45,    39,    46,   149,   178,    74,   183,   204,    47,    49,
      52,   179,   185,    48,    54,    60,    79,    80,    81,    82,
      83,    84,   215,    92,   110,   110,    47,    55,    50,    23,
      24,   124,    69,    70,   205,    47,    29,    56,   209,   150,
     161,    33,   210,    57,    48,    90,    91,   180,    58,   126,
      75,   151,    93,    94,    95,    96,    97,   220,    78,   181,
      99,    62,   101,   102,    76,    77,   108,   216,    45,   111,
     111,    78,   166,   112,   219,   113,   116,   117,   118,   119,
     120,   121,   122,    81,    82,    83,    84,    64,   140,    79,
      80,    81,    82,    83,    84,    85,   135,    86,   137,    65,
      66,    67,    79,    80,    81,    82,    83,    84,   142,   103,
     141,    98,   143,   144,   100,   127,   104,   125,   128,    84,
     163,   145,    91,     4,   148,     6,     7,   157,   154,     8,
     155,   156,   162,    12,    13,    14,    15,    16,   108,   164,
     165,   166,    21,   171,    22,    23,    24,   173,    25,    26,
     175,   186,    29,   176,    76,    77,   177,    33,   187,    91,
      34,    78,   188,   189,   190,   182,    35,   191,   135,   184,
     193,   194,   146,   197,   199,   200,   213,   201,   217,   207,
     208,   160,   196,    51,   211,     0,     0,     0,     0,     0,
       0,     0,    79,    80,    81,    82,    83,    84,     0,     0,
     135,     0,     0,   130,     0,     0,     0,   214,     0,     0,
       0,     0,     2,     3,     0,    -9,     0,   221,     4,     5,
       6,     7,     0,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,    22,
      23,    24,     0,    25,    26,    27,    28,    29,    30,    31,
      32,    71,    33,   -13,     0,    34,     4,     5,     6,     7,
      -9,    35,     8,    36,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     0,    22,    23,    24,
       0,    25,    26,    27,    28,    29,    30,    31,    32,     0,
      33,     0,     0,    34,     0,     0,     0,     0,   -13,    35,
       0,    36,   -13,    71,     0,   -15,     0,     0,     4,     5,
       6,     7,     0,     0,     8,     0,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,    22,
      23,    24,     0,    25,    26,    27,    28,    29,    30,    31,
      32,     0,    33,     0,     0,    34,     0,     0,     0,     0,
     -15,    35,     0,    36,   -15,    71,     0,   -12,     0,     0,
       4,     5,     6,     7,     0,     0,     8,     0,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,    22,    23,    24,     0,    25,    26,    27,    28,    29,
      30,    31,    32,     0,    33,     0,     0,    34,     4,     0,
       6,     7,   -12,    35,     8,    36,     0,     0,    12,    13,
      14,    15,    16,     0,     0,    76,    77,    21,     0,    22,
      23,    24,    78,    25,    26,     0,     0,    29,     0,    76,
      77,     0,    33,     0,     0,    34,    78,     0,     0,     0,
       0,    35,    76,    77,     0,     0,     0,   174,     0,    78,
       0,     0,     0,    79,    80,    81,    82,    83,    84,     0,
       0,     0,     0,     0,   132,     0,     0,    79,    80,    81,
      82,    83,    84,     0,     0,     0,     0,     0,   133,     0,
      79,    80,    81,    82,    83,    84,     0,     0,     0,    44,
       0,   167,     4,     5,     6,     7,     0,     0,     8,     0,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     0,    22,    23,    24,     0,    25,    26,    27,
      28,    29,    30,    31,    32,     0,    33,    76,    77,    34,
       0,     0,     0,     0,    78,    35,     0,    36,    76,    77,
       0,     0,     0,     0,     0,    78,     0,    76,    77,     0,
       0,     0,     0,     0,    78,     0,    76,    77,     0,     0,
       0,     0,     0,    78,     0,    79,    80,    81,    82,    83,
      84,     0,     0,   109,     0,     0,    79,    80,    81,    82,
      83,    84,     0,     0,   129,    79,    80,    81,    82,    83,
      84,     0,     0,   131,    79,    80,    81,    82,    83,    84,
      76,    77,   136,     0,     0,     0,     0,    78,     0,    76,
      77,     0,     0,     0,     0,     0,    78,     0,    76,    77,
       0,     0,     0,     0,     0,    78,     0,    76,    77,     0,
       0,     0,     0,     0,    78,     0,     0,     0,    79,    80,
      81,    82,    83,    84,     0,     0,   138,    79,    80,    81,
      82,    83,    84,     0,     0,   139,    79,    80,    81,    82,
      83,    84,     0,     0,   168,    79,    80,    81,    82,    83,
      84,    76,    77,   169,     0,     0,     0,     0,    78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    79,
      80,    81,    82,    83,    84,     0,     0,   192,     4,     5,
       6,     7,     0,     0,     8,     0,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,    22,
      23,    24,     0,    25,    26,    27,    28,    29,    30,    31,
      32,     0,    33,     0,     0,    34,     4,   105,     6,     7,
       0,    35,     8,    36,     0,     0,    12,    13,    14,    15,
      16,     0,     0,     0,     0,    21,     0,    22,    23,    24,
       0,    25,    26,     0,     0,    29,     0,     0,     0,     0,
      33,     0,     4,    34,     6,     7,     0,     0,     8,    35,
       0,     0,    12,    13,    14,    15,    16,     0,     0,     0,
       0,    21,     0,    22,    23,    24,     0,    25,    26,     0,
       0,    29,     0,     0,     0,     0,    33,     0,     4,    34,
      87,     7,     0,     0,     8,    35,     0,     0,    12,    13,
      14,    15,    16,     0,     0,     0,     0,    21,     0,    22,
      23,    24,     0,    25,    26,     0,     0,    29,     0,     0,
       0,     0,    33,     0,     4,    34,   147,     7,     0,     0,
       8,    35,    76,    77,    12,    13,    14,    15,    16,    78,
       0,    76,     0,    21,     0,    22,    23,    24,    78,    25,
      26,     0,     0,    29,     0,     0,     0,     0,    33,     0,
       0,    34,     0,     0,     0,     0,     0,    35,     0,     0,
      79,    80,    81,    82,    83,    84,     0,     0,     0,    79,
      80,    81,    82,    83,    84
};

static const yytype_int16 yycheck[] =
{
       3,     1,     4,     8,   165,     3,   170,     3,    49,     8,
      41,     8,   173,    54,    49,    17,    42,    43,    44,    45,
      46,    47,     3,     8,     3,     3,    49,    49,    27,    28,
      29,    54,    34,    35,    30,    49,    35,    49,   202,    44,
      54,    40,   203,    49,    54,    47,    48,    44,    49,    53,
      48,    56,    54,    55,    56,    57,    58,   218,    11,    56,
      62,    49,    64,    65,     4,     5,    68,    48,    71,    48,
      48,    11,    53,    52,    52,    75,    78,    79,    80,    81,
      82,    83,    84,    44,    45,    46,    47,    49,    53,    42,
      43,    44,    45,    46,    47,    10,    98,    12,   100,    49,
      49,    49,    42,    43,    44,    45,    46,    47,   111,    50,
     110,    49,   114,   115,    49,    55,    50,    50,    49,    47,
       8,   123,   124,     6,   126,     8,     9,    48,   130,    12,
     132,   133,    54,    16,    17,    18,    19,    20,   140,     8,
      50,    53,    25,     3,    27,    28,    29,    50,    31,    32,
      55,    55,    35,    54,     4,     5,    54,    40,    55,   161,
      43,    11,    51,    54,     8,   167,    49,     8,   170,   172,
      48,    26,    55,     3,    55,    54,    50,    54,   212,    55,
      55,   140,   185,     8,   205,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    43,    44,    45,    46,    47,    -1,    -1,
     202,    -1,    -1,    53,    -1,    -1,    -1,   210,    -1,    -1,
      -1,    -1,     0,     1,    -1,     3,    -1,   220,     6,     7,
       8,     9,    -1,    -1,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    -1,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,     1,    40,     3,    -1,    43,     6,     7,     8,     9,
      48,    49,    12,    51,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    -1,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      40,    -1,    -1,    43,    -1,    -1,    -1,    -1,    48,    49,
      -1,    51,    52,     1,    -1,     3,    -1,    -1,     6,     7,
       8,     9,    -1,    -1,    12,    -1,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    -1,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      48,    49,    -1,    51,    52,     1,    -1,     3,    -1,    -1,
       6,     7,     8,     9,    -1,    -1,    12,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      -1,    27,    28,    29,    -1,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    40,    -1,    -1,    43,     6,    -1,
       8,     9,    48,    49,    12,    51,    -1,    -1,    16,    17,
      18,    19,    20,    -1,    -1,     4,     5,    25,    -1,    27,
      28,    29,    11,    31,    32,    -1,    -1,    35,    -1,     4,
       5,    -1,    40,    -1,    -1,    43,    11,    -1,    -1,    -1,
      -1,    49,     4,     5,    -1,    -1,    -1,    55,    -1,    11,
      -1,    -1,    -1,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,     3,
      -1,    53,     6,     7,     8,     9,    -1,    -1,    12,    -1,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    -1,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    40,     4,     5,    43,
      -1,    -1,    -1,    -1,    11,    49,    -1,    51,     4,     5,
      -1,    -1,    -1,    -1,    -1,    11,    -1,     4,     5,    -1,
      -1,    -1,    -1,    -1,    11,    -1,     4,     5,    -1,    -1,
      -1,    -1,    -1,    11,    -1,    42,    43,    44,    45,    46,
      47,    -1,    -1,    50,    -1,    -1,    42,    43,    44,    45,
      46,    47,    -1,    -1,    50,    42,    43,    44,    45,    46,
      47,    -1,    -1,    50,    42,    43,    44,    45,    46,    47,
       4,     5,    50,    -1,    -1,    -1,    -1,    11,    -1,     4,
       5,    -1,    -1,    -1,    -1,    -1,    11,    -1,     4,     5,
      -1,    -1,    -1,    -1,    -1,    11,    -1,     4,     5,    -1,
      -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,    42,    43,
      44,    45,    46,    47,    -1,    -1,    50,    42,    43,    44,
      45,    46,    47,    -1,    -1,    50,    42,    43,    44,    45,
      46,    47,    -1,    -1,    50,    42,    43,    44,    45,    46,
      47,     4,     5,    50,    -1,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      43,    44,    45,    46,    47,    -1,    -1,    50,     6,     7,
       8,     9,    -1,    -1,    12,    -1,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    -1,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    40,    -1,    -1,    43,     6,     7,     8,     9,
      -1,    49,    12,    51,    -1,    -1,    16,    17,    18,    19,
      20,    -1,    -1,    -1,    -1,    25,    -1,    27,    28,    29,
      -1,    31,    32,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      40,    -1,     6,    43,     8,     9,    -1,    -1,    12,    49,
      -1,    -1,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    25,    -1,    27,    28,    29,    -1,    31,    32,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    40,    -1,     6,    43,
       8,     9,    -1,    -1,    12,    49,    -1,    -1,    16,    17,
      18,    19,    20,    -1,    -1,    -1,    -1,    25,    -1,    27,
      28,    29,    -1,    31,    32,    -1,    -1,    35,    -1,    -1,
      -1,    -1,    40,    -1,     6,    43,     8,     9,    -1,    -1,
      12,    49,     4,     5,    16,    17,    18,    19,    20,    11,
      -1,     4,    -1,    25,    -1,    27,    28,    29,    11,    31,
      32,    -1,    -1,    35,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    43,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    42,
      43,    44,    45,    46,    47
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    58,     0,     1,     6,     7,     8,     9,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    27,    28,    29,    31,    32,    33,    34,    35,
      36,    37,    38,    40,    43,    49,    51,    59,    61,    63,
      64,    77,    87,    91,     3,    64,    87,    49,    54,     8,
      27,    91,    41,    79,    49,    49,    49,    49,    49,    86,
      87,    65,    49,    70,    49,    49,    49,    49,    72,    87,
      87,     1,    62,    63,     3,    48,     4,     5,    11,    42,
      43,    44,    45,    46,    47,    10,    12,     8,    83,    84,
      87,    87,     8,    87,    87,    87,    87,    87,    49,    87,
      49,    87,    87,    50,    50,     7,    73,    74,    87,    50,
       3,    48,    52,    63,    89,    90,    87,    87,    87,    87,
      87,    87,    87,    88,    54,    50,    53,    55,    49,    50,
      53,    50,    53,    53,    85,    87,    50,    87,    50,    50,
      53,    63,    64,    87,    87,    87,    55,     8,    87,     8,
      44,    56,    80,    82,    87,    87,    87,    48,    69,    71,
      73,    54,    54,     8,     8,    50,    53,    53,    50,    50,
      66,     3,    60,    50,    55,    55,    54,    54,    60,     8,
      44,    56,    87,    85,    64,    60,    55,    55,    51,    54,
       8,     8,    50,    48,    26,    75,    64,     3,    92,    55,
      54,    54,    67,    76,     3,    30,    81,    55,    55,    85,
      60,    82,    78,    50,    64,     3,    48,    62,    68,    52,
      60,    64
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

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
#line 123 "bc.y"
    {
			      (yyval.i_value) = 0;
			      if (interactive && !quiet)
				{
				  show_bc_version ();
				  welcome ();
				}
			    }
    break;

  case 4:
#line 134 "bc.y"
    { run_code (); }
    break;

  case 5:
#line 136 "bc.y"
    { run_code (); }
    break;

  case 6:
#line 138 "bc.y"
    {
			      yyerrok;
			      init_gen ();
			    }
    break;

  case 8:
#line 145 "bc.y"
    { ct_warn ("newline not allowed"); }
    break;

  case 9:
#line 148 "bc.y"
    { (yyval.i_value) = 0; }
    break;

  case 13:
#line 154 "bc.y"
    { (yyval.i_value) = 0; }
    break;

  case 20:
#line 163 "bc.y"
    { (yyval.i_value) = (yyvsp[(2) - (2)].i_value); }
    break;

  case 21:
#line 166 "bc.y"
    { warranty (""); }
    break;

  case 22:
#line 168 "bc.y"
    { limits (); }
    break;

  case 23:
#line 170 "bc.y"
    {
			      if ((yyvsp[(1) - (1)].i_value) & EX_COMP)
				ct_warn ("comparison in expression");
			      if ((yyvsp[(1) - (1)].i_value) & EX_REG)
				generate ("W");
			      else 
				generate ("p");
			    }
    break;

  case 24:
#line 179 "bc.y"
    {
			      (yyval.i_value) = 0;
			      generate ("w");
			      generate ((yyvsp[(1) - (1)].s_value));
			      free ((yyvsp[(1) - (1)].s_value));
			    }
    break;

  case 25:
#line 186 "bc.y"
    {
			      if (break_label == 0)
				yyerror ("Break outside a for/while");
			      else
				{
				  snprintf (genstr, genlen, "J%1d:",
				  	    break_label);
				  generate (genstr);
				}
			    }
    break;

  case 26:
#line 197 "bc.y"
    {
			      ct_warn ("Continue statement");
			      if (continue_label == 0)
				yyerror ("Continue outside a for");
			      else
				{
				  snprintf (genstr, genlen, "J%1d:", 
					    continue_label);
				  generate (genstr);
				}
			    }
    break;

  case 27:
#line 209 "bc.y"
    { bc_exit (0); }
    break;

  case 28:
#line 211 "bc.y"
    { generate ("h"); }
    break;

  case 29:
#line 213 "bc.y"
    { generate ("R"); }
    break;

  case 30:
#line 215 "bc.y"
    {
			      (yyvsp[(1) - (1)].i_value) = break_label; 
			      break_label = next_label++;
			    }
    break;

  case 31:
#line 220 "bc.y"
    {
			      if ((yyvsp[(4) - (5)].i_value) & EX_COMP)
				ct_warn ("Comparison in first for expression");
			      if ((yyvsp[(4) - (5)].i_value) & EX_VOID)
				yyerror ("first expression is void");
			      if (!((yyvsp[(4) - (5)].i_value) & EX_EMPTY))
				generate ("p");
			      (yyvsp[(4) - (5)].i_value) = next_label++;
			      snprintf (genstr, genlen, "N%1d:", (yyvsp[(4) - (5)].i_value));
			      generate (genstr);
			    }
    break;

  case 32:
#line 232 "bc.y"
    {
			      if ((yyvsp[(7) - (8)].i_value) & EX_VOID)
				yyerror ("second expression is void");
			      if ((yyvsp[(7) - (8)].i_value) & EX_EMPTY ) generate ("1");
			      (yyvsp[(7) - (8)].i_value) = next_label++;
			      snprintf (genstr, genlen, "B%1d:J%1d:", (yyvsp[(7) - (8)].i_value),
			      		break_label);
			      generate (genstr);
			      (yyval.i_value) = continue_label;
			      continue_label = next_label++;
			      snprintf (genstr, genlen, "N%1d:", 
			      		continue_label);
			      generate (genstr);
			    }
    break;

  case 33:
#line 247 "bc.y"
    {
			      if ((yyvsp[(10) - (11)].i_value) & EX_COMP)
				ct_warn ("Comparison in third for expression");
			      if ((yyvsp[(10) - (11)].i_value) & EX_VOID)
				yyerror ("third expression is void");
			      if ((yyvsp[(10) - (11)].i_value) & EX_EMPTY)
				snprintf (genstr, genlen, "J%1d:N%1d:", (yyvsp[(4) - (11)].i_value), (yyvsp[(7) - (11)].i_value));
			      else
				snprintf (genstr, genlen, "pJ%1d:N%1d:", (yyvsp[(4) - (11)].i_value), (yyvsp[(7) - (11)].i_value));
			      generate (genstr);
			    }
    break;

  case 34:
#line 259 "bc.y"
    {
			      snprintf (genstr, genlen, "J%1d:N%1d:",
				       continue_label, break_label);
			      generate (genstr);
			      break_label = (yyvsp[(1) - (14)].i_value);
			      continue_label = (yyvsp[(9) - (14)].i_value);
			    }
    break;

  case 35:
#line 267 "bc.y"
    {
			      if ((yyvsp[(3) - (4)].i_value) & EX_VOID)
				yyerror ("void expression");
			      (yyvsp[(3) - (4)].i_value) = if_label;
			      if_label = next_label++;
			      snprintf (genstr, genlen, "Z%1d:", if_label);
			      generate (genstr);
			    }
    break;

  case 36:
#line 276 "bc.y"
    {
			      snprintf (genstr, genlen, "N%1d:", if_label); 
			      generate (genstr);
			      if_label = (yyvsp[(3) - (8)].i_value);
			    }
    break;

  case 37:
#line 282 "bc.y"
    {
			      (yyvsp[(1) - (1)].i_value) = continue_label;
			      continue_label = next_label++;
			      snprintf (genstr, genlen, "N%1d:", 
					continue_label);
			      generate (genstr);
			    }
    break;

  case 38:
#line 290 "bc.y"
    {
			      if ((yyvsp[(4) - (4)].i_value) & EX_VOID)
				yyerror ("void expression");
			      (yyvsp[(4) - (4)].i_value) = break_label; 
			      break_label = next_label++;
			      snprintf (genstr, genlen, "Z%1d:", break_label);
			      generate (genstr);
			    }
    break;

  case 39:
#line 299 "bc.y"
    {
			      snprintf (genstr, genlen, "J%1d:N%1d:", 
					continue_label, break_label);
			      generate (genstr);
			      break_label = (yyvsp[(4) - (8)].i_value);
			      continue_label = (yyvsp[(1) - (8)].i_value);
			    }
    break;

  case 40:
#line 307 "bc.y"
    { (yyval.i_value) = 0; }
    break;

  case 41:
#line 309 "bc.y"
    {  ct_warn ("print statement"); }
    break;

  case 45:
#line 316 "bc.y"
    {
			      generate ("O");
			      generate ((yyvsp[(1) - (1)].s_value));
			      free ((yyvsp[(1) - (1)].s_value));
			    }
    break;

  case 46:
#line 322 "bc.y"
    {
			      if ((yyvsp[(1) - (1)].i_value) & EX_VOID)
				yyerror ("void expression in print");
			      generate ("P");
			    }
    break;

  case 48:
#line 330 "bc.y"
    {
			      ct_warn ("else clause in if statement");
			      (yyvsp[(1) - (1)].i_value) = next_label++;
			      snprintf (genstr, genlen, "J%d:N%1d:", (yyvsp[(1) - (1)].i_value),
					if_label); 
			      generate (genstr);
			      if_label = (yyvsp[(1) - (1)].i_value);
			    }
    break;

  case 50:
#line 342 "bc.y"
    { char *params, *autos;
			      /* Check auto list against parameter list? */
			      check_params ((yyvsp[(5) - (10)].a_value),(yyvsp[(10) - (10)].a_value));
			      params = arg_str ((yyvsp[(5) - (10)].a_value));
			      autos  = arg_str ((yyvsp[(10) - (10)].a_value));
			      set_genstr_size (30 + strlen (params)
					       + strlen (autos));
			      cur_func = lookup((yyvsp[(3) - (10)].s_value),FUNCTDEF);
			      snprintf (genstr, genlen, "F%d,%s.%s[", cur_func,
					params, autos); 
			      generate (genstr);
			      functions[cur_func].f_void = (yyvsp[(2) - (10)].i_value);
			      free_args ((yyvsp[(5) - (10)].a_value));
			      free_args ((yyvsp[(10) - (10)].a_value));
			      (yyvsp[(1) - (10)].i_value) = next_label;
			      next_label = 1;
			    }
    break;

  case 51:
#line 360 "bc.y"
    {
			      generate ("0R]");
			      next_label = (yyvsp[(1) - (13)].i_value);
			      cur_func = -1;
			    }
    break;

  case 52:
#line 367 "bc.y"
    { (yyval.i_value) = 0; }
    break;

  case 53:
#line 369 "bc.y"
    {
			      (yyval.i_value) = 1;
			      ct_warn ("void functions");
			    }
    break;

  case 54:
#line 375 "bc.y"
    { (yyval.a_value) = NULL; }
    break;

  case 56:
#line 379 "bc.y"
    { (yyval.a_value) = NULL; }
    break;

  case 57:
#line 381 "bc.y"
    { (yyval.a_value) = (yyvsp[(2) - (3)].a_value); }
    break;

  case 58:
#line 383 "bc.y"
    { (yyval.a_value) = (yyvsp[(2) - (3)].a_value); }
    break;

  case 59:
#line 386 "bc.y"
    { (yyval.a_value) = nextarg (NULL, lookup ((yyvsp[(1) - (1)].s_value),SIMPLE), FALSE);}
    break;

  case 60:
#line 388 "bc.y"
    { (yyval.a_value) = nextarg (NULL, lookup ((yyvsp[(1) - (3)].s_value),ARRAY), FALSE); }
    break;

  case 61:
#line 390 "bc.y"
    { (yyval.a_value) = nextarg (NULL, lookup ((yyvsp[(2) - (4)].s_value),ARRAY), TRUE);
			      ct_warn ("Call by variable arrays");
			    }
    break;

  case 62:
#line 394 "bc.y"
    { (yyval.a_value) = nextarg (NULL, lookup ((yyvsp[(2) - (4)].s_value),ARRAY), TRUE);
			      ct_warn ("Call by variable arrays");
			    }
    break;

  case 63:
#line 398 "bc.y"
    { (yyval.a_value) = nextarg ((yyvsp[(1) - (3)].a_value), lookup ((yyvsp[(3) - (3)].s_value),SIMPLE), FALSE); }
    break;

  case 64:
#line 400 "bc.y"
    { (yyval.a_value) = nextarg ((yyvsp[(1) - (5)].a_value), lookup ((yyvsp[(3) - (5)].s_value),ARRAY), FALSE); }
    break;

  case 65:
#line 402 "bc.y"
    { (yyval.a_value) = nextarg ((yyvsp[(1) - (6)].a_value), lookup ((yyvsp[(4) - (6)].s_value),ARRAY), TRUE);
			      ct_warn ("Call by variable arrays");
			    }
    break;

  case 66:
#line 406 "bc.y"
    { (yyval.a_value) = nextarg ((yyvsp[(1) - (6)].a_value), lookup ((yyvsp[(4) - (6)].s_value),ARRAY), TRUE);
			      ct_warn ("Call by variable arrays");
			    }
    break;

  case 67:
#line 411 "bc.y"
    { (yyval.a_value) = NULL; }
    break;

  case 69:
#line 415 "bc.y"
    {
			      if ((yyvsp[(1) - (1)].i_value) & EX_COMP)
				ct_warn ("comparison in argument");
			      if ((yyvsp[(1) - (1)].i_value) & EX_VOID)
				yyerror ("void argument");
			      (yyval.a_value) = nextarg (NULL,0,FALSE);
			    }
    break;

  case 70:
#line 423 "bc.y"
    {
			      snprintf (genstr, genlen, "K%d:",
					-lookup ((yyvsp[(1) - (3)].s_value),ARRAY));
			      generate (genstr);
			      (yyval.a_value) = nextarg (NULL,1,FALSE);
			    }
    break;

  case 71:
#line 430 "bc.y"
    {
			      if ((yyvsp[(3) - (3)].i_value) & EX_COMP)
				ct_warn ("comparison in argument");
			      if ((yyvsp[(3) - (3)].i_value) & EX_VOID)
				yyerror ("void argument");
			      (yyval.a_value) = nextarg ((yyvsp[(1) - (3)].a_value),0,FALSE);
			    }
    break;

  case 72:
#line 438 "bc.y"
    {
			      snprintf (genstr, genlen, "K%d:", 
					-lookup ((yyvsp[(3) - (5)].s_value),ARRAY));
			      generate (genstr);
			      (yyval.a_value) = nextarg ((yyvsp[(1) - (5)].a_value),1,FALSE);
			    }
    break;

  case 73:
#line 456 "bc.y"
    {
			      (yyval.i_value) = EX_EMPTY;
			      ct_warn ("Missing expression in for statement");
			    }
    break;

  case 75:
#line 463 "bc.y"
    {
			      (yyval.i_value) = 0;
			      generate ("0");
			      if (cur_func == -1)
				yyerror("Return outside of a function.");
			    }
    break;

  case 76:
#line 470 "bc.y"
    {
			      if ((yyvsp[(1) - (1)].i_value) & EX_COMP)
				ct_warn ("comparison in return expresion");
			      if (!((yyvsp[(1) - (1)].i_value) & EX_PAREN))
				ct_warn ("return expression requires parenthesis");
			      if ((yyvsp[(1) - (1)].i_value) & EX_VOID)
				yyerror("return requires non-void expression");
			      if (cur_func == -1)
				yyerror("Return outside of a function.");
			      else if (functions[cur_func].f_void)
				yyerror("Return expression in a void function.");
			    }
    break;

  case 77:
#line 484 "bc.y"
    {
			      if ((yyvsp[(2) - (2)].c_value) != '=')
				{
				  if ((yyvsp[(1) - (2)].i_value) < 0)
				    snprintf (genstr, genlen, "DL%d:", -(yyvsp[(1) - (2)].i_value));
				  else
				    snprintf (genstr, genlen, "l%d:", (yyvsp[(1) - (2)].i_value));
				  generate (genstr);
				}
			    }
    break;

  case 78:
#line 495 "bc.y"
    {
			      if ((yyvsp[(4) - (4)].i_value) & EX_ASSGN)
				ct_warn("comparison in assignment");
			      if ((yyvsp[(4) - (4)].i_value) & EX_VOID)
				yyerror("Assignment of a void expression");
			      if ((yyvsp[(2) - (4)].c_value) != '=')
				{
				  snprintf (genstr, genlen, "%c", (yyvsp[(2) - (4)].c_value));
				  generate (genstr);
				}
			      if ((yyvsp[(1) - (4)].i_value) < 0)
				snprintf (genstr, genlen, "S%d:", -(yyvsp[(1) - (4)].i_value));
			      else
				snprintf (genstr, genlen, "s%d:", (yyvsp[(1) - (4)].i_value));
			      generate (genstr);
			      (yyval.i_value) = EX_ASSGN;
			    }
    break;

  case 79:
#line 513 "bc.y"
    {
			      ct_warn("&& operator");
			      (yyvsp[(2) - (2)].i_value) = next_label++;
			      snprintf (genstr, genlen, "DZ%d:p", (yyvsp[(2) - (2)].i_value));
			      generate (genstr);
			    }
    break;

  case 80:
#line 520 "bc.y"
    {
			      if (((yyvsp[(1) - (4)].i_value) & EX_VOID) || ((yyvsp[(4) - (4)].i_value) & EX_VOID))
				yyerror ("void expression with &&");
			      snprintf (genstr, genlen, "DZ%d:p1N%d:", (yyvsp[(2) - (4)].i_value), (yyvsp[(2) - (4)].i_value));
			      generate (genstr);
			      (yyval.i_value) = ((yyvsp[(1) - (4)].i_value) | (yyvsp[(4) - (4)].i_value)) & ~EX_PAREN;
			    }
    break;

  case 81:
#line 528 "bc.y"
    {
			      ct_warn("|| operator");
			      (yyvsp[(2) - (2)].i_value) = next_label++;
			      snprintf (genstr, genlen, "B%d:", (yyvsp[(2) - (2)].i_value));
			      generate (genstr);
			    }
    break;

  case 82:
#line 535 "bc.y"
    {
			      int tmplab;
			      if (((yyvsp[(1) - (4)].i_value) & EX_VOID) || ((yyvsp[(4) - (4)].i_value) & EX_VOID))
				yyerror ("void expression with ||");
			      tmplab = next_label++;
			      snprintf (genstr, genlen, "B%d:0J%d:N%d:1N%d:",
				       (yyvsp[(2) - (4)].i_value), tmplab, (yyvsp[(2) - (4)].i_value), tmplab);
			      generate (genstr);
			      (yyval.i_value) = ((yyvsp[(1) - (4)].i_value) | (yyvsp[(4) - (4)].i_value)) & ~EX_PAREN;
			    }
    break;

  case 83:
#line 546 "bc.y"
    {
			      if ((yyvsp[(2) - (2)].i_value) & EX_VOID)
				yyerror ("void expression with !");
			      (yyval.i_value) = (yyvsp[(2) - (2)].i_value) & ~EX_PAREN;
			      ct_warn("! operator");
			      generate ("!");
			    }
    break;

  case 84:
#line 554 "bc.y"
    {
			      if (((yyvsp[(1) - (3)].i_value) & EX_VOID) || ((yyvsp[(3) - (3)].i_value) & EX_VOID))
				yyerror ("void expression with comparison");
			      (yyval.i_value) = EX_REG | EX_COMP;
			      switch (*((yyvsp[(2) - (3)].s_value)))
				{
				case '=':
				  generate ("=");
				  break;

				case '!':
				  generate ("#");
				  break;

				case '<':
				  if ((yyvsp[(2) - (3)].s_value)[1] == '=')
				    generate ("{");
				  else
				    generate ("<");
				  break;

				case '>':
				  if ((yyvsp[(2) - (3)].s_value)[1] == '=')
				    generate ("}");
				  else
				    generate (">");
				  break;
				}
                              free((yyvsp[(2) - (3)].s_value));
			    }
    break;

  case 85:
#line 585 "bc.y"
    {
			      if (((yyvsp[(1) - (3)].i_value) & EX_VOID) || ((yyvsp[(3) - (3)].i_value) & EX_VOID))
				yyerror ("void expression with +");
			      generate ("+");
			      (yyval.i_value) = ((yyvsp[(1) - (3)].i_value) | (yyvsp[(3) - (3)].i_value)) & ~EX_PAREN;
			    }
    break;

  case 86:
#line 592 "bc.y"
    {
			      if (((yyvsp[(1) - (3)].i_value) & EX_VOID) || ((yyvsp[(3) - (3)].i_value) & EX_VOID))
				yyerror ("void expression with -");
			      generate ("-");
			      (yyval.i_value) = ((yyvsp[(1) - (3)].i_value) | (yyvsp[(3) - (3)].i_value)) & ~EX_PAREN;
			    }
    break;

  case 87:
#line 599 "bc.y"
    {
			      if (((yyvsp[(1) - (3)].i_value) & EX_VOID) || ((yyvsp[(3) - (3)].i_value) & EX_VOID))
				yyerror ("void expression with *");
			      generate ("*");
			      (yyval.i_value) = ((yyvsp[(1) - (3)].i_value) | (yyvsp[(3) - (3)].i_value)) & ~EX_PAREN;
			    }
    break;

  case 88:
#line 606 "bc.y"
    {
			      if (((yyvsp[(1) - (3)].i_value) & EX_VOID) || ((yyvsp[(3) - (3)].i_value) & EX_VOID))
				yyerror ("void expression with /");
			      generate ("/");
			      (yyval.i_value) = ((yyvsp[(1) - (3)].i_value) | (yyvsp[(3) - (3)].i_value)) & ~EX_PAREN;
			    }
    break;

  case 89:
#line 613 "bc.y"
    {
			      if (((yyvsp[(1) - (3)].i_value) & EX_VOID) || ((yyvsp[(3) - (3)].i_value) & EX_VOID))
				yyerror ("void expression with %");
			      generate ("%");
			      (yyval.i_value) = ((yyvsp[(1) - (3)].i_value) | (yyvsp[(3) - (3)].i_value)) & ~EX_PAREN;
			    }
    break;

  case 90:
#line 620 "bc.y"
    {
			      if (((yyvsp[(1) - (3)].i_value) & EX_VOID) || ((yyvsp[(3) - (3)].i_value) & EX_VOID))
				yyerror ("void expression with ^");
			      generate ("^");
			      (yyval.i_value) = ((yyvsp[(1) - (3)].i_value) | (yyvsp[(3) - (3)].i_value)) & ~EX_PAREN;
			    }
    break;

  case 91:
#line 627 "bc.y"
    {
			      if ((yyvsp[(2) - (2)].i_value) & EX_VOID)
				yyerror ("void expression with unary -");
			      generate ("n");
			      (yyval.i_value) = (yyvsp[(2) - (2)].i_value) & ~EX_PAREN;
			    }
    break;

  case 92:
#line 634 "bc.y"
    {
			      (yyval.i_value) = EX_REG;
			      if ((yyvsp[(1) - (1)].i_value) < 0)
				snprintf (genstr, genlen, "L%d:", -(yyvsp[(1) - (1)].i_value));
			      else
				snprintf (genstr, genlen, "l%d:", (yyvsp[(1) - (1)].i_value));
			      generate (genstr);
			    }
    break;

  case 93:
#line 643 "bc.y"
    {
			      int len = strlen((yyvsp[(1) - (1)].s_value));
			      (yyval.i_value) = EX_REG;
			      if (len == 1 && *(yyvsp[(1) - (1)].s_value) == '0')
				generate ("0");
			      else if (len == 1 && *(yyvsp[(1) - (1)].s_value) == '1')
				generate ("1");
			      else
				{
				  generate ("K");
				  generate ((yyvsp[(1) - (1)].s_value));
				  generate (":");
				}
			      free ((yyvsp[(1) - (1)].s_value));
			    }
    break;

  case 94:
#line 659 "bc.y"
    { 
			      if ((yyvsp[(2) - (3)].i_value) & EX_VOID)
				yyerror ("void expression in parenthesis");
			      (yyval.i_value) = (yyvsp[(2) - (3)].i_value) | EX_REG | EX_PAREN;
			    }
    break;

  case 95:
#line 665 "bc.y"
    { int fn;
			      fn = lookup ((yyvsp[(1) - (4)].s_value),FUNCT);
			      if (functions[fn].f_void)
				(yyval.i_value) = EX_VOID;
			      else
				(yyval.i_value) = EX_REG;
			      if ((yyvsp[(3) - (4)].a_value) != NULL)
				{ char *params = call_str ((yyvsp[(3) - (4)].a_value));
				  set_genstr_size (20 + strlen (params));
				  snprintf (genstr, genlen, "C%d,%s:", fn,
				  	    params);
				  free_args ((yyvsp[(3) - (4)].a_value));
				}
			      else
				{
				  snprintf (genstr, genlen, "C%d:", fn);
				}
			      generate (genstr);
			    }
    break;

  case 96:
#line 685 "bc.y"
    {
			      (yyval.i_value) = EX_REG;
			      if ((yyvsp[(2) - (2)].i_value) < 0)
				{
				  if ((yyvsp[(1) - (2)].c_value) == '+')
				    snprintf (genstr, genlen, "DA%d:L%d:", -(yyvsp[(2) - (2)].i_value), -(yyvsp[(2) - (2)].i_value));
				  else
				    snprintf (genstr, genlen, "DM%d:L%d:", -(yyvsp[(2) - (2)].i_value), -(yyvsp[(2) - (2)].i_value));
				}
			      else
				{
				  if ((yyvsp[(1) - (2)].c_value) == '+')
				    snprintf (genstr, genlen, "i%d:l%d:", (yyvsp[(2) - (2)].i_value), (yyvsp[(2) - (2)].i_value));
				  else
				    snprintf (genstr, genlen, "d%d:l%d:", (yyvsp[(2) - (2)].i_value), (yyvsp[(2) - (2)].i_value));
				}
			      generate (genstr);
			    }
    break;

  case 97:
#line 704 "bc.y"
    {
			      (yyval.i_value) = EX_REG;
			      if ((yyvsp[(1) - (2)].i_value) < 0)
				{
				  snprintf (genstr, genlen, "DL%d:x", -(yyvsp[(1) - (2)].i_value));
				  generate (genstr); 
				  if ((yyvsp[(2) - (2)].c_value) == '+')
				    snprintf (genstr, genlen, "A%d:", -(yyvsp[(1) - (2)].i_value));
				  else
				      snprintf (genstr, genlen, "M%d:", -(yyvsp[(1) - (2)].i_value));
				}
			      else
				{
				  snprintf (genstr, genlen, "l%d:", (yyvsp[(1) - (2)].i_value));
				  generate (genstr);
				  if ((yyvsp[(2) - (2)].c_value) == '+')
				    snprintf (genstr, genlen, "i%d:", (yyvsp[(1) - (2)].i_value));
				  else
				    snprintf (genstr, genlen, "d%d:", (yyvsp[(1) - (2)].i_value));
				}
			      generate (genstr);
			    }
    break;

  case 98:
#line 727 "bc.y"
    {
			      if ((yyvsp[(3) - (4)].i_value) & EX_VOID)
				yyerror ("void expression in length()");
			      generate ("cL");
			      (yyval.i_value) = EX_REG;
			    }
    break;

  case 99:
#line 735 "bc.y"
    {
			      if ( ((yyvsp[(3) - (8)].i_value) & EX_VOID) || ((yyvsp[(5) - (8)].i_value) & EX_VOID) || ((yyvsp[(7) - (8)].i_value) & EX_VOID) )
				yyerror ("void expression in powmod(a,b,r)");
			      generate ("cM");
			      (yyval.i_value) = EX_REG;
			    }
    break;

  case 100:
#line 742 "bc.y"
    {
			      if ((yyvsp[(3) - (4)].i_value) & EX_VOID)
				yyerror ("void expression in F(n)");
			      generate ("cF");
			      (yyval.i_value) = EX_REG;
			    }
    break;

  case 101:
#line 749 "bc.y"
    {
			      if ( ((yyvsp[(3) - (6)].i_value) & EX_VOID) || ((yyvsp[(5) - (6)].i_value) & EX_VOID) )
				yyerror ("void expression in P(n,r)");
			      generate ("cP");
			      (yyval.i_value) = EX_REG;
			    }
    break;

  case 102:
#line 756 "bc.y"
    {
			      if ( ((yyvsp[(3) - (6)].i_value) & EX_VOID) || ((yyvsp[(5) - (6)].i_value) & EX_VOID) )
				yyerror ("void expression in C(n,r)");
			      generate ("cC");
			      (yyval.i_value) = EX_REG;
			    }
    break;

  case 103:
#line 764 "bc.y"
    {
			      if ((yyvsp[(3) - (4)].i_value) & EX_VOID)
				yyerror ("void expression in sqrt()");
			      generate ("cR");
			      (yyval.i_value) = EX_REG;
			    }
    break;

  case 104:
#line 771 "bc.y"
    {
			      if ((yyvsp[(3) - (4)].i_value) & EX_VOID)
				yyerror ("void expression in scale()");
			      generate ("cS");
			      (yyval.i_value) = EX_REG;
			    }
    break;

  case 105:
#line 778 "bc.y"
    {
			      ct_warn ("read function");
			      generate ("cI");
			      (yyval.i_value) = EX_REG;
			    }
    break;

  case 106:
#line 784 "bc.y"
    {
			      ct_warn ("random function");
			      generate ("cX");
			      (yyval.i_value) = EX_REG;
			    }
    break;

  case 107:
#line 791 "bc.y"
    { (yyval.i_value) = lookup((yyvsp[(1) - (1)].s_value),SIMPLE); }
    break;

  case 108:
#line 793 "bc.y"
    {
			      if ((yyvsp[(3) - (4)].i_value) & EX_VOID)
				yyerror("void expression as subscript");
			      if ((yyvsp[(3) - (4)].i_value) & EX_COMP)
				ct_warn("comparison in subscript");
			      (yyval.i_value) = lookup((yyvsp[(1) - (4)].s_value),ARRAY);
			    }
    break;

  case 109:
#line 801 "bc.y"
    { (yyval.i_value) = 0; }
    break;

  case 110:
#line 803 "bc.y"
    { (yyval.i_value) = 1; }
    break;

  case 111:
#line 805 "bc.y"
    { (yyval.i_value) = 2; }
    break;

  case 112:
#line 807 "bc.y"
    { (yyval.i_value) = 3;
			      ct_warn ("History variable");
			    }
    break;

  case 113:
#line 811 "bc.y"
    { (yyval.i_value) = 4;
			      ct_warn ("Last variable");
			    }
    break;

  case 114:
#line 817 "bc.y"
    { ct_warn ("End of line required"); }
    break;

  case 116:
#line 820 "bc.y"
    { ct_warn ("Too many end of lines"); }
    break;


/* Line 1267 of yacc.c.  */
#line 2684 "bc.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 823 "bc.y"


