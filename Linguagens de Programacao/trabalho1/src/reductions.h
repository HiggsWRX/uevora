#ifndef _reductions_h
#define _reductions_h
#include "apt.h"
#include "ll.h"

static listnode *varslivres(node *r);
void analiseapt(node n);
node *alfa(node *r);
node *subs(node *root, node *n1, node *n2);
void alfasubs(node *r);
#endif