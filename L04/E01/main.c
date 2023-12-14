#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int u, v;
} s_archi;

typedef struct {
    int *vertici;
    s_archi *archi;
} s_grafo;

void leggiFile(FILE *fp, int *N, int *E, s_grafo *grafo);
void powerset(int pos,int *val,int *sol,int k,int start, int E, s_archi *archi);

int main() {
    int N, E;
    int *sol;
    FILE *fp;
    s_grafo grafo;

    if ((fp = fopen("../grafo.txt", "r")) == NULL)
        exit(1);

    leggiFile(fp, &N, &E, &grafo);

    sol = malloc(pow(2, N) * sizeof (int));

    powerset(0, grafo.vertici, sol, N, 0, E, grafo.archi);
    return 0;
}

void leggiFile(FILE *fp, int *N, int *E, s_grafo *grafo) {
    int i;

    fscanf(fp, "%d%d", N, E);

    grafo->vertici = malloc((*N)*sizeof (int ));
    grafo->archi = malloc ((*E)*sizeof(s_archi));

    for (i=0; i<(*N); i++)
        grafo->vertici[i] = i;
    for (i=0; i < (*E); i++) {
        fscanf(fp, "%d%d", &(grafo->archi[i].u), &(grafo->archi[i].v));
    }
}

void powerset(int pos,int *val,int *sol,int k,int start, int E, s_archi *archi) {
    int i, j;
    int found;
    if (start >= k) {
        for (i = 0; i < E; i++) {
            found = 0;
            for (j = 0; j < pos; j++) {
                if (sol[j] == archi[i].u || sol[j] == archi[i].v)
                    found = 1;
            }
            if (found == 0)
                break;
        }

        if (found == 1 && pos != 1) {
            for (i = 0; i < pos; i++) {
                printf("%d ", sol[i]);
            }
            printf("\n");
        }
        return;
    }
    for (i = start; i < k; i++) {
        sol[pos] = val[i];
        powerset(pos+1, val, sol, k, i+1, E, archi);
    }
    powerset(pos, val, sol, k, k, E, archi);
}