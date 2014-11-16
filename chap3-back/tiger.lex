%{
#include <string.h>
#include "util.h"
#include "errormsg.h"
#include "y.tab.h"
int charPos=1;

int yywrap(void)
{
 charPos=1;
 return 1;
}


void adjust(void)
{
 EM_tokPos=charPos;
 charPos+=yyleng;
}

%}

%%
\"(\\.|[^\\\"])*\"  {adjust(); yylval.sval=yytext;return STRING;}
[ \t]*	 {adjust(); printf(" ");continue;}
\n	 {adjust(); printf("\n");EM_newline(); continue;}
","	 {adjust(); printf(",");return COMMA;}
":"      {adjust();printf(":");return COLON;}
";"      {adjust();printf(";");return SEMICOLON;}
[0-9]+	 {adjust(); yylval.ival=atoi(yytext);printf("%d",yylval.ival);return INT;}
"("      {adjust();printf("(");return LPAREN;}
")"      {adjust();printf(")");return RPAREN;}
"["      {adjust();printf("[");return LBRACK;}
"]"      {adjust();printf("]");return RBRACK;}
"{"      {adjust();printf("{");return LBRACE;}
"}"      {adjust();printf("}");return RBRACE;}
"."      {adjust();printf(".");return DOT;}
"+"      {adjust();printf("+");return PLUS;}
"-"      {adjust();printf("-");return MINUS;}
"*"      {adjust();printf("*");return TIMES;}
"/"      {adjust();printf("/");return DIVIDE;}
"="      {adjust();printf("=");return EQ;}
"<>"     {adjust();printf("<>");return NEQ;}
"<"      {adjust();printf("<");return LT;}
"<="     {adjust();printf("<=");return LE;}
">"      {adjust();printf(">");return GT;}
">="     {adjust();printf(">=");return GE;}
"&"      {adjust();printf("&");return AND;}
"|"      {adjust();printf("|");return OR;}
":="     {adjust();printf(":=");return ASSIGN;}
"array"  {adjust();printf("array");return ARRAY;}
"if"     {adjust();printf("if");return IF;}
"then"   {adjust();printf("then");return THEN;}
"else"   {adjust();printf("else");return ELSE;}
"while"  {adjust();printf("while");return WHILE;}
"for"  	 {adjust(); printf("for");return FOR;}
"to"     {adjust();printf("to");return TO;}
"do"     {adjust();printf("do");return DO;}
"let"    {adjust();printf("let");return LET;}
"in"     {adjust();printf("in");return IN;}
"end"    {adjust();printf("end");return END;}
"of"     {adjust();printf("of");return OF;}
"break"  {adjust();printf("break");return BREAK;}
"nil"    {adjust();printf("nil");return NIL;}
"function" {adjust();printf("function");return FUNCTION;}
"var"    {adjust();printf("var");return VAR;}
"type"   {adjust();printf("type");return TYPE;}
[a-zA-Z][a-zA-Z_0-9]* {adjust();yylval.sval=yytext;printf("%s",yylval.sval);return ID;}

\/\*([^\*]|\*+[^/\*])*\*+\/ {adjust();continue;}
.	 {adjust(); EM_error(EM_tokPos,"illegal token");}
