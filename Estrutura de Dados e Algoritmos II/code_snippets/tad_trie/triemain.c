#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

void help()
{
    printf("Comandos:\n");
    printf("  i X\tinsere X na trie\n");
    printf("  e\tmostra se a palavra existe na trie\n");
    printf("  l\tlista a trie alfabeticamente\n");
    printf("  rs X\tremove (simples) X da trie\n");
    printf("  rc X\tremove (completo) X da trie\n");
    printf("  min\tdevolve a min palavra\n");
    printf("  max\tdevolve a max palavra\n");
    printf("  q\tsai do programa\n\n");
}

int  main()
{
    trie *t = nova();
    char v[32];
    int w;
    char comando[32];

    help();

    while (1) {
        scanf ("%s", comando);
        if (!strcmp (comando, "i")) {
            scanf ("%s", v);
            insere(t, v);
            printf ("inseriu %s\n", v);
        }
        else if (!strcmp (comando, "e")) {
            scanf ("%s", v);
            w = existe(t, v);
            printf("%d\n", w);
        }
        else if (!strcmp (comando, "rs")) {
            scanf ("%s", v);
            remove_simples(t, v);
        }
        else if (!strcmp (comando, "rc")) {
            scanf ("%s", v);
            remove_completo(t, v);
        }
        else if (!strcmp (comando, "l")) {
            lista_ord(t, v, 0);
        }
        else if (!strcmp (comando, "min")) {
            min(t, v);
            printf("min: %s\n", v);
        }
        else if (!strcmp (comando, "max")) {
            max(t, v);
            printf("max: %s\n", v);
        }
        else if (!strcmp (comando, "q")) {
            exit (0);
        }
    }

    free(t);
}

