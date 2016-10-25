#define Maxel 'z'
#define Minel 'a'
#define Nel (Maxel - Minel + 1)

/* nomear tipos*/

typedef struct trie trie;

/* definir tipos*/

struct trie {
    int existe;
    trie *prox[Nel];
};


/* assinatura funcoes*/

trie *nova_trie();
void insere_trie(trie *t, char *chave);
void lista_ord_trie(trie *t, char *cadeia, int n);
void min_trie(trie *t, char *cadeia);
void max_trie(trie *t, char *cadeia);
void remove_simples_trie(trie *t, char *chave);
int remove_completo_trie(trie *t, char *chave);
int existe_trie(trie *t, char *cadeia);

