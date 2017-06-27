#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reductions.h"

listnode *freevars;
listnode *usedvars;

void analiseapt(node n)
{
    node n2;
    freevars = new_list();
    usedvars = new_list();
    printf("<- ");
    printnodes(n, 0);
    printf("\n");
    freevars = varslivres(&n);
    n = *eval(&n);
    n2 = *eval(&n);
    while (n != n2) {
        n = *eval(&n);
        n2 = *eval(&n);
    }
    printf("-> ");
    printnodes(n2, 0);
    printf("\n");
}

static listnode *varslivres(node *r)
{
    listnode *vars;
    listnode *temp1;
    listnode *temp2;
    switch ((*r)->kind) {
        case var:
            vars = new_list();
            add(&vars, (*r)->u.v);
            break;
        case aplic:
            vars = new_list();
            temp1 = varslivres(&(*r)->u.nodestruct.n1);
            temp2 = varslivres(&(*r)->u.nodestruct.n2);
            join(&vars, temp1, temp2);
            break;
        case abstr:
            vars = varslivres(&(*r)->u.nodestruct.n2);
            del(&vars, (*r)->u.nodestruct.n1->u.v);
            break;
    }

    return vars;
}

void alfasubs(node *r)
{
    if (*r) {
        switch ((*r)->kind) {
            case abstr:
                r = alfa(r);
                alfasubs(&(*r)->u.nodestruct.n2);
                break;
            case aplic:
                alfasubs(&(*r)->u.nodestruct.n1);
                alfasubs(&(*r)->u.nodestruct.n2);
                break;
        }
    }

    return;
}

node *alfa(node *r)
{   
    listnode *vars = varslivres(&(*r)->u.nodestruct.n2);
    char *v;
    char t;
    v = strdup((*r)->u.nodestruct.n1->u.v);
    while (strcmp(v, (*r)->u.nodestruct.n1->u.v) == 0 || contains(vars, v)|| contains(freevars, v) || contains(usedvars, v)) {
        t = *v;
        if (t == 'z')
            v[0] = 'a';
        else
            v[0] = (char)(((int) t) +1);
    }

    add(&usedvars, v);
    
    node temp = varnode(v);
    node *temp2 = subs(&((*r)->u.nodestruct.n2), &((*r)->u.nodestruct.n1), &temp);

    (*r)->u.nodestruct.n1 = temp;
    (*r)->u.nodestruct.n2 = *temp2;

    return r;
}

node *beta(node *r)
{
    node *esq = &(*r)->u.nodestruct.n1;
    if ((*esq)->kind == var || (*esq)->kind == aplic) {
        return r;
    } else if ((*esq)->kind == abstr) {
        node *ret = subs(&(*esq)->u.nodestruct.n2, &(*esq)->u.nodestruct.n1, &(*r)->u.nodestruct.n2);
        return ret;
    }

    return r;
}

node *eval(node *r)
{
    if (r != NULL) {
        switch ((*r)->kind) {
            case var:
                return r;
            case abstr:
                (*r)->u.nodestruct.n2 = *eval(&(*r)->u.nodestruct.n2);
                return r;
            case aplic:
                (*r)->u.nodestruct.n1 = *eval(&(*r)->u.nodestruct.n1);
                (*r)->u.nodestruct.n2 = *eval(&(*r)->u.nodestruct.n2);
                return beta(r);
            default:
                printf("?????");
        }
    }

    return r;
}

node *subs(node *root, node *n1, node *n2)
{
    char *n = NULL;
    node *temp = NULL;
    switch ((*root)->kind) {
        case var:
            if (strcmp((*root)->u.v, (*n1)->u.v) == 0)
                return n2;
            else
                return root;
        case aplic:
            temp = subs(&(*root)->u.nodestruct.n1, n1, n2);
            (*root)->u.nodestruct.n1 = *temp;
            temp = subs(&(*root)->u.nodestruct.n2, n1, n2);
            (*root)->u.nodestruct.n2 = *temp;
            return root;
        case abstr:
            n = (*root)->u.nodestruct.n1->u.v;
            if (strcmp(n, (*n1)->u.v) != 0) {
                listnode *vars = varslivres(n2);
                while (contains(vars, n)) {
                    root = alfa(root);
                    n = (*root)->u.nodestruct.n1->u.v;
                }
                temp = subs(&(*root)->u.nodestruct.n2, n1, n2);
                (*root)->u.nodestruct.n2 = *temp;
            }
            return root;
    }

    return root;
}
