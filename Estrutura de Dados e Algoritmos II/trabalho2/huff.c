#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"

char *readfile(char *filename, FreqNode **buffer);
void writefile(char *filename, char *alltext, FreqNode *root, NodeLList *auxlist, int numvalidsymbols);
int main(int argc, char**argv);

char *readfile(char *filename, FreqNode **buffer)
{
    FILE *input;
    char *line = NULL;
    char *alltext = "";
    size_t len = 0;
    ssize_t read;
    int i;

    input = fopen(filename, "r");

    if (!input) {
        printf("Error: file not found.\n");
        exit(-1);
    }

    while (read = getline(&line, &len, input) != -1) {
        for (i = 0; i < len; i++) {
            if (buffer[line[i]]) {
                buffer[line[i]]->freq += 1;
            } else {
                buffer[line[i]] = malloc(sizeof(FreqNode));
                buffer[line[i]]->sym = substr(line, i, i+1);
                buffer[line[i]]->freq = 1;
            }
            if (line[i] > 31 && line[i] < 127) {
                alltext = concat(alltext, substr(line, i, i+1));
            }
        }
    }

    free(line);
    fclose(input);

    return alltext;
}

void writefile(char *filename, char *alltext, FreqNode *root, NodeLList *auxlist, int numvalidsymbols)
{
    int i;
    NodeLList *curr;
    char auxchar;
    char auxstr[2] = "\0";
    FILE *output;
    char *newfilename = substr(filename, 0, strlen(filename)-3);
    newfilename = concat(newfilename, "huff");
    output = fopen(newfilename, "wb");
    curr = auxlist;

    fprintf(output, "%d", numvalidsymbols);
    while (curr) {
        fputc(*curr->val->sym, output);
        fprintf(output, "%d", curr->val->freq);
        curr = curr->next;
    }

    encodefile(root, alltext, output);
    fclose(output);
}

int main(int argc, char**argv)
{
    FreqNode *root;
    char *alltext;
    FreqNode *buffer[256] = { NULL };
    NodeLList *txtfreqs = newlist();
    NodeLList *auxlist;
    Stack *auxstack;
    char auxchar;
    char auxchar2;
    int i, j;
    int numvalidsymbols;
    int highestfreq;
    int isfirst;
    
    if (argc == 1) {
        printf("Error: Missing filename as argument.\n");
        exit(-1);
    }

    alltext = readfile(argv[1], buffer);

    numvalidsymbols = 0;
    for (i = 0; i < 256; i++) {
        if (buffer[i] &&
            strcmp(buffer[i]->sym, " ") >= 0 &&
            strcmp(buffer[i]->sym, "~") <= 0
            ) {
            numvalidsymbols++;
        }
    }

    isfirst = 1;
    for (i = 0; i < numvalidsymbols; i++) {
        for (j = 32; j < 127; j++) {
            if (buffer[j] && isfirst) {
                highestfreq = j;
                isfirst = 0;
            } else if (buffer[j] && buffer[j]->freq > buffer[highestfreq]->freq) {
                highestfreq = j;
            }
        }
        addend(&txtfreqs, buffer[highestfreq]);
        buffer[highestfreq] = NULL;
        isfirst = 1;
    }

    auxlist = copylist(txtfreqs);
    root = huffman(&txtfreqs, numvalidsymbols-1);
    auxstack = newstack();
    auxchar = 0 << 7 | 0 << 6 | 0 << 5 | 0 << 4 | 0 << 3 | 0 << 2 | 0 << 1 | 0 << 0;
    push(&auxstack, auxchar);
    generatehuffcodes(&root, &auxstack, 0);
    writefile(argv[1], alltext, root, auxlist, numvalidsymbols);
    return 0;
}
