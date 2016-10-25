#ifndef _hashtable_h
#define _hashtable_h
#include <stdio.h>
#include <stdlib.h>
#include "apt.h"

#define SIZE 113

typedef struct node {
    char *key;
    type value[32];
} node;

typedef struct hash {
    int size;
    node *tab[SIZE];
} hash;

int getindex(char *word);
void insert(hash *ht, char *word, type val);
type getval(hash *ht, char *word);
type *getvalues(hash *ht, char *word);
void inithash(hash **ht);

#endif