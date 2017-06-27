%{
#include <stdlib.h>
#include <string.h>
#include "apt.h"
#include "ll.h"
#include "reductions.h"
#include "parser.h"
%}

VAR [a-z]
esp [ \t]+
nl  [\r\n]+

%%

"("         { return LPAR; }
")"         { return RPAR; }

"."         { return DOT; }
"!"         { return LAMBDA; }
{VAR}       { yylval.str = strdup(yytext); return VAR; }
{esp}   ;
{nl}    ;

%%

int yywrap()
{
    return 1;
}
