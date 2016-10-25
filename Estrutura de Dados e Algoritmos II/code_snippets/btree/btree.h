#define ordem 3
#define maxfilhos 2*ordem 
#define maxchaves 2*ordem-1 

/* nomear tipos*/

typedef struct btree btree;

/* definir tipos*/

struct btree {
    int folha;  
    int n;
    //int numfilho;
    char *chave[maxchaves];
    struct btree *filho[maxfilhos];
    //struct btree *pai;
};


/* assinatura funcoes*/

void nova_btree(btree **t);
void insere_btree(btree **t, char *k);
void insere_btree_n_cheia(btree *t, char *k);
void lista_btree(btree *t, int b);
void parte_btree(btree *t, int i);
int search_btree(btree *t, char *k);
char *min_btree(btree *t);
void btree_remove(btree **t, char *k);
void btree_remove_safe(btree *t, char *k);
void btree_destroy(btree **temp);

/*
void btree_remove(btree **t, char *k);
btree *search_node(btree *t, char *k);
*/