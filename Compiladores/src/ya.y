%{
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "semantica.h"
#include "apt.h"

int yylex (void);
void yyerror (char const *);

%}
            
%union {
    int intlit;
    double fltlit;
    char *str;
    declist declist;
    decl decl;
    stmlist stmlist;
    stm stm;
    explist explist;
    expr expr;
    arglist arglist;
    arg arg;
    idlist idlist;
    type type;
}

/* Bison declarations.  */
%left               SMCL
%token  <intlit>    INTLIT BOOL
%token  <fltlit>    FLTLIT
%token  <str>       ID STRING VAR_TYPE
%token              DEF IF ELSE THEN RETURN WHILE DO BREAK NEXT CLN

%right              ASSIGN
%left               OR
%left               AND
%left               NOT
%nonassoc           EQUALS LESS LESSEQUALS BIGGER BIGGEREQUALS DIF
%left               SUB ADD
%left               MUL DIV MOD
%right              EXPO
%left               NEG

%token              LPAR RPAR COMMA LBRK RBRK
            
%type   <declist>   declist
%type   <decl>      decl
%type   <explist>   explist
%type   <expr>      expr
%type   <stmlist>   stmlist
%type   <stm>       stm
%type   <arglist>   arglist
%type   <arg>       arg
%type   <idlist>    idlist
%type   <type>      type
%%


prgrm:  declist { analisedeclist($1); }
;

declist:    decl SMCL { $$ = declistnode($1, NULL); }
    |   decl SMCL declist  { $$ = declistnode($1, $3); }
;

decl:   idlist CLN type { $$ = vardeclnode($1, $3, NULL); }
    |   idlist CLN type ASSIGN expr { $$ = vardeclnode($1, $3, $5); }
    |   DEF ID type { $$ = typedeclnode($2, $3); }
    |   ID LPAR RPAR CLN type LBRK stmlist RBRK { $$ = functiondeclnode($1, NULL, $5, $7); }
    |   ID LPAR arglist RPAR CLN type LBRK stmlist RBRK { $$ = functiondeclnode($1, $3, $6, $8); }
;

stmlist:    stm SMCL { $$ = stmlistnode($1, NULL); }
    |   stm SMCL stmlist { $$ = stmlistnode($1, $3); }
;

stm:    decl { $$ = declstmnode($1); }
    |   expr { $$ = expstmnode($1); }
    |   IF expr THEN LBRK stmlist RBRK { $$ = ifstmnode($2, $5, NULL); }
    |   IF expr THEN LBRK stmlist RBRK ELSE LBRK stmlist RBRK { $$ = ifstmnode($2, $5, $9); }
    |   WHILE expr DO LBRK stmlist RBRK { $$ = whilestmnode($2, $5); }
    |   RETURN expr { $$ = returnstmnode($2); }
;

explist:    expr { $$ = explistnode($1, NULL); }
    |   expr COMMA explist { $$ = explistnode($1, $3); }
;

expr:   ID { $$ = idexpnode($1); }
    |   INTLIT { $$ = intexpnode($1); }
    |   FLTLIT { $$ = floatexpnode($1); }
    |   BOOL { $$ = boolexpnode($1); }
    |   STRING { $$ = stringexpnode($1); }
    |   ID ASSIGN expr { $$ = assignexpnode($1, $3); }
    |   expr ADD expr { $$ = binopexpnode("+", $1, $3); }
    |   expr SUB expr { $$ = binopexpnode("-", $1, $3); }
    |   expr DIV expr { $$ = binopexpnode("/", $1, $3); }
    |   expr MUL expr { $$ = binopexpnode("*", $1, $3); }
    |   expr EXPO expr { $$ = binopexpnode("^", $1, $3); }
    |   expr MOD expr { $$ = binopexpnode("%", $1, $3); }
    |   NOT expr { $$ = unopexpnode("!", $2); }
    |   expr AND expr { $$ = binopexpnode("&&", $1, $3); }
    |   expr OR expr { $$ = binopexpnode("||", $1, $3); }
    |   SUB expr %prec NEG { $$ = unopexpnode("-", $2); }
    |   expr EQUALS expr { $$ = binopexpnode("==", $1, $3); }
    |   expr LESS expr { $$ = binopexpnode("<", $1, $3); }
    |   expr LESSEQUALS expr { $$ = binopexpnode("<=", $1, $3); }
    |   expr BIGGER expr { $$ = binopexpnode(">", $1, $3); }
    |   expr BIGGEREQUALS expr { $$ = binopexpnode(">=", $1, $3); }
    |   expr DIF expr { $$ = binopexpnode("!=", $1, $3); }
    |   LPAR expr RPAR { $$ = $2; }
    |   ID LPAR explist RPAR { $$ = fcallexpnode($1, $3); }
    |   ID LPAR RPAR { $$ = fcallexpnode($1, NULL); }
;

arglist:    arg { $$ = arglistnode($1, NULL); }
    |   arg COMMA arglist { $$ = arglistnode($1, $3); }
;

arg:    ID CLN type { $$ = argnode($1, $3); }
;

idlist: ID { $$ = idlistnode($1, NULL); }
    | ID COMMA idlist { $$ = idlistnode($1, $3); }
;

type:   VAR_TYPE { $$ = typenode($1); }
    |   ID { $$ = typenode($1); }
;
%%

/* Called by yyparse on error.  */

void yyerror (char const *s)
{
    fprintf (stderr, "%s\n", s);
}

int main (void)
{
    initst();
    return yyparse();
}
