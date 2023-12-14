#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 50

typedef struct {
    char type;
    int amount;
} pietre_t;

void typeDefine (pietre_t *pietre);
int leggiFile(FILE *fp, pietre_t *vet);
int disp_rip(int pos, pietre_t *val,char *sol,int n,int k);
int pruning(char sol, char value);
int ricercaSoluzione(int l, int r, char *sol, pietre_t *val, int max);


int main() {
    time_t start, end;
    double sec;
    FILE *fp;
    char nome[MAXN], *sol;
    int n, i, n_pietre, max;
    pietre_t pietre[4];

    typeDefine(pietre);

    /*printf("Inserire nome file da aprire:");
    scanf("%s", nome);*/
    if ((fp = fopen("../sfida.txt", "r")) == NULL)
        exit(1);
    fscanf(fp, "%d", &n);

    for (i=0; i<n; i++) {
        n_pietre = leggiFile(fp, pietre);
        sol = malloc(n_pietre * sizeof (char));
        printf("TEST #%d:\n", i+1);
        printf("Numero pietre totali: %d\n", n_pietre);
        start = clock();
        max = ricercaSoluzione(0, n_pietre, sol, pietre, 0);
        end = clock();
        sec = (double)(end - start)/(double) CLOCKS_PER_SEC;
        printf("Lunghezza massima collana: %d\n", max);
        printf("L'esecuzione ha impiegato %.3lf secondi.\n\n", sec);
        free(sol);
    }
    return 0;
}

void typeDefine(pietre_t *pietre) {
    pietre[0].type = 'Z';
    pietre[1].type = 'R';
    pietre[2].type = 'T';
    pietre[3].type = 'S';
}

int leggiFile(FILE *fp, pietre_t *vet) {
    int i, tot=0;
    for (i=0; i<4; i++) {
        fscanf(fp, "%d", &vet[i].amount);
        tot += vet[i].amount;
    }
    return tot;
}

int disp_rip(int pos, pietre_t *val,char *sol,int n,int k){
    int i;
    int flag = 0;

    // soluzione
    if (pos >= k) {
        return 1;
    }

    for (i = 0; i < n; i++) {
        if (pos == 0 || (val[i].amount > 0 && !pruning(sol[pos-1], val[i].type))) {
            sol[pos] = val[i].type;
            val[i].amount--;
            if (disp_rip(pos + 1, val, sol, n, k))
                flag = 1;
            val[i].amount++;
            if (flag)
                return 1;
        }
    }
    return 0;
}

int pruning(char sol, char value) {
    switch (sol) {
        case 'Z':
            if (value != 'Z' && value != 'R')
                return 1;
            return 0;
        case 'S':
            if (value != 'S' && value != 'T')
                return 1;
            return 0;
        case 'R':
            if (value != 'S' && value != 'T')
                return 1;
            return 0;
        case 'T':
            if (value != 'Z' && value != 'R')
                return 1;
            return 0;
    }
    return 0;
}

int ricercaSoluzione(int l, int r, char *sol, pietre_t *val, int max) {
    int m = (l+r)/2;
    if (l>r)
        return max = r;
    if (disp_rip(0, val, sol,4, m)) {
        max = ricercaSoluzione(m+1, r, sol, val, max);
    }
    else
        max = ricercaSoluzione(l, m-1, sol, val, max);
    return max;
}
