#ifndef _structs_h
#define _structs_h

typedef struct FreqNode
{
    char *sym;
    char huffcode;
    int numbits;
    int freq;
    struct FreqNode *left, *right;
} FreqNode;

typedef struct Bitarray
{
    int bit;
    struct Bitarray *next;
} Bitarray;

typedef struct NodeLList
{
    FreqNode *val;
    struct NodeLList *next;
} NodeLList;

typedef struct Stack
{
    char v;
    struct Stack *next;
} Stack;

NodeLList *newlist();
void addstart(NodeLList **head, FreqNode *val);
void addend(NodeLList **head, FreqNode *val);
void insertorder(NodeLList **head, FreqNode *val);
FreqNode *removefirst(NodeLList **head);
FreqNode *removelast(NodeLList **head);
FreqNode *getelement(NodeLList *head, int n);
NodeLList *copylist(NodeLList *head);
void clearlist(NodeLList **head);

FreqNode *newfreqnode();
void inserttree(FreqNode **tree, FreqNode *item);
FreqNode *search(FreqNode **tree, char *s);
void destroytree(FreqNode *tree);
int isleaf(FreqNode *root);
int countbits(FreqNode *root);

void generatehuffcodes(FreqNode **root, Stack **s, int depth);
void getcodeinfo(FreqNode *root, char *s, char *d, int *n);
void encodefile(FreqNode *root, char *alltext, FILE *f);

Stack *newstack();
void push(Stack **s, char v);
char pop(Stack **s);
char top(Stack *s);

char *substr(char *s, int x, int y);
char *concat(char *s1, char*s2);
FreqNode *huffman(NodeLList **txtfreqs, int n);

Bitarray *newbitarray();
void addendbit(Bitarray **head, int bit);
void decodefile(FILE *f, FreqNode *root, FreqNode *current, Bitarray *b);
int getbit(char c, int k);
#endif