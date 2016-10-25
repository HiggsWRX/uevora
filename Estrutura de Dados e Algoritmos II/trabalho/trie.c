#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

trie *nova_trie()
{
    int i;
    trie *temp = malloc(sizeof(trie));
    temp->existe = 0;
    for(i = 0; i < Nel; i++) {
        temp->prox[i] = NULL;
    }

    return temp;
}

void insere_trie(trie *t, char *chave)
{
    if (*chave == 0) {
        t->existe = 1;
    }
    else {
        if (t->prox[*chave - Minel] == NULL) {
            t->prox[*chave - Minel] = nova_trie();
        }
        insere_trie(t->prox[*chave-Minel], chave + 1);
    }
}

int existe_trie(trie *t, char *cadeia)
{
    if (*cadeia == 0) {
        return (t->existe);
    }
    else {
        if (t->prox[*cadeia - Minel] == NULL) {
            return 0;
        }
        else {
            return (existe_trie(t->prox[*cadeia - Minel], cadeia + 1));
        }
    }
}

void lista_ord_trie(trie *t, char *cadeia, int n)
{
    int j;

    if (t->existe) { *cadeia = 0; printf("%s\n", cadeia-n); }

    for (j = 0; j < Nel; j++)
    {
        if (t->prox[j] != NULL) {
            *cadeia = j + Minel;
            lista_ord_trie(t->prox[j], cadeia + 1, n + 1);
        }
    }
}

void min_trie(trie *t, char *cadeia)
{
    int j;

    if (t->existe) { *cadeia = 0; return; }

    for (j = 0; j < Nel; j++) {
        if (t->prox[j] != NULL) {
            *cadeia = j + Minel;
            min_trie(t->prox[j], cadeia + 1);
            return;
        }
    }

    *cadeia = '\0';
    return;
}

void max_trie(trie *t, char *cadeia)
{
    int j;

    for (j = Nel-1; j >= 0; j--)
    {
        if (t->prox[j] != NULL) {
            *cadeia = j + Minel;
            max_trie(t->prox[j], cadeia + 1);
            return;
        }
    }
    
    if (t->existe) { *cadeia = 0; return; }
}

void remove_simples_trie(trie *t, char *chave)
{
    if (*chave == 0) {
        t->existe = 0;
    } else {
        if (t->prox[*chave - Minel] == NULL) {
            return;
        }
        else {
            remove_simples_trie(t->prox[*chave - Minel], chave + 1);
        }
    }
}

int remove_completo_trie(trie *t, char *chave)
{
    if (*chave == 0) {
        int c;
        t->existe = 0;
        for (c = 0; c < Nel; c++)
        {
            if (t->prox[c])
            {
                return 0;
            }
        }
        return 1;
    } else {
        if (t->prox[*chave - Minel] == NULL) {
            return 0;
        } else {
            int i;
            i = remove_completo_trie(t->prox[*chave - Minel], chave + 1);
            if (i) {
                free(t->prox[*chave - Minel]);
                t->prox[*chave - Minel] = NULL;
                for (i = 0; i < Nel; ++i) {
                    if (t->prox[i]) {
                        return 0;
                    }
                }
                return (!t->existe);
            } else {
                return 0;
            }
            
        }
    }
}