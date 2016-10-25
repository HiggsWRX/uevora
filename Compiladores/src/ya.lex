%{
#include <stdlib.h>
#include <string.h>
#include "apt.h"
#include "semantica.h"
#include "parser.h"

int btoi(char *text)
{
    return *text == 't';
}
%}

INTLIT [0-9]+
FLTLIT [0-9]*\.[0-9]+([eE][\+\-]?[0-9]+)?
BOOL "true"|"false"
VAR_TYPE "int"|"float"|"string"|"bool"|"void"
ID [a-zA-Z][a-zA-Z0-9_]*
STRING \".*\"

%%

{INTLIT}  { yylval.intlit = atof(yytext); return INTLIT; }
{FLTLIT}  { yylval.fltlit = atof(yytext); return FLTLIT; }
{BOOL}    { yylval.intlit = btoi(yytext); return BOOL; } 
{VAR_TYPE}    { yylval.str = strdup(yytext); return VAR_TYPE; }

"define"    { return DEF; }
"if"        { return IF; }
"else"      { return ELSE; }
"then"      { return THEN; }
"return"    { return RETURN; }
"while"     { return WHILE; }
"do"        { return DO; }
"break"     { return BREAK; }
"and"       { return AND; }
"or"        { return OR; }
"not"       { return NOT; }
"next"      { return NEXT; }

"=="        { return EQUALS; }
"<"         { return LESS; }
">"         { return BIGGER; }
"<="        { return LESSEQUALS; }
">="        { return BIGGEREQUALS; }
"!="        { return DIF; }

"+"         { return ADD; }
"-"         { return SUB; }
"/"         { return DIV; }
"*"         { return MUL; }
"^"         { return EXPO; }
"("         { return LPAR; }
")"         { return RPAR; }
"{"         { return LBRK; }
"}"         { return RBRK; }
"="         { return ASSIGN; }
"mod"       { return MOD; }

","         { return COMMA; }
":"         { return CLN; }
{STRING}  { yylval.str = strdup(yytext); return STRING; }
{ID}      { yylval.str = strdup(yytext); return ID; }
";"         { return SMCL; }

%%

int yywrap()
{
    return 1;
}