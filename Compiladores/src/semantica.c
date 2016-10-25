#include <stdlib.h>
#include "semantica.h"

ST *globalst;
char *currentfunction;

void initst()
{
    globalst = newsymtable();
}

ST *newsymtable()
{
    ST *s = malloc(sizeof(ST));
    inithash(&(s->h));
    s->prox = NULL;
    return s;
}

void createcontext()
{
    ST *s = newsymtable();
    s->prox = globalst;
    globalst = s;
}

void dropcontext()
{
    ST *s = globalst;
    globalst = globalst->prox;
    free(s);
}

void insertst(char *word, type t)
{
    insert(globalst->h, word, t);
}

type lookupst(char *word)
{
    type t1 = getval(globalst->h, word);
    if (!t1) {
        if (globalst->prox) {
            t1 = getval((globalst->prox)->h, word);
        }
    }

    return t1;
}

type lookuplocalst(char *word)
{
    type t1 = getval(globalst->h, word);

    return t1;
}

type *getfunctionargs(char *word)
{
    type *t1 = getvalues(globalst->h, word);
    if (!t1) {
        if (globalst->prox) {
            t1 = getvalues(globalst->prox->h, word);
        }
    }

    return t1;
}

int isarithmeticoperation(char c)
{
    return (c == '+' || 
            c == '-' ||
            c == '/' ||
            c == '*' ||
            c == '^' ||
            c == '%');
}

void analisedeclist(declist decls)
{
    static int symtableinitialized = 0;

    if (!symtableinitialized) {
        globalst = newsymtable();
        //initfunctions();
        symtableinitialized = 1;
    }

    switch (decls->kind) {
        case singledecl:
            analisedecl(decls->u.decliststruct.d);
            break;
        case multipledecls:
            analisedecl(decls->u.decliststruct.d);
            analisedeclist(decls->u.decliststruct.decls);
            break;
    }
}

type analisedecl(decl d)
{
    type t1;
    type t2;
    type *fargs;
    idlist id;
    switch (d->kind) {
        case vardeclwval:
            t1 = d->u.var.t;
            t2 = analiseexp(d->u.var.e);
            if (t1->kind != t2->kind) {
                printf("error: rvalue does not match variable type.\n");
                exit(1);
            }
        case vardecl:
            id = d->u.var.id;
            while (id) {
                if (lookupst(id->u.idliststruct.id)) {
                    printf("warning: var <%s> is already declared.\n", id->u.idliststruct.id);
                }
                insertst(id->u.idliststruct.id, d->u.var.t);
                id = id->u.idliststruct.ids;
            }
            return d->u.var.t;
            break;
        case typedecl:
            if (lookupst(d->u.newtype.id)) {
                printf("error: type <%s> already exists.\n", d->u.newtype.id);
                exit(1);
            }
            insertst(d->u.newtype.id, d->u.newtype.t);
            return d->u.newtype.t;
            break;
        case functiondecl:
            currentfunction = d->u.function.id;
            if (lookupst(currentfunction)) {
                printf("error: function <%s> is already declared.\n", currentfunction);
                exit(1);
            }
            insertst(currentfunction, d->u.function.t);
            createcontext();
            analisestmlist(d->u.function.stms);
            dropcontext();
            currentfunction = NULL;
            return d->u.function.t;
            break;
        case functiondeclwargs:
            currentfunction = d->u.function.id;
            if (lookupst(currentfunction)) {
                printf("error: function <%s> is already declared.\n", currentfunction);
                exit(1);
            }
            insertst(currentfunction, d->u.function.t);
            fargs = getfunctionargs(currentfunction);
            createcontext();
            analisearglist(d->u.function.args, fargs);
            analisestmlist(d->u.function.stms);
            dropcontext();
            currentfunction = NULL;
            return d->u.function.t;
            break;
    }
}

void analiseexplist(explist e, type *fargs)
{
    static int currentarg = 1;
    type t1;
    type t2;
    switch (e->kind) {
        case singleexp:
            t1 = analiseargexp(e->u.expliststruct.e);
            t2 = fargs[currentarg++];
            if (t1->kind != t2->kind) {
                printf("error: calling function with invalid argument type.\n");
                exit(1);
            }
            currentarg = 1;
            break;
        case multipleexps:
            t1 = analiseargexp(e->u.expliststruct.e);
            t2 = fargs[currentarg++];
            if (t1->kind != t2->kind) {
                printf("error: calling function with invalid argument type.\n");
                exit(1);
            }
            analiseexplist(e->u.expliststruct.exps, fargs);
            break;
    }
}

type analiseexp(expr e)
{
    type t1;
    type t2;
    type *fargs;
    switch (e->kind) {
        case intexp:
            return typenode("int");
            break;
        case floatexp:
            return typenode("float");
            break;
        case boolexp:
            return typenode("bool");
            break;
        case stringexp:
            return typenode("string");
            break;
        case idexp:
            return lookupst(e->u.id);
            break;
        case binopexp:
            t1 = analiseexp(e->u.binop.arg1);
            t2 = analiseexp(e->u.binop.arg2);
            if (t1->kind != t2->kind) {
                printf("error: binop between different types.\n");
                exit(1);
            } else if (t1->kind == newtype){
                printf("error: binop between new types not supported.\n");
            } else {
                if (isarithmeticoperation(e->u.binop.op[0])) {
                    return t1;
                } else if ((e->u.binop.op[0] == '&'  ||
                            e->u.binop.op[0] == '|') &&
                            t1->kind != booltype) {
                    printf("error: boolean operation between non boolean expression.\n");
                    exit(1);
                } else {
                    return typenode("bool");
                }
            }
            break;
        case unopexp:
            t1 = analiseexp(e->u.binop.arg1);
            if (e->u.binop.op[0] == '!' && t1->kind != booltype) {
                printf("error: NOT can only be used with boolean expression.\n");
                exit(1);
            }
            return t1;
            break;
        case assignexp:
            t1 = lookupst(e->u.assign.id);
            t2 = analiseexp(e->u.assign.e);
            if (t1->kind != t2->kind) {
                printf("error: rvalue does not match variable type.\n");
                exit(1);
            } else {
                return t1;
            }
            break;
        case fcallexp:
            return lookupst(e->u.fcall.id);
            break;
        case fcallwargsexp:
            fargs = getfunctionargs(e->u.fcall.id);
            analiseexplist(e->u.fcall.args, fargs);
            return lookupst(e->u.fcall.id);
            break;
    }
}

void analisestmlist(stmlist stms)
{
    switch (stms->kind) {
        case singlestm:
            analisestm(stms->u.stmliststruct.s);
            break;
        case multiplestms:
            analisestm(stms->u.stmliststruct.s);
            analisestmlist(stms->u.stmliststruct.stms);
            break;
    }
}

type analisestm(stm s)
{
    type t1;
    type t2;
    switch (s->kind) {
        case declstm:
            return analisedecl(s->u.d);
            break;
        case expstm:
            return analiseexp(s->u.e);
            break;
        case whilestm:
        case ifstm:
            t1 = analiseexp(s->u.cicle.e);
            if (t1->kind != booltype) {
                printf("error: if condition not a boolean.\n");
                exit(1);
            }
            analisestmlist(s->u.cicle.stms);
            break;
        case ifelsestm:
            t1 = analiseexp(s->u.cicle.e);
            if (t1->kind != booltype) {
                printf("error: if condition not a boolean.\n");
                exit(1);
            }
            analisestmlist(s->u.cicle.stms);
            analisestmlist(s->u.cicle.elsestms);
            break;
        case returnstm:
            t1 = analiseexp(s->u.e);
            if (currentfunction) {
                t2 = lookupst(currentfunction);
                if (t1->kind != t2->kind) {
                    printf("error: return type does not match function type.\n");
                    exit(1);
                } else {
                    return t1;
                }
            } else {
                printf("error: return cannot be used outside a function.\n");
                exit(1);
            }
            break;
    }
}

void analisearglist(arglist args, type *fargs)
{
    static int argindex = 1;
    switch (args->kind) {
        case singlearg:
            fargs[argindex] = analisearg(args->u.argliststruct.a);
            argindex = 1;
            break;
        case multipleargs:
            fargs[argindex++] = analisearg(args->u.argliststruct.a);
            analisearglist(args->u.argliststruct.args, fargs);
            break;
    }
}

type analisearg(arg a)
{
    if(lookuplocalst(a->u.argument.id)) {
        printf("error: argument <%s> is already declared\n", a->u.argument.id);
        exit(1);
    }

    insertst(a->u.argument.id, a->u.argument.t);

    return a->u.argument.t;
}

type analiseargexp(expr e)
{
    return analiseexp(e);
}
/*
void initfunctions()
{
    insertst("print", type_primitive_node("void"));
}
*/