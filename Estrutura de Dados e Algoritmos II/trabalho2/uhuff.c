#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"

int main(int argc, char **argv)
{
    FILE *file;
    char c;
    char *ptr;
    int numvalidsymbols;
    int i;
    int j;
    NodeLList *txtfreqs = newlist();
    Bitarray *barray = newbitarray();
    FreqNode *node;
    FreqNode *root;
    char *newfilename = substr(argv[1], 0, strlen(argv[1])-4);
    newfilename = concat(newfilename, "dehuff");

    if (argc == 1) {
        printf("Error: Missing filename as argument.\n");
        exit(-1);
    }

    file = fopen(argv[1], "rb");
    if (!file) {
        printf("Error: file not found.\n");
        exit(-1);
    }

    fscanf(file, "%d", &numvalidsymbols);

    for (i = 0; i < numvalidsymbols; i++) {
        c = fgetc(file);
        ptr = malloc(sizeof(char));
        *ptr = c;
        fscanf(file, "%d", &j);
        node = newfreqnode();
        node->sym = ptr;
        node->freq = j;
        addend(&txtfreqs, node);
    }

    root = huffman(&txtfreqs, numvalidsymbols-1);

    while ((c = fgetc(file)) != EOF) {
        for (i = 7; i > -1; i--) {
            j = getbit(c, i);
            addendbit(&barray, j);
        }
    }

    fclose(file);

    file = fopen(newfilename, "w");
    decodefile(file, root, root, barray);
    fclose(file);
    printf("File %s decompressed, file %s created.\n", argv[1], newfilename);

    return 0;
}