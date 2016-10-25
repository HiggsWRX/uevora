#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

void nova_btree(btree **t)
{
    int i;
    *t = malloc(sizeof(**t));
    (*t)->folha = 1;
    (*t)->n = 0;
    for (i = 0; i < maxfilhos; i++) {
        (*t)->filho[i] = NULL;
    }
    for (i = 0; i < maxchaves; i++) {
        (*t)->chave[i] = NULL;
    }
}

void insere_btree(btree **t, char *k)
{
    if ((*t)->n == 2 * ordem - 1) { /*parte nó*/
        struct btree *x;
        nova_btree(&x);
        x->filho[0] = *t;
        *t = x;
        x->folha = 0;
        parte_btree(x, 0);
    }

    insere_btree_n_cheia(*t, k);
}


void insere_btree_n_cheia(btree *t, char *k)
{
    int i, j;
    if (t->folha) { /*insere no local adequado*/
        for (i = 0; ((i < t->n) && (strcmp(t->chave[i], k) < 0)); i++);
        
        for (j = t->n; j > i; j--) {
            t->chave[j] = t->chave[j - 1];
        }

        t->chave[i] = strdup(k);
        t->n = t->n + 1;
    }
    else {
        for (i = 0; (i < t->n) && (strcmp(t->chave[i], k) < 0); i++);

        /* t->filho[i]; ou le do disco*/
        if (t->filho[i]->n == 2 * ordem -1) /*se está cheia*/
        {
           parte_btree(t, i);
           insere_btree_n_cheia(t, k);
        }
        else { 
           insere_btree_n_cheia(t->filho[i], k);
        }
    }
}
        
void parte_btree(btree *t, int i)
{
    int j; 
    btree *z= malloc(sizeof(*t));

    z->folha = t->filho[i]->folha;
    z->n = t->filho[i]->n = ordem - 1;
    /*copia chaves de filho i para novo*/
    for (j = 0;j < ordem - 1 ; j++) {
        z->chave[j] = t->filho[i]->chave[ordem + j];
        t->filho[i]->chave[ordem + j] = NULL;
    }


    if (!z->folha) {
        for (j = 0; j < ordem ; j++) {
            z->filho[j]=t->filho[i]->filho[ordem+j];
        }
    }
    for (j = t->n; j > i; j--) {
        t->chave[j]=t->chave[j-1];
    }
    for (j = t->n; j > i; j--) {
        t->filho[j + 1] = t->filho[j];
    }
    
    t->chave[i] = t->filho[i]->chave[ordem - 1];
    t->filho[i]->chave[ordem - 1] = NULL;
    t->filho[i + 1] = z;
    t->n = t->n + 1;
}

void lista_btree(btree *t, int b)
{
    int i, j;

    if(!(t->folha)) {
        for (i = t->n; i >= 0; i--) {
            lista_btree(t->filho[i], b + 3);
        } 
    }
    for (i = t->n - 1; i >= 0; i--) {
        for (j = 0; j < b; j++) {
            printf(" ");
        }
        printf("|%s|\n", t->chave[i]);
    }
    printf("\n");
}

char *min_btree(btree *t)
{
    if(!(t->folha)) {
        min_btree(t->filho[0]); 
    } else {
        return t->chave[0];
    }
}

int search_btree(btree *t, char *k)
{
    int i;

    for (i = 0; i <= (t->n - 1); i++) {
        if (strcmp(t->chave[i], k) == 0) {
            return 1;
        }
        if (strcmp(t->chave[i], k) > 0) {
            if (t->folha) {
                return 0;
            }
            return search_btree(t->filho[i], k);
        }
    }
    if (!t->folha) {
        return search_btree(t->filho[i], k);
    } else {
        return 0;
    }
}

char *btree_remove_max(btree *t)
{
    char *s = t->chave[t->n-1];
    t->chave[t->n - 1] = NULL;
    t->n = t->n - 1;
    return s;
}

char *btree_remove_min(btree *t)
{
    int i;
    char *s = t->chave[0];
    for (i = 0; i < t->n - 1; i++) {
        t->chave[i] = t->chave[i + 1];
    }
    t->chave[t->n - 1] = NULL;
    t->n = t->n - 1;
    return s;
}

void btree_borrow_left(btree *t, int i)
{
    int j;
    btree *y = t->filho[i];                 // irmao esquerdo do no i
    btree *z = t->filho[i - 1];             // -> i - 1

    for (j = ordem - 1; j >= 0; j--) {      // arranjar espaco para nova chave
        y->chave[j + 1] = y->chave[j];
    }

    y->chave[0] = t->chave[i - 1];
    t->chave[i - 1] = z->chave[z->n - 1];

    if (!y->folha) {
        for (j = ordem; j >= 0; j--) {      // arranjar espaco para novo filho
            y->filho[j + 1] = y->filho[j];
        }
        y->filho[0] = z->filho[z->n];
    }
    y->n = ordem;
    z->n = z->n - 1;
}

void btree_borrow_right(btree *t, int i)
{
    int j;
    btree *y = t->filho[i];
    btree *z = t->filho[i + 1];

    for (j = ordem - 1; j >= 0; j--) {
        y->chave[j + 1] = y->chave[j];
    }

    y->chave[0] = t->chave[i - 1];
    t->chave[i - 1] = z->chave[z->n];

    if (!y->folha) {
        for (j = ordem; j >= 0; j--) {
            y->chave[j + 1] = y->chave[j];
        }
        y->chave[0] = z->chave[z->n + 1];
    }
    y->n = ordem;
    z->n = z->n - 1;
}

void btree_merge_children(btree *t, int i)
{
    int j;
    btree *y = t->filho[i];
    btree *z = t->filho[i + 1];
    
    y->chave[ordem - 1] = t->chave[i];
    
    for (j = 0; j < ordem - 1; j++) {              // filho[i + 1]
        y->chave[ordem + j] = z->chave[j];          // para filho[i]
    }

    if (!y->folha) {
        for (j = 0; j <= ordem; j++) {
            y->filho[ordem + j] = z->filho[j];
        }
    }

    y->n = maxchaves;

    for (j = i; j < t->n; j++) {
        t->chave[j] = t->chave[j + 1];
    }
    for (j = i + 1; j < t->n; j++) {
        t->filho[j] = t->filho[j + 1];
    }

    t->n = t->n - 1;
    free(z);

}

void btree_remove(btree **t, char *k)
{
    btree *r = *t;
    btree_remove_safe(r, k);
    if (r->n == 0 && !(r->folha)) {
        r = r->filho[0];
        free((*t));
        *t = r;
    }
}

void btree_remove_safe(btree *t, char *k)
{
    btree *y;
    btree *z;
    int j;
    int m = 0;
    int borrowed = 0;
    int i = 0;
    while (i < t->n && strcmp(k, t->chave[i]) >= 1) {
        i++;
    }

    if (i < t->n && strcmp(t->chave[i], k) == 0) {
        if (t->folha) {                                 //
            for (j = i; j <= t->n - 1; j++) {           //
                t->chave[j] = t->chave[j + 1];          // caso 1
            }                                           //
            t->n = t->n - 1;
        } else {
            y = t->filho[i];
            if (y->n > ordem - 1) {                     // caso 2a
                t->chave[i] = btree_remove_max(y);      //
            } else {
                z = t->filho[i + 1];                    //
                if (z->n > ordem - 1) {                 // caso 2b
                    t->chave[i] = btree_remove_min(z);  //
                } else {
                    btree_merge_children(t, i);         // caso 2c
                    btree_remove_safe(y, k);            //
                }
            }
        }
    } else if (!t->folha) {
        y = t->filho[i];
        if (y->n == ordem - 1) {
            borrowed = 0;
            if (i > 1) {
                z = t->filho[i - 1];                    //
                if (z->n > ordem - 1) {                 // caso 3a
                    btree_borrow_left(t, i);            //
                    borrowed = 1;
                } else {
                    m = i - 1;
                }
            }
            if (!borrowed && i < t->n) {
                z = t->filho[i + 1];                    //
                if (z->n > ordem - 1) {                 // caso 3a
                    btree_borrow_right(t, i);           //
                    borrowed = 1;
                } else {
                    m = i;
                }
            }
            if (!borrowed) {                            //
                btree_merge_children(t, m);             // caso 3b
                y = t->filho[m];                        //
            }
        }
        btree_remove_safe(y, k);
    }
}

void btree_destroy(btree **temp)
{
    btree *t = *temp;
    int i;

    if (!(t->folha)) {
        for (i = 0; i < maxfilhos - 1; i++) {
            if (t->filho[i]) {
                btree_destroy(&(t->filho[i]));
            }
        }
    }

    for (i = 0; i < maxchaves - 1; i++) {
        if (t->chave[i]) {
            t->chave[i] = 0;
        }
    }

    free(t);
}