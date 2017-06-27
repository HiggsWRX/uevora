#ifndef _apt_h
#define _apt_h
#include "ll.h"

typedef struct node_ *node;

struct node_ {
    enum {
        var,
        abstr,
        aplic
    } kind;
    union {
        char *v;
        struct {
            node n1;
            node n2;
        } nodestruct;
    } u;
};

node varnode(char *v);
node aplicnode(node n1, node n2);
node absnode(node n1, node n2);
node pairnode(node n1, node n2);
void analiseapt(node n);
void printnodes(node r, int l);
#endif