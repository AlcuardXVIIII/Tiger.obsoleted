%{
#include <string.h>
#include "util.h"
#include "tokens.h"
#include "errormsg.h"
#include "3-12.tab.h"
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
digits [0-9]+
id [a-zA-z][a-zA-z0-9]*
%%
id       {adjust();return ID;}
":="     {adjust();return ASSIGN;}
while    {adjust();return WHILE;}
do       {adjust();return DO;}
begin    {adjust();return BEGIN;}
end      {adjust();return END;}
if       {adjust();return IF;}
then     {adjust();return then;}
else     {adjust();return ELSE;}
";"      {adjust();return SIMI;}
" "      {adjust(); continue;}
\n       {adjust(); EM_newline(); continue;}
","      {adjust(); return COMMA;}
digits   {adjust(); yylval.ival=atoi(yytext); return INT;}
.        {adjust(); EM_error(EM_tokPos,"illegal token");}
