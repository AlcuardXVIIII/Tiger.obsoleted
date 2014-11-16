%token NUM STR
%left '+' '-'
%left '*'
%%
exp : exp '+' exp
    | exp '-' exp
    | exp '*' exp
    | exp '/' exp
    | NUM
    ;
useless: STR
%%
