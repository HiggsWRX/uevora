#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "structs.h"

NodeLList *newlist()
{
    NodeLList *head = malloc(sizeof(NodeLList));
    head->val = NULL;
    head->next = NULL;

    return head;
}

void addstart(NodeLList **head, FreqNode *val)
{
    if ((*head)->val) {
        NodeLList *newnode = malloc(sizeof(NodeLList));
        newnode->val = val;
        newnode->next = *head;
        *head = newnode;
    } else {
        (*head)->val = val;
    }
}

void addend(NodeLList **head, FreqNode *val)
{
    NodeLList *current = *head;

    if ((*head)->val) {
        while (current->next) {
            current = current->next;
        }
        current->next = malloc(sizeof(NodeLList));
        current->next->val = val;
        current->next->next = NULL;
    } else {
        (*head)->val = val;
    }
}

void addendbit(Bitarray **head, int bit)
{
    Bitarray *current = *head;

    if ((*head)->bit != -1) {
        while (current->next) {
            current = current->next;
        }
        current->next = malloc(sizeof(NodeLList));
        current->next->bit = bit;
        current->next->next = NULL;
    } else {
        (*head)->bit = bit;
    }
}

void insertorder(NodeLList **head, FreqNode *val)
{
    NodeLList *new;
    NodeLList *current = *head;
    NodeLList *previous = NULL;

    if (!(*head)->val) {
        (*head)->val = val;
        return;
    }

    if (current) {
        while (current) {
            if (current->val->freq < val->freq) {
                if (previous) {
                    new = malloc(sizeof(NodeLList));
                    new->val = val;
                    previous->next = new;
                    new->next = current;
                    return;
                } else {
                    new = malloc(sizeof(NodeLList));
                    new->val = val;
                    new->next = *head;
                    *head = new;
                    return;
                }
            }
            previous = current;
            current = current->next;
        }
    } else {
        current = newlist();
        current->val = val;
    }

    new = malloc(sizeof(NodeLList));
    new->val = val;
    previous->next = new;

    return;
}

FreqNode *removefirst(NodeLList **head)
{
    NodeLList *nextnode = NULL;
    FreqNode *retval;

    if ((*head)->next) {
        nextnode = (*head)->next;
        retval = (*head)->val;
        free(*head);
        *head = nextnode;
    } else {
        if ((*head)->val) {
            retval = (*head)->val;
            (*head)->val = NULL;
        } else {
            printf("Warning: Removing from empty list. Returning NULL.\n");
            retval = NULL;
        }
    }

    return retval;
}

FreqNode *removelast(NodeLList **head)
{
    NodeLList *current = *head;
    NodeLList *previous;
    FreqNode *retval;

    if (current->val) {
        if (!current->next) {
            retval = current->val;
            current->val = NULL;
        } else {
            while (current->next) {
                previous = current;
                current = current->next;
            }

            retval = current->val;
            free(current);
            previous->next = NULL;
        }
    } else {
        printf("Warning: Removing from empty list. Returning NULL.\n");
        retval = NULL;
    }

    return retval;
}

NodeLList *copylist(NodeLList *head)
{
    NodeLList *ret;
    if (!head) {
        return NULL;
    }

    ret =  newlist();
    ret->val = head->val;
    ret->next = copylist(head->next);
    return ret;
}

void clearlist(NodeLList **head)
{
    NodeLList *current = *head;
    while (current->next) {
        current = current->next;
        free(*head);
        *head = current;
    }
    current->val = NULL;
}

FreqNode *newfreqnode()
{
    FreqNode *ret = malloc(sizeof(FreqNode));

    ret->sym = NULL;
    ret->huffcode = -1;
    ret->numbits = -1;
    ret->freq = -1;
    ret->left = NULL;
    ret->right = NULL;

    return ret;
}

void inserttree(FreqNode **tree, FreqNode *item)
{
    FreqNode *temp = NULL;
   if (!(*tree)) {
      temp = malloc(sizeof(FreqNode));
      temp->left = temp->right = NULL;
      temp->freq = item->freq;
      *tree = temp;
      return;
   }

   if (item->sym < (*tree)->sym) {
      inserttree(&(*tree)->left, item);
   } else if (item->sym > (*tree)->sym) {
      inserttree(&(*tree)->right, item);
   }
}

void destroytree(FreqNode *tree)
{
    if (tree) {
        destroytree(tree->left);
        destroytree(tree->right);
        free(tree);
    }
}

int isleaf(FreqNode *node)
{
    return !node->left && !node->right;
}

int countbits(FreqNode *root)
{
    int sum = 0;
    if (root->left) {
        sum += countbits(root->left);
    }
    if (root->right) {
        sum += countbits(root->right);
    }

    if (isleaf(root)) {
        sum += root->numbits * root->freq;
        return sum;
    }

    return sum;
}

void generatehuffcodes(FreqNode **root, Stack **s, int depth)
{
    char c;
    int currdepth = depth;
    if((*root)->left) {
        c = top(*s);
        c = c << 1;
        push(s, c);
        generatehuffcodes(&(*root)->left, s, ++depth);
        depth--;
    }
    if ((*root)->right) {
        c = top(*s);
        c = c << 1;
        c = c | (1 << 0);
        push(s, c);
        generatehuffcodes(&(*root)->right, s, ++depth);
        depth--;
    }
    c = pop(s);
    (*root)->huffcode = c;
    (*root)->numbits = currdepth;
}

void getcodeinfo(FreqNode *root, char *s, char *d, int *n)
{
    if (strcmp(root->sym, s) == 0) {
        *d = root->huffcode;
        *n = root->numbits;
    }
    if (root->left) {
        getcodeinfo(root->left, s, d, n);
    }
    if (root->right) {
        getcodeinfo(root->right, s, d, n);
    }
    
}

void encodefile(FreqNode *root, char *alltext, FILE *f)
{
    int numbits = countbits(root);
    int numbytesrequired = (int) ceil(numbits / 8.0);
    int unusedbits = (8 * numbytesrequired) - numbits;
    char bitarray[numbytesrequired];
    unsigned char sym;
    char auxchar;
    char str[2] = "\0";
    int i, j, b;
    int numsymbits;
    int currentbyte = 0;

    for (i = 0; i < numbytesrequired; i++) {
        bitarray[i] = 0;
    }

    b = 0;
    for (i = 0; i < strlen(alltext); i++) {
        str[0] = alltext[i];
        getcodeinfo(root, str, &sym, &numsymbits);
        for (j = 0; j < numsymbits; j++) {
            auxchar = sym;
            auxchar = auxchar >> (numsymbits - 1 - j);
            bitarray[currentbyte] = bitarray[currentbyte] << 1;
            bitarray[currentbyte] = bitarray[currentbyte] | auxchar;
            b++;
            if (b > 7) {
                currentbyte++;
                b = 0;
                sym = sym << 8 - numsymbits + (j + 1);
                sym = sym >> 8 - numsymbits + j + 1;
            }
        }
    }

    for (i = 0; i < unusedbits; i++) {
        bitarray[currentbyte] = bitarray[currentbyte] << 1;
    }

    for (i = 0; i < numbytesrequired; i++) {
        fputc(bitarray[i], f);
    }

    i = strlen(alltext) * 8; // t. inicial em bits
    printf("Original text size: %d bits --- Compressed text size: %d bits\n", i, numbits);
    printf("Ganho de compressão: %.2f%\n", (1.0 - (1.0 / ((strlen(alltext)*8.0)/numbits))) * 100);
}

Stack *newstack()
{
    Stack *ret = malloc(sizeof(Stack));

    ret->v = -1;
    ret->next = NULL;

    return ret;
}

void push(Stack **s, char v)
{
    if ((*s)->v != -1) {
        Stack *new = malloc(sizeof(Stack));
        new->v = v;
        new->next = *s;
        *s = new;
    } else {
        (*s)->v = v;
    }
}


char pop(Stack **s)
{
    char ret;
    Stack *t;
    if ((*s)->v != -1) {
        ret = (*s)->v;
        if ((*s)->next) {
            t = *s;
            *s = (*s)->next;
            free(t);
            return ret;
        } else {
            (*s)->v = -1;
        }
    } else {
        printf("Error: Popping from empty stack.\n");
        exit(1);
    }
}

char top(Stack *s)
{
    if (s->v != -1) {
        return s->v;
    } else {
        printf("Empty stack, no value on top.\n");
        return -1;
    }
}

char *substr(char *s, int x, int y)
{
    char *ret = malloc(strlen(s) + 1);

    if (ret) {
        char *p = ret;
        char *q = &s[x];
        while (x < y) {
            *p++ = *q++;
            x++;
        }
        *p++ = '\0';
    } else {
        printf("MALLOC ERROR.\n");
        exit(1);
    }

    return ret;
}

char *concat(char *s1, char*s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    if (result) {
        strcpy(result, s1);
        strcat(result, s2);
    } else {
        printf("MALLOC ERROR.\n");
        exit(1);
    }

    return result;
}

FreqNode *huffman(NodeLList **txtfreqs, int n)
{
    int i;
    NodeLList *Q = *txtfreqs;
    FreqNode *z;
    FreqNode *x;
    FreqNode *y;
    for (i = 0; i < n; i++) {
        z = newfreqnode();
        z->left = x = removelast(&Q);
        z->right = y = removelast(&Q);
        z->sym = concat(x->sym, y->sym);
        z->freq = x->freq + y->freq;
        insertorder(&Q, z);
    }

    return removelast(&Q);
}

Bitarray *newbitarray()
{
    Bitarray *ret = malloc(sizeof(Bitarray));

    ret->bit = -1;
    ret->next = NULL;

    return ret;
}

void decodefile(FILE *f, FreqNode *root, FreqNode *current, Bitarray *b)
{
    if (b) {
        if (isleaf(current)) {
            fputc(current->sym[0], f);
            decodefile(f, root, root, b);
        } else if (b->bit == 0 && current->left) {
            decodefile(f, root, current->left, b->next);
        } else if (b->bit == 1 && current->right) {
            decodefile(f, root, current->right, b->next);
        }
    } else if (isleaf(current)) {
        fputc(current->sym[0], f);
    }
}

int getbit(char c, int k)
{
    return (c & (1 << k )) >> k;
}