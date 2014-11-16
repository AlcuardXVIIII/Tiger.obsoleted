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
    OR = 289,
    AND = 290,
    EQ = 291,
    NEQ = 292,
    LT = 293,
    LE = 294,
    GT = 295,
    GE = 296,
    PLUS = 297,
    MINUS = 298,
    TIMES = 299,
    DIVIDE = 300,
    UMINUS = 301
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
#define OR 289
#define AND 290
#define EQ 291
#define NEQ 292
#define LT 293
#define LE 294
#define GT 295
#define GE 296
#define PLUS 297
#define MINUS 298
#define TIMES 299
#define DIVIDE 300
#define UMINUS 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 21 "tiger.grm" /* yacc.c:1909  */

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
	

#line 167 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
