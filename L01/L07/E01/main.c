#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define DD 10
#define DP 20
#define NDIAG 3
#define NELEM 5

typedef struct {
    char nome[MAXN];
    int tipologia;
    int direzione_ingresso;
    int direzione_uscita;
    int requisito_precedenza;
    int finale;
    float valore;
    int difficolta;
} elementi_t;

void leggiElementi(int n_elementi, elementi_t *elementi, FILE *fp);
void stampa(int n, elementi_t *elementi);
void bestSol (elementi_t *elementi, int n);
void bestSolR(int pos, int diag, int **sol, int **bestSolM, float *tot, elementi_t *elementi, int n, int dd, int dp);
int checkSol(int **sol, elementi_t *elementi);
float calcolaVal (int **sol, elementi_t *elementi);

int main() {
    int n_elementi;
    FILE *fp;
    elementi_t *elementi;

    if ((fp  =fopen("../elementi.txt", "r")) == NULL)
        exit(1);

    fscanf(fp, "%d ", &n_elementi);
    elementi = malloc(n_elementi * sizeof (elementi_t));
    leggiElementi(n_elementi, elementi, fp);

    //stampa(n_elementi, elementi);

    bestSol(elementi, n_elementi);

    return 0;
}

void leggiElementi(int n_elementi, elementi_t *elementi, FILE *fp) {
    int i;
    for (i=0; i<n_elementi; i++) {
        fscanf(fp, "%s %d %d %d %d %d %f %d", elementi[i].nome, &elementi[i].tipologia, &elementi[i].direzione_ingresso,
              &elementi[i].direzione_uscita, &elementi[i].requisito_precedenza, &elementi[i].finale, &elementi[i].valore,
              &elementi[i].difficolta);
    }
}

void stampa(int n, elementi_t *elementi) {
    for (int i=0; i<n; i++) {
        printf("%s %d %d %d %d %d %.2f %d\n", elementi[i].nome, elementi[i].tipologia, elementi[i].direzione_ingresso,
               elementi[i].direzione_uscita, elementi[i].requisito_precedenza, elementi[i].finale, elementi[i].valore,
               elementi[i].difficolta);
    }
}

void bestSol (elementi_t *elementi, int n) {
    int **sol = malloc(NDIAG * sizeof (int *));
    int **bestSolM = malloc(NDIAG * sizeof (int *));
    float tot  = 0;
    int i, j;

    for (i=0; i<NDIAG; i++) {
        sol[i] = malloc(NELEM * sizeof (int ));
        bestSolM[i] = malloc(NELEM * sizeof (int ));
        for (j=0; j<NELEM; j++)
            sol[i][j] = -1;
    }
    bestSolR(0, 0, sol, bestSolM, &tot, elementi, n, 0, 0);
    printf("DD = %d DP = %d\n", DD, DP);
    printf("TOT = %.2f\n", tot);
    for (i=0; i<NDIAG; i++) {
        printf("DIAG #%d\n", i+1);
        for (j=0; j<NELEM && bestSolM[i][j]!=-1; j++) {
            printf("%s ", elementi[bestSolM[i][j]].nome);
        }
        printf("\n");
    }

}

void bestSolR(int pos, int diag, int **sol, int **bestSolM, float *tot, elementi_t *elementi, int n, int dd, int dp) {
    int i, j;
    float val;

    if (diag >= NDIAG) {
        if (checkSol(sol, elementi)) {
            val = calcolaVal(sol, elementi);
            if (val > *tot) {
                *tot = val;
                for (i=0; i<NDIAG; i++) {
                    for (j=0; j<NELEM; j++) {
                        bestSolM[i][j] = sol[i][j];
                    }
                }
            }
        }
        return;
    }

    for (i=0; i<n; i++) {
        if (pos == 0) {
            if (elementi[i].direzione_ingresso == 0) continue;
            if (elementi[i].requisito_precedenza == 1) continue;
        }
        if (pos > 0) {
            if (elementi[i].direzione_ingresso != elementi[sol[diag][pos-1]].direzione_uscita) continue;
        }
        if (dd+elementi[i].difficolta > DD || dp+elementi[i].difficolta>DP) continue;

        sol[diag][pos] = i;
        bestSolR(pos+1, diag, sol, bestSolM, tot, elementi, n, dd+elementi[i].difficolta, dp+elementi[i].difficolta);
    }
    if (pos > 0) {
        sol[diag][pos] = -1;
        bestSolR(0, diag+1, sol, bestSolM, tot, elementi, n, 0, dp);
    }
    return;

}

int checkSol(int **sol, elementi_t *elementi) {
    int i, j;
    int acrob;
    int avanti = 0;
    int indietro = 0;
    int seq = 0;
    for (i=0; i<NDIAG; i++) {
        acrob = 0;
        for (j=0; j<NELEM && sol[i][j]!=-1; j++) {
            if (elementi[sol[i][j]].tipologia != 0) {
                acrob = 1;
                if (j>0 && elementi[sol[i][j-1]].tipologia!=0)
                    seq = 1;
            }
            if (elementi[sol[i][j]].tipologia == 2) avanti = 1;
            if (elementi[sol[i][j]].tipologia == 1) indietro = 1;
        }
        if (!acrob) return 0;
    }
    if (!avanti || !indietro) return 0;
    if (!seq) return 0;
    return 1;
}

float calcolaVal (int **sol, elementi_t *elementi) {
    int i, j;
    float *diag = calloc(NDIAG, sizeof (int));
    float coeff = 1.0;
    for (i=0; i<NDIAG; i++) {
        for (j=0; j<NELEM && sol[i][j]!=-1; j++) {
            diag[i] += elementi[sol[i][j]].valore;
            if (i==2) {
                if (elementi[sol[i][j]].difficolta >= 8.0)
                    coeff = 1.5;
            }
        }
    }
    diag[2] = diag[2] * coeff;
    return diag[0]+diag[1]+diag[2];
}