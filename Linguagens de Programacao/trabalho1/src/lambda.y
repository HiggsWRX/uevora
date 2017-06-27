%{
#include <stdio.h>
#include <string.h>
#include "apt.h"
#include "ll.h"
#include "reductions.h"

int yylex (void);
void yyerror (char const *);

%}
            
%union {
    char *str;
    node node;
}

/* Bison declarations.  */
%token  <str>       VAR
%token              LAMBDA DOT
%token              LPAR RPAR

%type   <node>      term
%type   <node>      termlist
%type   <node>      lamlist
%type   <node>      lam
%%


prgrm:  termlist { analiseapt($1); }
;

termlist:   termlist term   { $$ = aplicnode($1, $2); }
    |       term            { $$ = $1; }
;

term:   VAR                 { $$ = varnode($1); }
    |   LPAR lamlist termlist RPAR { $$ = pairnode($2, $3); }
;
lamlist:    lamlist lam     { $$ = pairnode($1, $2); }
    |       lam             { $$ = $1; }
;
lam:    LAMBDA VAR { $<node>$ = varnode($2); } DOT { $$ = absnode($<node>3, NULL); }
;
%%

/* Called by yyparse on error.  */

void yyerror (char const *s)
{
    fprintf (stderr, "%s\n", s);
}

int main (void)
{
    return yyparse();
}
