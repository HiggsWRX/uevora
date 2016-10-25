#include <stdlib.h>
#include <string.h>
#include "hashtable.h"


int getindex(char *word)
{
    int hash_val = 0;

    for(int i = 0; i < strlen(word); i++) {
        hash_val = 37 * hash_val + word[i];
    }

    hash_val = hash_val % SIZE;

    if (hash_val < 0) {
        hash_val += SIZE;
    }
    
    return hash_val;
}

void insert(hash *ht, char *word, type val)
{
    int i;
    node *n = malloc(sizeof(node));
    n->key = word;
    n->value[0] = val;
    i = getindex(n->key);
    ht->tab[i] = n;
}

type getval(hash *ht, char *word)
{
    int i;
    type ret;
    i = getindex(word);
    if (ht->tab[i]) {
        ret = (ht->tab[i])->value[0];
    } else {
        ret = NULL;
    }
    return ret;
}

type *getvalues(hash *ht, char *word)
{
    int i;
    type *ret;
    i = getindex(word);
    if (ht->tab[i]) {
        ret = ht->tab[i]->value;
    } else {
        ret = NULL;
    }
    return ret;
}

void inithash(hash **ht)
{
    *ht = malloc(sizeof(hash));
    for(int i = 0; i < SIZE; i++) {
        (*ht)->tab[i] = NULL;
    }
}