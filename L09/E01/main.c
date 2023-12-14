#include <stdio.h>
#include "GRAPH.h"

int main() {
    FILE *in;
    GRAPH G;
    in = fopen("../grafo2.txt", "r");
    G = GRAPHload(in);
    //printf("Grafo di %d nodi e %d archi caricato in memoria.\n", GRAPHgetV(G), GRAPHgetE(G));
    GRAPHtoDAG(G);
    printf("Elenco dei nodi sorgente del DAG: \n");
    DAGprintSource(G);
    DAGlongestPathS(G);
    return 0;
}
