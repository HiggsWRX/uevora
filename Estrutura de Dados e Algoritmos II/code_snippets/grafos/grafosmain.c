#include <stdio.h>
#include "grafo.h"

int main()
{ 
    struct Arcos arcos[12] = {
        {1,2,1}, {1,3,1}, {2,6,1},
        {3,6,1}, {3,8,1}, {4,7,1},
        {5,6,1}, {5,2,1}, {5,7,1},
        {6,7,1}, {7,3,1}, {8,4,1}
    };
    struct vertice g[8];
    int nvertices = 8;
    int narcos = 12;
    cria_grafo(g, nvertices, narcos, arcos);
    lista_grafo(g, nvertices);
    bfs(g, g, nvertices);
    distancias(g, g, nvertices);

    return 0;
}
