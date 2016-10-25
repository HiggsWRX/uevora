/*
 * tad_fila.h  -  API do Tipo Abstracto de Dados _fila_.
 *
 *                Uma fila contém números inteiros positivos.
 */


/* Tipos base */

struct lista {
  int val;
  struct lista *prox;
};

struct fila {
  struct lista *cabeca;
  struct lista *cauda;
};


/* Assinatura das funções (públicas) */

struct fila *fila_nova();
int   fila_vazia(struct fila *f);
void  fila_insere(struct fila *q, int v);
int   fila_remove(struct fila *q);
void fila_mostra(struct fila *f);
void fila_insere_apos(struct fila *f, int v1, int v);
void fila_insere_antes(struct fila *f, int v1, int v);
int fila_nesimo(struct fila *f, int n);
int fila_apaga(struct fila *f, int v);