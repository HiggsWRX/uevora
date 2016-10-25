#define maxv 20;

/* nomear tipos*/
typedef struct fila fila;
typedef struct lista lista;

/* definir tipos*/
struct fila {
    lista *cabeca, *cauda;
};

struct lista{
    struct vertice *v;
    int d;
    struct lista *prox;
};

enum Cor {
    branco,
    cinzento,
    preto
};

struct vertice {
    enum Cor cor;
    int distancia;
    int v;
    struct vertice *pai;
    struct lista *adj;
};

struct Arcos {
    int u;
    int v;
    int d;
};

/* assinatura funcoes*/
fila *nova_fila();
int fila_vazia(fila *f);
void insere_fila(fila *q, struct vertice *v);
struct vertice *remove_fila(fila *q);
struct lista *insere(struct lista *l, struct vertice *v, int d);
struct lista *nova_lista();
struct lista * next(struct lista * curr);
void cria_grafo(struct vertice *g, int nvertices, int narcos, struct Arcos *arcos);
void lista_grafo(struct vertice *g, int nvertices);
void bfs(struct vertice *g, struct vertice *s, int nvertices);
void distancias(struct vertice *g, struct vertice *s,int nvertices);


void caminho3(struct vertice *g, int s,int u, int v, int nvertices);
void melhor_caminho(struct vertice *g,struct vertice *s,struct vertice *u,int nvertices);