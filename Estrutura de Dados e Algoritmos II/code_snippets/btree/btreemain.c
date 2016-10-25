#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"



int  main()
{
    btree *t;
    char v[32];
    int w;
    char comando[32];
    nova_btree(&t);

    insere_btree(&t, "a");
    insere_btree(&t, "b");
    insere_btree(&t, "c");
    insere_btree(&t, "d");
    insere_btree(&t, "e");
    insere_btree(&t, "f");
    //insere_btree(&t, "g");
    //insere_btree(&t, "h");
    
    while (1) {
        scanf ("%s", comando);
        if (!strcmp (comando, "i")) {
            scanf ("%s", v);
            insere_btree(&t, v);
            printf ("inseriu %s\n", v);
        }
        if (!strcmp (comando, "s")) {
            scanf ("%s", v);
            w = search_btree(t, v);
            printf ("existe: %d\n", w);
        }
        if (!strcmp (comando, "r")) {
            scanf ("%s", v);
            btree_remove(&t, v);
        }
        else if (!strcmp (comando, "l")) {
            lista_btree(t,0);
        }
        else if (!strcmp (comando, "q")) {
            exit (0);
        }
    }
}

