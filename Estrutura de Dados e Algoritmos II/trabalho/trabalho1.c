/* DEPENDENCIES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "btree.h"
#include "trie.h"

static struct timeval tm1;

static inline void start_clock()
{
    gettimeofday(&tm1, NULL);
}

unsigned long long stop_clock()
{
    struct timeval tm2;
    unsigned long long t;

    gettimeofday(&tm2, NULL);

    t = 1000 * (tm2.tv_sec - tm1.tv_sec) + (tm2.tv_usec - tm1.tv_usec) / 1000;

    return t;
}

void read_insert_trie(trie *tr, int LER_X)
{
    FILE *ficheiro_en;
    char *linha = NULL;
    size_t len = 0;
    ssize_t read;
    int counter;
    unsigned long long time;

    start_clock();
    ficheiro_en = fopen("words_en.txt", "r");
    if (ficheiro_en == NULL) {
        printf("File not found, exiting...\n");
        exit(EXIT_FAILURE);
    } else {
        counter = 0;
        while ((read = getline(&linha, &len, ficheiro_en)) != -1 && counter < LER_X) {
            counter++;
            insere_trie(tr, strtok(linha, "\n"));
        }
    }

    time = stop_clock();
    printf("%llu ms\n", time);
    free(linha);
    fclose(ficheiro_en);
}

void read_insert_btree(btree **bt, int LER_X)
{
    FILE *ficheiro_en;
    char *linha = NULL;
    size_t len = 0;
    ssize_t read;
    int counter;
    unsigned long long time;

    start_clock();
    ficheiro_en = fopen("words_en.txt", "r");
    if (ficheiro_en == NULL) {
        printf("File not found, exiting...\n");
        exit(EXIT_FAILURE);
    } else {
        counter = 0;
        while ((read = getline(&linha, &len, ficheiro_en)) != -1 && counter < LER_X) {
            counter++;
            insere_btree(bt, strtok(linha, "\n"));
        }
    }

    time = stop_clock();
    printf("%llu ms\n", time);
    free(linha);
    fclose(ficheiro_en);
}

void read_search_trie(trie *tr, int LER_Y)
{
    FILE *ficheiro_s;
    char *linha = NULL;
    size_t len = 0;
    ssize_t read;
    int counter;
    int found;
    unsigned long long time;

    start_clock();

    ficheiro_s = fopen("words_s.txt", "r");
    if (ficheiro_s == NULL) {
        printf("File not found, exiting\n");
        exit(EXIT_FAILURE);
    } else {
        counter = 0;
        found = 0;
        while ((read = getline(&linha, &len, ficheiro_s)) != 1 && counter < LER_Y) {
            counter++;
            if (existe_trie(tr, strtok(linha, "\n"))) {
                found++;
            }
        }
    }

    time = stop_clock();
    printf("%llu ms\n", time);
    printf("* Found %d words.\n", found);
    fclose(ficheiro_s);
    free(linha);
}

void read_search_btree(btree *bt, int LER_Y)
{
    FILE *ficheiro_s;
    char *linha = NULL;
    size_t len = 0;
    ssize_t read;
    int counter;
    int found;
    unsigned long long time;

    start_clock();

    ficheiro_s = fopen("words_s.txt", "r");
    if (ficheiro_s == NULL) {
        printf("File not found, exiting\n");
        exit(EXIT_FAILURE);
    } else {
        counter = 0;
        found = 0;
        while ((read = getline(&linha, &len, ficheiro_s)) != 1 && counter < LER_Y) {
            counter++;
            if (search_btree(bt, strtok(linha, "\n"))) {
                found++;
            }
        }
    }
    
    time = stop_clock();
    printf("%llu ms\n", time);
    printf("* Found %d words.\n", found);
    fclose(ficheiro_s);
    free(linha);
}

void read_remove_trie(trie *tr)
{
    char word[32];
    long time;

    start_clock();

    do {
        min_trie(tr, word);
        remove_completo_trie(tr, word);
    } while (strcmp(word, "\0") != 0);

    time = stop_clock();
    printf("%ldms\n", time);
}

void read_remove_btree(btree **bt, int kaput)
{   
    /* a funcao btree_remove() nao conseguiu ficar completamente
    implementada. estao implementados os casos 1, 2a, 2b e 2c.
    fazemos a remocao ate encontrar um caso 3a ou 3b, que como
    nao se encontra implementado, daria segmentation fault */
    char *word;
    long time;
    int i = 0;
    start_clock();
    while (i < kaput) {
        word = min_btree(*bt);
        btree_remove(bt, word);
        i++;
    }

    time = stop_clock();
    printf("%ldms\n", time);
}

int main() {
    trie *tr = nova_trie();
    btree *bt;
    int LER_X;
    int LER_Y;
    nova_btree(&bt);

    LER_X = 500;
    LER_Y = LER_X / 10;
    printf("\n***** TRIES *****\n");
    printf("* Inserting %d words: ", LER_X);
    read_insert_trie(tr, LER_X);
    printf("* Searching %d words: ", LER_Y);
    read_search_trie(tr, LER_Y);
    printf("* Removing all %d words: ", LER_X);
    read_remove_trie(tr);
    printf("***************\n");

    printf("\n***** BTREES *****\n");
    printf("* Inserting %d words: ", LER_X);
    read_insert_btree(&bt, LER_X);
    printf("* Searching %d words: ", LER_Y);
    read_search_btree(bt, LER_Y);
    printf("* Removing all %d words: ", LER_X);
    read_remove_btree(&bt, 422);
    //btree_destroy(&bt);
    printf("***************\n");

    LER_X = 1000;
    LER_Y = LER_X / 10;
    printf("\n***** TRIES *****\n");
    printf("* Inserting %d words: ", LER_X);
    read_insert_trie(tr, LER_X);
    printf("* Searching %d words: ", LER_Y);
    read_search_trie(tr, LER_Y);
    printf("* Removing all %d words: ", LER_X);
    read_remove_trie(tr);
    printf("***************\n");

    nova_btree(&bt);
    printf("\n***** BTREES *****\n");
    printf("* Inserting %d words: ", LER_X);
    read_insert_btree(&bt, LER_X);
    printf("* Searching %d words: ", LER_Y);
    read_search_btree(bt, LER_Y);
    printf("* Removing all %d words: ", LER_X);
    read_remove_btree(&bt, 900);
    //btree_destroy(&bt);
    printf("***************\n");

    LER_X = 10000;
    LER_Y = LER_X / 10;
    printf("\n***** TRIES *****\n");
    printf("* Inserting %d words: ", LER_X);
    read_insert_trie(tr, LER_X);
    printf("* Searching %d words: ", LER_Y);
    read_search_trie(tr, LER_Y);
    printf("* Removing all %d words: ", LER_X);
    read_remove_trie(tr);
    printf("***************\n");

    nova_btree(&bt);
    printf("\n***** BTREES *****\n");
    printf("* Inserting %d words: ", LER_X);
    read_insert_btree(&bt, LER_X);
    printf("* Searching %d words: ", LER_Y);
    read_search_btree(bt, LER_Y);
    printf("* Removing all %d words: ", LER_X);
    read_remove_btree(&bt, 3285);
    //btree_destroy(&bt);
    printf("***************\n");

    LER_X = 50000;
    LER_Y = LER_X / 10;
    printf("\n***** TRIES *****\n");
    printf("* Inserting %d words: ", LER_X);
    read_insert_trie(tr, LER_X);
    printf("* Searching %d words: ", LER_Y);
    read_search_trie(tr, LER_Y);
    printf("* Removing all %d words: ", LER_X);
    read_remove_trie(tr);
    printf("***************\n");

    nova_btree(&bt);
    printf("\n***** BTREES *****\n");
    printf("* Inserting %d words: ", LER_X);
    read_insert_btree(&bt, LER_X);
    printf("* Searching %d words: ", LER_Y);
    read_search_btree(bt, LER_Y);
    printf("* Removing all %d words: ", LER_X);
    read_remove_btree(&bt, 0);
    //btree_destroy(&bt);
    printf("***************\n");

    exit(EXIT_SUCCESS);
}