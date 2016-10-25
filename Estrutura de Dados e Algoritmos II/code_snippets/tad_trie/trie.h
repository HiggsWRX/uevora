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

trie *nova();
void insere(trie *t, char *chave);
void lista_ord(trie *t, char *cadeia, int n);
void min(trie *t, char *cadeia);
void max(trie *t, char *cadeia);
void remove_simples(trie *t, char *chave);
int remove_completo(trie *t, char *chave);
int existe(trie *t, char *cadeia);
int proxima(trie *t, char *cadeia);
