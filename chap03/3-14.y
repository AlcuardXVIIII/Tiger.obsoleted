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


%token
  ID ASSIGN OR AND EQUAL PLUS
%start stm
%left OR
%left AND
%left PLUS
%%

stm : ID ASSIGN ae
    | ID ASSIGN be

ae : be OR be
   | be AND be
   | ae EQUAL ae
   | ID
be : ae PLUS ae
   | ID
