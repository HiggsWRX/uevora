#include <stdio.h>
#include <stdlib.h>
#include "tad_fila.h"

/* nova_fila() - devolve uma nova fila */
struct fila *fila_nova()
{
    struct fila *f = (struct fila *) malloc(sizeof(struct fila));
  
    f->cabeca = f->cauda = NULL;
    return f;
}

/* fila_vazia(f) - testa se a fila f está vazia */
int fila_vazia(struct fila *f)
{
    return(f->cabeca==NULL);
}

/* fila_insere(f, v) - insere o valor v no fim da fila f */
void fila_insere(struct fila *f, int v)
{
    struct lista *l = (struct lista *) malloc(sizeof(struct lista));
  
    l->val   = v;
    l->prox  = NULL;
  
    if (fila_vazia(f)) {
        f->cabeca = f->cauda = l;
    }
    else {
        f->cauda->prox = l;
        f->cauda       = l;
    }
}

/* fila_remove(f) - remove o valor no início da fila f e devolve-o */
int fila_remove(struct fila *f)
{
    if(!fila_vazia(f)) {
        struct lista *cabeca = f->cabeca;
        int vcabeca          = f->cabeca->val;
    
        f->cabeca=f->cabeca->prox;
        free(cabeca);
    
        return(vcabeca);
    }
    else { /* fila vazia */
        return(-1); /* assumimos que os valores da fila são sempre positivos */
    }
}

/* mostra o conteúdo da fila f */
void fila_mostra(struct fila *f)
{
    struct lista *aux = f->cabeca;
    while (aux != NULL)
    {
        printf("%d\n", aux->val);
        aux = aux->prox;
    }
}

/* insere v na fila f, após v1 */
void fila_insere_apos(struct fila *f, int v1, int v)
{
    struct lista *aux = f->cabeca;
    struct lista *l = (struct lista *) malloc(sizeof(struct lista));
    l->val = v;

    if (!fila_vazia(f))
    {
        while (aux->val != v1 && aux->prox != NULL)
        {
            aux = aux->prox;
        }
        l->prox = aux->prox;
        aux->prox = l;
        if (l->prox == NULL)
        {
            f->cauda = l;
        }
    }
}

/* insere v na fila f, antes de v1 */
void fila_insere_antes(struct fila *f, int v1, int v)
{
    struct lista *aux = f->cabeca;
    struct lista *l = (struct lista *) malloc(sizeof(struct lista));
    l->val = v;

    if (!fila_vazia(f)) {
        if (aux->val == v1) {
            l->prox = f->cabeca;
            f->cabeca = l;
        } else {
            while (aux->prox->val != v1 && aux->prox->prox != NULL) {
                aux = aux->prox;
            }
            l->prox = aux->prox;
            aux->prox = l;
        }
    }
}

/* devolve o n-ésimo valor da fila f */
int fila_nesimo(struct fila *f, int n)
{
    struct lista *aux = f->cabeca;
    int i;
    for (i = 0; i < n; ++i)
    {
        if (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        else {
            return -1;
        }
    }
    return aux->val;
}

/* apaga o valor v da fila f. devolve 0 se v não estava na fila, 1 em caso de sucesso */
int fila_apaga(struct fila *f, int v)
{
    struct lista *aux = f->cabeca;

    if (!fila_vazia(f)) {
        if (aux->val == v) {
            f->cabeca = f->cabeca->prox;
            free(aux);
            return 1;
        } else {
            while (aux->prox != NULL && aux->prox->val != v) {
                aux = aux->prox;
            }
            if (aux->prox != NULL)
            {
                struct lista *tmp = aux->prox;
                aux->prox = aux->prox->prox;
                free(tmp);
                if (aux->prox == NULL)
                {
                    f->cauda = aux;
                }
                return 1;
            } else {
                return 0;
            }
        }
    }
}