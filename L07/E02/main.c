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

void stampa(int n, elementi_t *elementi) {
    for (int i=0; i<n; i++) {
        printf("%s %d %d %d %d %d %.2f %d\n", elementi[i].nome, elementi[i].tipologia, elementi[i].direzione_ingresso,
               elementi[i].direzione_uscita, elementi[i].requisito_precedenza, elementi[i].finale, elementi[i].valore,
               elementi[i].difficolta);
    }
}

void leggiElementi(int n_elementi, elementi_t *elementi, FILE *fp);
void mergeSort(elementi_t *elementi, int n);
void mergeSortR (elementi_t *A, elementi_t *B, int l, int r);
void merge(elementi_t *A, elementi_t *B, int l, int r, int q);
void cercaSol(elementi_t *elementi, int n, int sol[NDIAG][NELEM], float *val);
void calcolaVal (int sol[NDIAG][NELEM], elementi_t *elementi, float *val);
float greedyDiag1 (int sol[NDIAG][NELEM], elementi_t *e, int n, int *dp);

int main() {
    int n_elementi;
    FILE *fp;
    elementi_t *elementi;
    float val;
    int sol[NDIAG][NELEM];
    for (int k=0; k<NDIAG; k++) {
        for (int y=0; y<NELEM; y++) {
            sol[k][y] = -1;
        }
    }

    if ((fp  =fopen("elementi.txt", "r")) == NULL)
        exit(1);

    fscanf(fp, "%d ", &n_elementi);
    elementi = malloc(n_elementi * sizeof (elementi_t));
    leggiElementi(n_elementi, elementi, fp);
    mergeSort(elementi, n_elementi);

    stampa(n_elementi, elementi);
    int dp = 0;
   // cercaSol(elementi, n_elementi, sol, &val);
    val = greedyDiag1(sol, elementi, n_elementi, &dp);

    printf("DD = %d DP = %d\n", DD, DP);
    printf("TOT = %.2f\n",val);
    //for (int i=0; i<NDIAG; i++) {
        //printf("DIAG #%d\n", i+1);
        for (int j=0; j<NELEM && sol[0][j]!=-1; j++) {
            printf("%s ", elementi[sol[0][j]].nome);
        }
        printf("\n");
    //}

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

void mergeSort(elementi_t *elementi, int n) {
    int l=0, r=n-1;
    elementi_t *B = malloc(n * sizeof (elementi_t));
    mergeSortR(elementi, B, l, r);
    free(B);
}

void mergeSortR (elementi_t *A, elementi_t *B, int l, int r) {
    int q;
    if (l>=r)
        return;
    q = (l+r)/2;
    mergeSortR(A, B, l, q);
    mergeSortR(A, B, q+1, r);
    merge(A, B, l, r, q);
}

void merge(elementi_t *A, elementi_t *B, int l, int r, int q) {
    int i, j, k;
    i = l;
    j = q+1;
    for(k = l; k <= r; k++)
        if (i > q)
            B[k] = A[j++];
        else if (j > r)
            B[k] = A[i++];
        else if (A[i].tipologia != 0 && A[j].tipologia == 0)
            B[k] = A[i++];
        else if (A[i].valore >= A[j].valore)
            B[k] = A[i++];
        else
            B[k] = A[j++];
    for ( k = r; k >= l; k--)
        A[k] = B[k];
}

void cercaSol(elementi_t *elementi, int n, int sol[NDIAG][NELEM], float *val) {
    int diag, pos, i, j, k;
    int acrob, fronte=0, indietro=0, sequenza=0;
    int dd, dp=0;
    for (diag=0; diag<NDIAG; diag++) {
        /*acrob = 0;
        dd = 0;
        for (pos = 0; pos < NELEM; pos ++) {
            if (pos == 0) {
                for (i = 0; i < n; i++) {
                    if (elementi[i].requisito_precedenza == 0 && elementi[i].direzione_ingresso == 1
                        && dd+elementi[i].difficolta<=DD && dp+elementi[i].difficolta<=DP) {
                        if (!acrob) {
                            if (elementi[i].tipologia != 0) {
                                sol[diag][pos] = i;
                                dd += elementi[i].difficolta;
                                dp += elementi[i].difficolta;
                                acrob = 1;
                                if (elementi[i].tipologia == 2) fronte = 1;
                                if (elementi[i].tipologia == 1) indietro = 1;
                                break;
                            }
                        }
                    }
                }
                if (!acrob) {
                    for (i = 0; i < n; i++) {
                        if (elementi[i].requisito_precedenza == 0 && elementi[i].direzione_ingresso == 1
                            && dd+elementi[i].difficolta<=DD && dp+elementi[i].difficolta<=DP) {
                            sol[diag][pos] = i;
                            dd += elementi[i].difficolta;
                            dp += elementi[i].difficolta;
                            break;
                        }
                    }
                }
            }
            if (pos > 0) {
                for (i=0; i<n; i++) {
                    if (elementi[i].direzione_ingresso == elementi[sol[diag][pos - 1]].direzione_uscita &&
                        dd + elementi[i].difficolta < DD && dp + elementi[i].difficolta < DP) {
                        if (!acrob) {
                            if (elementi[i].tipologia != 0) {
                                sol[diag][pos] = i;
                                dd += elementi[i].difficolta;
                                dp += elementi[i].difficolta;
                                acrob = 1;
                                if (elementi[i].tipologia == 2) fronte = 1;
                                if (elementi[i].tipologia == 1) indietro = 1;
                                break;
                            }
                        }
                        else if (acrob && !sequenza) {
                            if (elementi[i].tipologia != 0) {
                                sol[diag][pos] = i;
                                dd += elementi[i].difficolta;
                                dp += elementi[i].difficolta;
                                sequenza = 1;
                                if (elementi[i].tipologia == 2) fronte = 1;
                                if (elementi[i].tipologia == 1) indietro = 1;
                                break;
                            }
                        }
                        else if (!fronte) {
                            if (elementi[i].tipologia == 2) {
                                sol[diag][pos] = i;
                                dd += elementi[i].difficolta;
                                dp += elementi[i].difficolta;
                                fronte = 1;
                                break;
                            }
                        }
                        else if (!indietro) {
                            if (elementi[i].tipologia == 1) {
                                sol[diag][pos] = i;
                                dd += elementi[i].difficolta;
                                dp += elementi[i].difficolta;
                                indietro = 1;
                                break;
                            }
                        }
                        else {
                            sol[diag][pos] = i;
                            dd += elementi[i].difficolta;
                            dp += elementi[i].difficolta;
                            break;
                        }
                    }
                }
            }
        }*/
    }
    calcolaVal(sol, elementi, val);
}

void calcolaVal (int sol[NDIAG][NELEM], elementi_t *elementi, float *val) {
    int i, j;
    float *diag = calloc(NDIAG, sizeof (int));
    float coeff = 1.0;
    //for (i=0; i<NDIAG; i++) {
        for (j=0; j<NELEM && sol[0][j]!=-1; j++) {
            diag[0] += elementi[sol[0][j]].valore;
            /*if (i==2) {
                if (elementi[sol[i][j]].difficolta >= 8.0)
                    coeff = 1.5;
            }*/
        }
    //}
    diag[2] = diag[2] * coeff;
    *val = diag[0];
}


float greedyDiag1 (int sol[NDIAG][NELEM], elementi_t *e, int n, int *dp) {
    int dd = 0;
    int pos, i, seq=0;
    int fronte=0, indietro=0;
    for (pos = 0; pos < NELEM; pos++) {
        if (pos == 0) {
            for (i = 0; i < n; i++) {
                if (e[i].requisito_precedenza == 0 && e[i].direzione_ingresso == 1
                    && dd + e[i].difficolta <= DD && *dp + e[i].difficolta <= DP && e[i].tipologia != 0) {
                    sol[0][pos] = i;
                    dd += e[i].difficolta;
                    *dp += e[i].difficolta;
                    if (e[i].tipologia == 2) fronte = 1;
                    if (e[i].tipologia == 1) indietro = 1;
                    break;
                }
            }
        }
        if (pos > 0) {
            if (!seq) {
                for (i = 0; i < n; i++) {
                    if (e[i].tipologia != 0 && dd + e[i].difficolta <= DD && *dp + e[i].difficolta <= DP
                    && e[i].direzione_ingresso == e[sol[0][pos - 1]].direzione_uscita) {
                        if (!indietro && e[i].tipologia == 1) {
                            indietro = 1;
                            sol[0][pos] = i;
                            dd += e[i].difficolta;
                            *dp += e[i].difficolta;
                            seq = 1;
                            break;
                        }
                        else if (!fronte && e[i].tipologia == 2) {
                            fronte = 1;
                            sol[0][pos] = i;
                            dd += e[i].difficolta;
                            *dp += e[i].difficolta;
                            seq = 1;
                            break;
                        }
                    }
                }
            }
            else{
                for (i = 0; i < n; i++) {
                    if (e[i].direzione_ingresso == e[sol[0][pos - 1]].direzione_uscita &&
                            dd + e[i].difficolta <= DD && *dp + e[i].difficolta <= DP) {
                        sol[0][pos] = i;
                        dd += e[i].difficolta;
                        *dp += e[i].difficolta;
                        break;
                    }
                }
            }
        }
    }
    float val;
    calcolaVal(sol, e, &val);
    return val;
}
