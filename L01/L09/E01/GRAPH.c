//
// Created by Marco on 04/02/2022.
//

#include "GRAPH.h"
#include "ST.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo *link;

struct nodo {
    int id;
    int wt;
    link next;
};

struct grafo {
    int V;
    int E;
    ST st;
    int **madj;
    link *ladj;
    int *sources;
};

static int **matrixInit(int maxN) {
    int **m;
    m = malloc(maxN * sizeof (int *));
    for (int i=0; i<maxN; i++) {
        m[i] = calloc(maxN, sizeof (int));
    }
    for (int i=0; i<maxN; i++) {
        for (int j=0; j<maxN; j++) {
            m[i][j] = 0;
        }
    }
    return m;
}

static void matrixFree (int **m, int n) {
    int i;
    for (i=0; i<n; i++) {
        free(m[i]);
    }
    free(m);
}

static link NEW(int dst, int w, link next){
    link x;
    x = malloc(sizeof(*x));
    x->id = dst;
    x->wt = w;
    x->next =  next;
    return x;
}


GRAPH GRAPHinit(int V) {
    GRAPH G = malloc(sizeof (*G));
    G->V = V;
    G->E = 0;
    G->st = STinit(V);
    G->madj = matrixInit(V);
    G->sources = calloc(V, sizeof (int ));
    return G;
}

void GRAPHfree(GRAPH G) {
    STfree(G->st);
    matrixFree(G->madj, G->V);
    free(G);
}

static EDGE NEWEdge(int v, int w, int wt) {
    EDGE edge;
    edge.v = v;
    edge.w = w;
    edge.wt = wt;
    return edge;
}


static void removeE(GRAPH G, EDGE e){
    int v = e.v, w = e.w;
    if(G->madj[v][w] != 0){
        G->madj[v][w] = 0;
        G->E--;
    }
}

static void insertE (GRAPH g, EDGE e){
    int v = e.v, w = e.w, wt = e.wt;
    if(g->madj[v][w] == 0)
        g->E++;
    g->madj[v][w] = wt;
}


static void GRAPHinsertE (GRAPH G, int id1, int id2, int wt) {
    EDGE edge = NEWEdge(id1, id2, wt);
    insertE(G, edge);
}

static void GRAPHremoveE (GRAPH G, int id1, int id2, int wt) {
    EDGE edge = NEWEdge(id1, id2, wt);
    removeE(G, edge);
}

GRAPH GRAPHload (FILE *fp) {
    GRAPH G;
    int i, n;
    int wt;
    char id1[30], id2[30];
    int index1, index2;
    fscanf(fp, "%d", &n);
    G = GRAPHinit(n);
    for (i=0; i<n; i++) {
        fscanf(fp, "%s", id1);
        STinsert(G->st, id1);
    }
    while ((fscanf(fp, "%s %s %d", id1, id2, &wt)) == 3) {
        index1 = STsearch(G->st, id1);
        index2 = STsearch(G->st, id2);
        if (index1>=0 && index2>=0) {
            GRAPHinsertE(G, index1, index2, wt);
        }
    }
    return G;
}

int GRAPHedges (GRAPH G, int *a, int i) {
    int j, n=0;
    for (j=0; j<G->V; j++) {
        if (G->madj[i][j] != 0)
            a[n++] = j;
    }
    return n;
}

static link listIns(link head, int dst, int wt){
    head = NEW(dst, wt ,head);
    return head;
}

void GRAPHladjcreate(GRAPH G){
    int i,j;
    G->ladj = malloc(G->V * sizeof(link));
    for (i = 0; i < G->V; i++)
        G->ladj[i] = NULL;
    for (i = 0; i < G->V; i++) {
        for (j = 0; j < G->V; j++) {
            if (G->madj[i][j] != 0) {
                G->ladj[i] = listIns(G->ladj[i], j, G->madj[i][j]);
            }
        }
    }

}

static int LISTsearch(link head, int i){
    link x;
    for(x=head; x!=NULL; x=x->next)
        if(x->id == i)
            return 1;
    return 0;
}

static EDGE *createEdgelist(GRAPH G){
    EDGE *archi;
    archi = malloc(G->E* sizeof(EDGE));
    link t;
    int i,j=0;
    for(i=0; i<G->V; i++){
        for(t = G->ladj[i]; t!=NULL; t=t->next){
            archi[j++] = NEWEdge(i, t->id, t->wt);
        }
    }
    return archi;
}

void dfsR (GRAPH G, EDGE e, int *time, int *pre, int *flag) {
    link t;
    int v, w = e.w;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != NULL; t = t->next) {
        if (pre[t->id] == -1)
            dfsR(G, NEWEdge(w, t->id, 1), time, pre, flag);
        else {
            v = t->id;
            if (pre[w] < pre[v])
                *flag = 0;
        };
    }
}

static int isAciclico(GRAPH G) {
    int flag=1, v, time=0, *pre;
    pre = malloc(G->V * sizeof (int));
    for (v=0; v<G->V; v++)
        pre[v] = -1;
    for (v=0; v<G->V; v++)
        if(pre[v] == -1)
            dfsR(G, NEWEdge(v, v, 1), &time, pre, &flag);
    return flag;
}

static int checkSum(EDGE *sol, int l){
    int i, sum=0;
    for(i=0; i<l; i++){
        sum += sol[i].wt;
    }
    return sum;
}


void combinazioni(GRAPH G, int pos, EDGE *sol, EDGE *best, EDGE *archi, int *bestval, int *found, int l, int start) {
    int i, tmp;
    if (pos >= l) {
        for (i=0; i<l; i++){
            removeE(G, sol[i]);
        }
        if (isAciclico(G)) {
            *found = 1;
            tmp = checkSum(sol, pos);
            if (tmp > *bestval) {
                *bestval = tmp;
                for (i=0; i<l; i++)
                    best[i] = sol[i];
            }
            for (i=0; i<l; i++)
                insertE(G, sol[i]);
        }
        return;
    }
    for (i=start; i<G->E; i++) {
        sol[pos] = archi[i];
        combinazioni(G, pos+1, sol, best, archi, bestval, found, l, i+1);
    }
    return;
}

void GRAPHtoDAG (GRAPH G) {
    EDGE *sol, *bestsol, *archi;
    int i, j, found=0, bestval=0;
    sol = malloc(G->E * sizeof (EDGE));
    bestsol = malloc(G->E * sizeof(EDGE));
    GRAPHladjcreate(G);
    archi = createEdgelist(G);
    for (i=1; i<G->E && !found; i++) {
        combinazioni(G, 0, sol, bestsol, archi, &bestval, &found, i, 0);
    }
    if(found) {
        printf("DAG ottenuto rimuovendo %d  archi a peso %d: \n", i - 1, bestval);
        for (j = 0; j < i - 1; j++) {
            printf("(%s -> %s) ", STsearchByIndex(G->st, bestsol[j].v), STsearchByIndex(G->st, bestsol[j].w));
            removeE(G, bestsol[j]);
        }
        printf("\n");
    }
    else
        printf("LOL\n");
}