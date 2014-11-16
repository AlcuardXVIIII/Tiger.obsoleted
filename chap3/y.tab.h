/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
    TYPE_ID = 260,
    INT = 261,
    COMMA = 262,
    COLON = 263,
    SEMICOLON = 264,
    LPAREN = 265,
    RPAREN = 266,
    LBRACK = 267,
    RBRACK = 268,
    LBRACE = 269,
    RBRACE = 270,
    DOT = 271,
    ASSIGN = 272,
    ARRAY = 273,
    IF = 274,
    THEN = 275,
    ELSE = 276,
    WHILE = 277,
    FOR = 278,
    TO = 279,
    LET = 280,
    IN = 281,
    END = 282,
    OF = 283,
    DO = 284,
    BREAK = 285,
    NIL = 286,
    FUNCTION = 287,
    VAR = 288,
    TYPE = 289,
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
#define TYPE_ID 260
#define INT 261
#define COMMA 262
#define COLON 263
#define SEMICOLON 264
#define LPAREN 265
#define RPAREN 266
#define LBRACK 267
#define RBRACK 268
#define LBRACE 269
#define RBRACE 270
#define DOT 271
#define ASSIGN 272
#define ARRAY 273
#define IF 274
#define THEN 275
#define ELSE 276
#define WHILE 277
#define FOR 278
#define TO 279
#define LET 280
#define IN 281
#define END 282
#define OF 283
#define DO 284
#define BREAK 285
#define NIL 286
#define FUNCTION 287
#define VAR 288
#define TYPE 289
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
#line 15 "tiger.grm" /* yacc.c:1909  */

	int pos;
	int ival;
	string sval;
	

#line 155 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
