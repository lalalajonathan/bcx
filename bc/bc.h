/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 52 "bc.y"
{
	char	 *s_value;
	char	  c_value;
	int	  i_value;
	arg_list *a_value;
       }
/* Line 1529 of yacc.c.  */
#line 138 "bc.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

