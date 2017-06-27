#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "apt.h"

void printnodes(node r, int l)
{
    switch (r->kind) {
        case var:
            printf("%s", r->u.v);
            break;
        case abstr:
            if(l == 0) {
                printf("(");
            }
            l++;
            printf("!");
            printnodes(r->u.nodestruct.n1, l);
            printf(".");
            printnodes(r->u.nodestruct.n2, l);
            l--;
            if(l == 0) {
                printf(")");
            }
            break;
        case aplic:
            printnodes(r->u.nodestruct.n1, l);
            printf(" ");
            printnodes(r->u.nodestruct.n2, l);
            break;
    }
}

node aplicnode(node n1, node n2)
{
    node ret = malloc(sizeof(*ret));

    ret->kind = aplic;
    ret->u.nodestruct.n1 = n1;
    ret->u.nodestruct.n2 = n2;

    return ret;
}

node absnode(node n1, node n2)
{
    node ret = malloc(sizeof(*ret));

    ret->kind = abstr;
    ret->u.nodestruct.n1 = n1;
    if (n2) {
        ret->u.nodestruct.n2 = n2;
    }

    return ret;
}

node varnode(char *v)
{
    node ret = malloc(sizeof(*ret));
    ret->kind = var;
    ret->u.v = v;

    return ret;
}

node pairnode(node n1, node n2)
{
    node t = n1;
    while (t->u.nodestruct.n2) {
        t = t->u.nodestruct.n2;
    }
    t->u.nodestruct.n2 = n2;

    return n1;
}