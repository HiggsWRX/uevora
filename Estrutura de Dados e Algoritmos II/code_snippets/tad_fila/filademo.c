#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad_fila.h"

void help()
{
    printf("Comandos:\n");
    printf("  i X\tinsere o valor X na fila\n");
    printf("  r\tremove (e mostra) o valor no topo da fila\n");
    printf("  e\tmostra se a fila está vazia\n");
    printf("  m\tmostra a fila\n");
    printf("  n X\tdevolve o X-esimo valor da fila\n");
    printf("  d X Y\tinsere Y depois de X\n");
    printf("  a X Y\tinsere Y antes ded X\n");
    printf("  x Y\tapaga o valor Y da fila. 1 significa sucesso, 0 caso contrario\n");
    printf("  h\tmostra estas instruções\n");
    printf("  q\tsai do programa\n\n");
}

int main()
{
    struct fila *f = fila_nova();
    int v;
    int w;
    char comando[32];
 
    help();
    
    while (1) {
        scanf ("%s", comando);
        if (!strcmp (comando, "i")) {
            scanf ("%d", &v);
            fila_insere (f, v);
            printf ("inseriu %d\n", v);
        }
        else if (!strcmp (comando, "d")) {
            scanf ("%d %d", &v, &w);
            fila_insere_apos(f, v, w);
        }
        else if (!strcmp (comando, "n")) {
            scanf ("%d", &v);
            w = fila_nesimo(f, v);
            printf("O valor %d e: %d\n", v, w);
        }
        else if (!strcmp (comando, "a")) {
            scanf ("%d %d", &v, &w);
            fila_insere_antes(f, v, w);
        }
        else if (!strcmp (comando, "r")) {
            v = fila_remove (f);
            printf ("remove -> %d\n", v);
        }
        else if (!strcmp (comando, "x")) {
                scanf ("%d", &v);
            w = fila_apaga(f, v);
            printf ("remover %d... %d\n", v, w);
        }
        else if (!strcmp (comando, "e")) {
            printf ("vazio -> %s\n", fila_vazia (f)? "TRUE": "FALSE");
        }
        else if (!strcmp (comando, "m")) {
            fila_mostra(f);
        }
        else if (!strcmp (comando, "h")) {
            help();
        }
        else if (!strcmp (comando, "q")) {
            printf("Good bye.\n");
            exit (0);
        }
    }
}

