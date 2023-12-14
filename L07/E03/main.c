#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Graph.h"

int main() {
    FILE *fp;
    Graph G;

    if ((fp = fopen("../grafo.txt", "r")) == NULL)
        exit(1);

    G = GRAPHload(fp);
}