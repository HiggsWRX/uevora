#ifndef _ll_h
#define _ll_h
#include "apt.h"

typedef struct listnode {
    char *val;
    struct listnode *next;
} listnode;

listnode *new_list();
void add(listnode **head, char *val);
void del(listnode **head, char *val);
void *getelement(listnode *head, int n);
void print(listnode *head);
void join(listnode **l1, listnode *l2, listnode *l3);
int contains(listnode *head, char *v);
#endif