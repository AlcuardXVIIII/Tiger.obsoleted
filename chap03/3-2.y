%{
#include <stdio.h>
#include "util.h"
#include "errormsg.h"

int yylex(void); /* function prototype */

void yyerror(char *s)
{
 EM_error(EM_tokPos, "%s", s);
}
%}


%union {
        int pos;
        int ival;
        string sval;
        }

%token <sval> ID STRING
%token <ival> INT

%token
  PLUS MINUS MUL DIV LPARAM RPARAM
%start exp
%left PLUS MINUS
%left MUL DIV
%%

exp : ID
  | INT
  | exp PLUS exp
  | exp MINUS exp
  | exp MUL exp
  | exp DIV exp
  | LPARAM exp RPARAM
