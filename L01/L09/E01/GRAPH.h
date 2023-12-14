//
// Created by Marco on 04/02/2022.
//

#ifndef E01_GRAPH_H
#define E01_GRAPH_H

#include <stdio.h>

typedef struct grafo *GRAPH;
typedef struct {
    int v;
    int w;
    int wt;
} EDGE;

GRAPH GRAPHinit(int V);
void GRAPHfree(GRAPH G);
GRAPH GRAPHload (FILE *fp);
int GRAPHedges (GRAPH G, int *a, int i);
void GRAPHladjcreate(GRAPH G);
void GRAPHtoDAG (GRAPH G);

#endif //E01_GRAPH_H
