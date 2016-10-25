#ifndef _semantica_h
#define _semantica_h
#include "hashtable.h"

typedef struct ST {
    hash *h;
    struct ST *prox;
} ST;

void initst();
ST *newsymtable();
void createcontext();
void dropcontext();
void insertst(char *word, type t);
type lookupst(char *word);
type lookuplocalst(char *word);
type *getfunctionargs(char *word);

void analisedeclist(declist decls);
type analisedecl(decl d);
void analiseexplist(explist e, type *fargs);
type analiseexp(expr e);
void analisestmlist(stmlist stms);
type analisestm(stm s);
void analisearglist(arglist args, type *fargs);
type analisearg(arg a);
type analiseargexp(expr e);

void initfunctions();
#endif