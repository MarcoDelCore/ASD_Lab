
#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 30
#define MAX_WT INT_MAX

typedef struct nodo nodo_t, *link;

struct nodo {
    int v;
    int wt;
    link next;
};

struct graph {
    int V;
    int E;
    int **madj;
    ST tab;
    link *ladj;
    link z;
};

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

static int **MATRIXinit (int v) {
    int i, j;
    int **t = calloc(v,sizeof(int *));
    for (i=0; i<v; i++){
        t[i] = calloc(v,sizeof (int));
    }
    for (i=0; i<v; i++) {
        for (j=0; j<v; j++) {
            t[i][j] = MAX_WT;
        }
    }
    return t;
}

static Edge EDGEcreate (int v, int w, int wt) {
    Edge e;
    e.v  =v;
    e.w = w;
    e.wt = wt;
    return e;
}

Graph GRAPHinit (int v) {
    Graph G = malloc(sizeof(*G));
    G->V = v;
    G->E = 0;
    G->madj = MATRIXinit(v);
    G->tab = STinit(v);
    return G;
}

void GRAPHfree(Graph G) {
    int i;
    for (i=0; i<G->V; i++) {
        free(G->madj[i]);
    }
    free(G->madj);
    STfree(G->tab);
    free(G);
}

void GRAPHinsertE (Graph G, int id1, int id2, int wt) {
    Edge e = EDGEcreate(id1, id2, wt);
    if (G->madj[e.v][e.w] == MAX_WT)
        G->E++;
    G->madj[e.v][e.w] = wt;
    G->madj[e.w][e.v] = wt;
}

Graph GRAPHload(FILE *fp) {
    Graph G;
    int i, V=0, wt, cnt = 0;
    int id1, id2;
    char label1[MAXN], label2[MAXN], net_id1[MAXN], net_id2[MAXN], temp[140];

    while ((fscanf(fp, "%s %s %s %s %d", label1, net_id1, label2, net_id2, &wt)) == 5) {
        V++;
    }
    G = GRAPHinit(V);
    rewind(fp);
    for (i=0; i<V; i++) {
        fscanf(fp, "%s %s %s %s %d", label1, net_id1, label2, net_id2, &wt);
        if (STsearch(G->tab, label1) == -1)
            STinsert(G->tab, label1, net_id1, cnt++);
        if (STsearch(G->tab, label2) == -1)
            STinsert(G->tab, label2, net_id2, cnt++);
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >= 0) {
            GRAPHinsertE(G, id1, id2, wt);
        }
    }
    G->V = cnt;
    return G;
}

void GRAPHedges (Graph G, Edge *a) {
    int i, j, E=0;
    for (i=0; i<G->V; i++)
        for (j = i+1; j<G->V; j++)
            if (G->madj[i][j] != MAX_WT)
                a[E++] = EDGEcreate(i, j, G->madj[i][j]);
}

void GRAPHstore (Graph G, FILE *fp) {
    int i, j;
    Edge *a;
    a = malloc(G->E * sizeof (Edge));
    GRAPHedges(G, a);
    fprintf(fp, "N. vertici: %d\n", G->V);
    for (i=0; i<G->V; i++) {
        fprintf(fp, "\n%d. %s\n", i, STsearchByIndex(G->tab, i));
        fprintf(fp, "Archi:\n");
        for (j=0; j<G->E; j++) {
            if (a[j].v == i || a[j].w == i) {
                fprintf(fp, "%s %s %d |", STsearchByIndex(G->tab, a[j].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);
            }
        }
    }
}

int GRAPHadjacent (Graph G, char *label1, char *label2, char *label3) {
    int id1, id2, id3;
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    id3 = STsearch(G->tab, label3);
    if (G->madj[id1][id2] != MAX_WT)
        if (G->madj[id1][id3] != MAX_WT)
            if (G->madj[id2][id3] != MAX_WT)
                return 1;
    return 0;
}

int GRAPHmat2list (Graph G) {
    int i, j, v;

    G->z = NEW(-1, 0, NULL);
    G->ladj = malloc(G->V * sizeof (link));

    for (v=0; v<G->V; v++)
        G->ladj[v] = G->z;

    for (i=1; i<G->V; i++) {
        for (j=0; j<i; j++) {
            if (G->madj[i][j] != MAX_WT) {
                G->ladj[i] = NEW(j, G->madj[i][j], G->ladj[i]);
                G->ladj[j] = NEW(i, G->madj[i][j], G->ladj[j]);
                if (G->ladj[i] == NULL || G->ladj[j] == NULL)
                    return 0;
            }
        }
    }
    return 1;
}