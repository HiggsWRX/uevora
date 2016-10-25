#include <stdlib.h>
#include <string.h>
#include "apt.h"

decl vardeclnode(idlist id, type t, expr e)
{ 
    decl ret = malloc(sizeof(*ret));
    ret->u.var.id = id;
    ret->u.var.t = t;
    if (e) {
        ret->kind = vardeclwval;
        ret->u.var.e = e;
    } else {
        ret->kind = vardecl;
    }

    return ret;
}

decl typedeclnode(char *id, type t) {
    decl ret = malloc(sizeof(*ret));
    ret->kind = typedecl;
    ret->u.newtype.id = id;
    ret->u.newtype.t = t;

    return ret;
}

decl functiondeclnode(char *id, arglist args, type t, stmlist stms)
{
    decl ret = malloc(sizeof(*ret));
    ret->u.function.id = id;
    ret->u.function.t = t;
    ret->u.function.stms = stms;
    if (args) {
        ret->kind = functiondeclwargs;
        ret->u.function.args = args;
    } else {
        ret->kind = functiondecl;
    }

    return ret;
}

declist declistnode(decl d, declist decls)
{
    declist ret = malloc(sizeof(*ret));

    if (decls) {
        ret->kind = multipledecls;
        ret->u.decliststruct.decls = decls;
    } else {
        ret->kind = singledecl;
    }
    ret->u.decliststruct.d = d;

    return ret;
}

expr intexpnode(int i)
{
    expr ret = malloc(sizeof(*ret));
    ret->kind = intexp;
    ret->u.i = i;

    return ret;
}

expr floatexpnode(float f)
{
    expr ret = malloc(sizeof(*ret));
    ret->kind = floatexp;
    ret->u.f = f;

    return ret;
}

expr boolexpnode(int i)
{
    expr ret = malloc(sizeof(*ret));
    ret->kind = boolexp;
    ret->u.i = i;

    return ret;
}

expr stringexpnode(char *id)
{
    expr ret = malloc(sizeof(*ret));
    ret->kind = stringexp;
    ret->u.id = id;

    return ret;
}

expr idexpnode(char *id)
{
    expr ret = malloc(sizeof(*ret));
    ret->kind = idexp;
    ret->u.id = id;

    return ret;
}


expr binopexpnode(char op[], expr arg1, expr arg2)
{
    expr ret = malloc(sizeof(*ret));
    ret->kind = binopexp;
    strcpy(ret->u.binop.op, op);
    ret->u.binop.arg1 = arg1;
    ret->u.binop.arg2 = arg2;

    return ret;
}

expr unopexpnode(char op[], expr arg1)
{
    expr ret = malloc(sizeof(*ret));
    ret->kind = unopexp;
    strcpy(ret->u.binop.op, op);
    ret->u.binop.arg1 = arg1;

    return ret;
}

expr assignexpnode(char *id, expr e)
{
    expr ret = malloc(sizeof(*ret));
    ret->kind = assignexp;
    ret->u.assign.id = id;
    ret->u.assign.e = e;

    return ret;
}

expr fcallexpnode(char *id, explist args)
{
    expr ret = malloc(sizeof(*ret));
    ret->u.fcall.id = id;
    if (args) {
        ret->kind = fcallwargsexp;
        ret->u.fcall.args = args;
    } else {
        ret->kind = fcallexp;
    }

    return ret;
}

explist explistnode(expr e, explist exps)
{
    explist ret = malloc(sizeof(*ret));

    if (exps) {
        ret->kind = multipleexps;
        ret->u.expliststruct.exps = exps;
    } else {
        ret->kind = singleexp;
    }
    ret->u.expliststruct.e = e;

    return ret;
}

stmlist stmlistnode(stm s, stmlist stms)
{
    stmlist ret = malloc(sizeof(*ret));
    
    if (stms) {
        ret->kind = multiplestms;
        ret->u.stmliststruct.stms = stms;
    } else {
        ret->kind = singlestm;
    }
    ret->u.stmliststruct.s = s;

    return ret;
}

stm declstmnode(decl d)
{
    stm ret = malloc(sizeof(*ret));
    ret->kind = declstm;
    ret->u.d = d;

    return ret;
}

stm expstmnode(expr e)
{
    stm ret = malloc(sizeof(*ret));
    ret->kind = expstm;
    ret->u.e = e;

    return ret;
}

stm ifstmnode(expr e, stmlist ifstms, stmlist elsestms)
{
    stm ret = malloc(sizeof(*ret));
    ret->u.cicle.e = e;
    ret->u.cicle.stms = ifstms;
    if (elsestms) {
        ret->kind = ifelsestm;
        ret->u.cicle.elsestms = elsestms;
    } else {
        ret->kind = ifstm;
    }

    return ret;
}

stm whilestmnode(expr e, stmlist stms)
{
    stm ret = malloc(sizeof(*ret));

    ret->kind = whilestm;
    ret->u.cicle.e = e;
    ret->u.cicle.stms = stms;

    return ret;
}

stm returnstmnode(expr e)
{
    stm ret = malloc(sizeof(*ret));

    ret->kind = returnstm;
    ret->u.e = e;

    return ret;
}

arglist arglistnode(arg a, arglist args)
{
    arglist ret = malloc(sizeof(*ret));

    if (args) {
        ret->kind = multipleargs;
        ret->u.argliststruct.args = args;
    } else {
        ret->kind = singlearg;
    }
    ret->u.argliststruct.a = a;

    return ret;
}

arg argnode(char *id, type t)
{
    arg ret = malloc(sizeof(*ret));

    ret->kind = idarg;

    ret->u.argument.id = id;
    ret->u.argument.t = t;

    return ret;
}

idlist idlistnode(char *id, idlist ids)
{
    idlist ret = malloc(sizeof(*ret));

    if (ids) {
        ret->kind = multipleids;
        ret->u.idliststruct.ids = ids;
    } else {
        ret->kind = singleid;
    }
    ret->u.idliststruct.id = id;

    return ret;
}

type typenode(char *id)
{
    type ret = malloc(sizeof(*ret));

    if (strcmp(id, "int") == 0) {
        ret->kind = inttype;
    } else if (strcmp(id, "float") == 0) {
        ret->kind = floattype;
    } else if (strcmp(id, "string") == 0) {
        ret->kind = stringtype;
    } else if (strcmp(id, "bool") == 0) {
        ret->kind = booltype;
    } else if (strcmp(id, "void") == 0) {
        ret->kind = voidtype;
    } else {
        ret->kind = newtype;
    };
    ret->u.id = id;

    return ret;
}