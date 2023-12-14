
#ifndef E03_2_GRAPH_H
#define E03_2_GRAPH_H

#include "ST.h"
#include <stdio.h>

typedef struct edge {
    int v;
    int w;
    int wt;
} Edge;

typedef struct graph *Graph;

Graph GRAPHinit (int v);
void GRAPHfree(Graph G);
Graph GRAPHload(FILE *fp);
void GRAPHinsertE (Graph G, int id1, int id2, int wt);
void GRAPHedges (Graph G, Edge *a);
void GRAPHstore (Graph G, FILE *fp);
int GRAPHadjacent (Graph G, char *label1, char *label2, char *label3);
int GRAPHmat2list (Graph G);

#endif //E03_2_GRAPH_H
