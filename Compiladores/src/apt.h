#ifndef _apt_h
#define _apt_h

typedef struct declist_ *declist;
typedef struct decl_ *decl;
typedef struct stmlist_ *stmlist;
typedef struct stm_ *stm;
typedef struct explist_ *explist;
typedef struct expr_ *expr;
typedef struct arglist_ *arglist;
typedef struct arg_ *arg;
typedef struct idlist_ *idlist;
typedef struct type_ *type;

struct declist_ {
    enum {
        singledecl,
        multipledecls
    } kind;

    union {
        struct {
            decl d;
            declist decls;
        } decliststruct;
    } u;
};

struct decl_ {
    enum {
        vardecl,
        vardeclwval,
        typedecl,
        functiondecl,
        functiondeclwargs
    } kind;

    union {
        struct {
            idlist id;
            type t;
            expr e;
            void *stnode;
        } var;
        struct {
            char *id;
            type t;
        } newtype;
        struct {
            char *id;
            arglist args;
            type t;
            stmlist stms;
        } function;
    } u;
};

struct explist_ {
    enum {
        singleexp,
        multipleexps
    } kind;

    union {
        struct {
            expr e;
            explist exps;
        } expliststruct;
    } u;
};

struct expr_ {
    enum {
        intexp,
        floatexp,
        boolexp,
        stringexp,
        idexp,
        binopexp,
        unopexp,
        assignexp,
        fcallexp,
        fcallwargsexp
    } kind;

    union {
        int i;
        float f;
        char *id;
        struct {
            char op[4];
            expr arg1;
            expr arg2;
        } binop;
        struct {
            char *id;
            expr e;
        } assign;
        struct {
            char *id;
            explist args;
        } fcall;
    } u;
};

struct stmlist_ {
    enum {
        singlestm,
        multiplestms
    } kind;

    union {
        struct {
            stm s;
            stmlist stms;
        } stmliststruct;
    } u;
};

struct stm_ {
    enum {
        declstm,
        expstm,
        ifstm,
        ifelsestm,
        whilestm,
        returnstm
    } kind;

    union {
        decl d;
        expr e;
        struct {
            expr e;
            stmlist stms;
            stmlist elsestms;
        } cicle;
    } u;
};

struct arglist_ {
    enum {
        singlearg,
        multipleargs
    } kind;
    union {
        struct {
            arg a;
            arglist args;
        } argliststruct;
    } u;
};

struct arg_ {
    enum {
        idarg
    } kind;

    union {
        struct {
            char *id;
            type t;
            void *stnode;
        } argument;
    } u;
};

struct idlist_ {
    enum {
        singleid,
        multipleids
    } kind;

    union {
        struct {
            char *id;
            idlist ids;
        } idliststruct;
    } u;
};

struct type_ {
    enum {
        inttype,
        floattype,
        stringtype,
        booltype,
        newtype,
        voidtype
    } kind;

    union {
        char *id;
    } u;
};

decl vardeclnode(idlist id, type t, expr e);
decl typedeclnode(char *id, type t);
decl functiondeclnode(char *id, arglist args, type t, stmlist stms);
declist declistnode(decl d, declist decls);
expr intexpnode(int i);
expr floatexpnode(float f);
expr boolexpnode(int b);
expr stringexpnode(char *id);
expr idexpnode(char *id);
expr binopexpnode(char op[], expr arg1, expr arg2);
expr unopexpnode(char op[], expr arg1);
expr assignexpnode(char *id, expr e);
expr fcallexpnode(char *id, explist args);
explist explistnode(expr e, explist exps);
stm declstmnode(decl d);
stm expstmnode(expr e);
stm ifstmnode(expr e, stmlist ifstms, stmlist elsestms);
stm whilestmnode(expr e, stmlist stms);
stm returnstmnode(expr e);
stmlist stmlistnode(stm s, stmlist stms);
arglist arglistnode(arg a, arglist args);
arg argnode(char *id, type t);
idlist idlistnode(char *id, idlist ids);
type typenode(char *id);
#endif