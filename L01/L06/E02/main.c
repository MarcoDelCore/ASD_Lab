#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 50

typedef enum {
    zaffiro, rubino, topazio, smeraldo
} pietre_e;

int max(int a, int b);
int leggiFile(FILE *fp, int *z, int *r, int *t, int *s);
int *****malloc5d(int z, int r, int t, int s);
void free5d (int *****M, int z, int r, int t);
int fZ (int z, int r, int t, int s, int *****M) ;
int fR (int z, int r, int t, int s, int *****M) ;
int fT (int z, int r, int t, int s, int *****M) ;
int fS (int z, int r, int t, int s, int *****M) ;

int main() {
    time_t start, stop;
    double sec;
    FILE *fp;
    char nome[MAXN];
    int n, i, n_pietre;
    int z, r, t, s;
    int *****M;
    int lz, lr, lt, ls;

    printf("Inserire nome file da aprire:");
    scanf("%s", nome);

    if ((fp = fopen(nome, "r")) == NULL) {
        printf("Errore apertura file input.\n");
        exit(1);
    }
    fscanf(fp, "%d ", &n);

    for (i=0; i<n; i++) {
        n_pietre = leggiFile(fp, &z, &r, &t, &s);
        M = malloc5d(z, r, t, s);
        printf("Test #%d\n", i+1);
        printf("Pietre totali: %d\n", n_pietre);
        start = clock();
        lz = fZ(z, r, t, s, M);
        lr = fR(z, r, t, s, M);
        lt = fT(z, r, t, s, M);
        ls = fS(z, r, t, s, M);
        stop = clock();
        sec = (double)(stop - start)/(double) CLOCKS_PER_SEC;
        printf("Lunghezza max con Z: %d\n", lz);
        printf("Lunghezza max con R: %d\n", lr);
        printf("Lunghezza max con T: %d\n", lt);
        printf("Lunghezza max con S: %d\n", ls);
        printf("Lunghezza max: %d\n", max(max(lz, lr), max(lt, ls)));
        printf("Tempo impiegato: %.5lf\n\n", sec);
        free5d(M, z, r, t);
    }

    return 0;
}

int leggiFile(FILE *fp, int *z, int *r, int *t, int *s) {
    int tot;
    fscanf(fp, "%d %d %d %d\n", z, r, t, s);
    tot = *z + *r + *t + *s;
    return tot;
}

int max(int a, int b) {
    if (a>b)
        return a;
    return b;
}

int fZ (int z, int r, int t, int s, int *****M) {
    if (z <= 0)
        return 0;
    if (M[zaffiro][z][r][t][s] != -1)
        return M[zaffiro][z][r][t][s];
    return M[zaffiro][z][r][t][s] = 1 + max(fZ(z-1, r, t, s, M), fR(z-1, r, t, s, M));
}

int fR (int z, int r, int t, int s, int *****M)  {
    if (r <= 0)
        return 0;
    if (M[rubino][z][r][t][s] != -1)
        return M[rubino][z][r][t][s];
    return M[rubino][z][r][t][s] = 1 + max(fS(z, r-1, t, s, M), fT(z, r-1, t, s, M));
}

int fT (int z, int r, int t, int s, int *****M)  {
    if (t <= 0)
        return 0;
    if (M[topazio][z][r][t][s] != -1)
        return M[topazio][z][r][t][s];
    return M[topazio][z][r][t][s] = 1 + max(fZ(z, r, t-1, s, M), fR(z, r, t-1, s, M));
}

int fS (int z, int r, int t, int s, int *****M)  {
    if (s <= 0)
        return 0;
    if (M[smeraldo][z][r][t][s] != -1)
        return M[smeraldo][z][r][t][s];
    return M[smeraldo][z][r][t][s] = 1 + max(fS(z, r, t, s-1, M), fT(z, r, t, s-1, M));
}

int *****malloc5d(int z, int r, int t, int s) {
    int *****M;
    int i, j, k, l, x;
    M = calloc(smeraldo+1, sizeof (int ****));
    for (i=0; i<=smeraldo; i++) {
        M[i] = calloc(z+1, sizeof (int ***));
        for (j=0; j<=z; j++) {
            M[i][j] = calloc(r+1, sizeof (int **));
            for (k=0; k<=r; k++) {
                M[i][j][k] = calloc(t + 1, sizeof(int *));
                for (l=0; l<=t; l++) {
                    M[i][j][k][l] = calloc(s+1, sizeof (int ));
                    for (x=0; x<=s; x++)
                        M[i][j][k][l][x] = -1;
                }
            }

        }
    }
    return M;
}

void free5d (int *****M, int z, int r, int t) {
    int i, j, k, x;
    for (x = zaffiro; x <= smeraldo; x++) {
        for (i = 0; i < z; i++) {
            for (j = 0; j < r; j++) {
                for (k = 0; k < t; k++)
                    free(M[x][i][j][k]);
                free(M[x][i][j]);
            }
            free(M[x][i]);
        }
        free(M[x]);
    }
    free(M);
}