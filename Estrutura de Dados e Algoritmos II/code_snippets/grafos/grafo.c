#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

fila *nova_fila()
{
    fila *f = (fila *) malloc(sizeof(fila));
    f->cabeca = f->cauda = NULL;
    return f;
}

/* fila vazia*/

int fila_vazia(fila *f)
{
    return(f->cabeca == NULL);
}

/* função insere*/

void insere_fila(fila *f, struct vertice *v)
{
    lista *l = (lista *) malloc(sizeof(lista));
    l->v = v;
    l->prox= NULL;
    if (fila_vazia(f)) {
        f->cabeca = f->cauda = l;
    } else {
        (f->cauda)->prox =l;
        f->cauda =l;
    }
}

/*função remove*/

struct vertice *remove_fila(fila *f)
{
    if(!fila_vazia(f)){
        lista *cabeca = f->cabeca;
        struct vertice *vcabeca = (f->cabeca)->v;
        f->cabeca = f->cabeca->prox;
        free(cabeca);
        return(vcabeca);
    }
    return(NULL);
}



struct lista *insere(struct lista *l, struct vertice *v, int d)
{
    struct lista *x = l;
    l = (struct lista *) malloc(sizeof (struct lista));
    l->prox = x;
    l->v = v;
    l->d = d;
    return(l);
}

struct lista *nova_lista()
{
    struct lista *l = (struct lista *) malloc (sizeof(struct lista));
    l->prox = NULL;
    return(l);
}

struct lista *next(struct lista *curr)
{
    return(curr->prox);
}


void cria_grafo(struct vertice *g, int nvertices, int narcos, struct Arcos *arcos)
{
    int i;

    for (i = 0; i < nvertices; i++) {
        g[i].v = i;
        g[i].adj = NULL;
    }
    for(i = 0; i < narcos; i++) {
        g[arcos[i].u - 1].adj = insere(g[arcos[i].u - 1].adj, g + arcos[i].v - 1, arcos[i].d);
    }
}


void lista_grafo(struct vertice *g, int nvertices)
{
    int i;
    struct lista *adj;
    for (i = 0; i < nvertices; i++) {
        printf("vertice %d\n", i + 1);
        adj = g[i].adj;
        while (adj){
            printf("        ligado a %d com custo %d\n", (adj->v)->v + 1,adj->d);
            adj = next(adj);
        }
    }
 }


void bfs(struct vertice *g, struct vertice *s, int nvertices)
{
    int i;
    fila *q = nova_fila();
    struct vertice *v, *u;
    struct lista *adj;
 
    for(i = 0; i < nvertices; i++) {
        g[i].cor = branco;
        g[i].distancia = 1000;
        g[i].pai = NULL;
    }

    s->cor = cinzento;
    s->distancia = 0; 

    insere_fila(q,s);


    while (!fila_vazia(q)) {
        u = remove_fila(q);
        adj = u->adj;
        while (adj) {
            v = adj->v;
            if (v->cor == branco) {
                v->cor = cinzento;
                v->distancia = u->distancia + 1;
                v->pai = u;
                insere_fila(q,v);
            }
            adj = next(adj);
        }
        u->cor = preto;
    }
}



void distancias(struct vertice *g, struct vertice *s,int nvertices)
{
    int i;
    struct vertice *u;
    for (i = 0; i < nvertices; i++){
        u = g + i;
        if (u->pai) {
        printf("no - %d - dist de %d: %d \n", u->v + 1, s->v + 1,  u->distancia);
        }
    }
}