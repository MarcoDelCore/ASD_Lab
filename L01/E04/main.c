#include <stdio.h>
#include <string.h>
#define MAXN 30

typedef struct {
    char codice[MAXN];
    char partenza[MAXN];
    char destinazione[MAXN];
    char data[MAXN];
    char ora_p [MAXN];
    char ora_a[MAXN];
    int ritardo;
} s_log;

void ordinaData (s_log **A, int N);
void ordinaOra (s_log **A, int N, int l, int r);
void ordinaTratta (s_log **A, int N);
void ordinaPartenza (s_log **A, int N);
void ordinaArrivo (s_log **A, int N);

int main() {
    FILE *fp;
    int nr, i;
    s_log tab[MAXN];
    s_log *ordData[MAXN], *ordTratta[MAXN], *ordPartenza[MAXN], *ordArrivo[MAXN];

    if ((fp = fopen("../corse.txt", "r")) == NULL)
        return 1;

    fscanf(fp, "%d", &nr);
    for (i=0; i<nr; i++) {
        fscanf(fp, "%s %s %s %s %s %s %d", tab[i].codice, tab[i].partenza,
               tab[i].destinazione, tab[i].data, tab[i].ora_p, tab[i].ora_a, &tab[i].ritardo);
    }

    printf("Vettore originale:\n");
    for (i=0; i<nr; i++) {
        printf("%s %s %s %s %s %s %d\n", tab[i].codice, tab[i].partenza, tab[i].destinazione,
               tab[i].data, tab[i].ora_p, tab[i].ora_a, tab[i].ritardo);
    }

    for (i=0; i<nr; i++) {
        ordData[i] = ordPartenza[i] = ordArrivo[i] = ordTratta[i] = &tab[i];
    }

    ordinaData(ordData, nr);
    printf("\nVettore ordinato secondo la data:\n");
    for (i=0; i<nr; i++) {
        printf("%s %s %s %s %s %s %d\n", ordData[i]->codice, ordData[i]->partenza, ordData[i]->destinazione,
               ordData[i]->data, ordData[i]->ora_p, ordData[i]->ora_a, ordData[i]->ritardo);
    }

    ordinaTratta(ordTratta, nr);
    printf("\nVettore ordinato secondo codice tratta:\n");
    for (i=0; i<nr; i++) {
        printf("%s %s %s %s %s %s %d\n", ordTratta[i]->codice, ordTratta[i]->partenza, ordTratta[i]->destinazione,
               ordTratta[i]->data, ordTratta[i]->ora_p, ordTratta[i]->ora_a, ordTratta[i]->ritardo);
    }

    ordinaPartenza(ordPartenza, nr);
    printf("\nVettore ordinato secondo stazione di partenza:\n");
    for (i=0; i<nr; i++) {
        printf("%s %s %s %s %s %s %d\n", ordPartenza[i]->codice, ordPartenza[i]->partenza, ordPartenza[i]->destinazione,
               ordPartenza[i]->data, ordPartenza[i]->ora_p, ordPartenza[i]->ora_a, ordPartenza[i]->ritardo);
    }

    ordinaArrivo(ordArrivo, nr);
    printf("\nVettore ordinato secondo stazione di arrivo:\n");
    for (i=0; i<nr; i++) {
        printf("%s %s %s %s %s %s %d\n", ordArrivo[i]->codice, ordArrivo[i]->partenza, ordArrivo[i]->destinazione,
               ordArrivo[i]->data, ordArrivo[i]->ora_p, ordArrivo[i]->ora_a, ordArrivo[i]->ritardo);
    }

    return 0;
}


void ordinaData (s_log **A, int N) {
    int i, j, l=0, r=N-1, h=1;
    s_log *x;
    while (h < N/3)
        h = 3 * h + 1;
    while(h >= 1) {
        for (i = l + h; i <= r; i++) {
            j = i;
            x = A[i];
            while(j >= l + h && strcmp(x->data, A[j-h]->data)<0) {
                A[j] = A[j-h];
                j -=h;
            }
            A[j] = x;
        }
        h = h/3;
    }

    for (i=0; i<N; i++) {
        j = 0;
        if (i+j+1<N) {
            while (strcmp(A[i + j]->data, A[i + j + 1]->data) == 0) {
                j++;
            }
            if (j != 0) {
                ordinaOra(A, N, i, i + j);
                i += j;
            }
        }
    }

}

void ordinaOra (s_log **A, int N, int l, int r) {
    int i, j, h=1;
    s_log *x;
    while (h < N/3)
        h = 3 * h + 1;
    while(h >= 1) {
        for (i = l + h; i <= r; i++) {
            j = i;
            x = A[i];
            while(j >= l + h && strcmp(x->ora_p, A[j-h]->ora_p)<0) {
                A[j] = A[j-h];
                j -=h;
            }
            A[j] = x;
        }
        h = h/3;
    }
}

void ordinaTratta (s_log **A, int N) {
    int i, j, l=0, r=N-1, h=1;
    s_log *x;
    while (h < N/3)
        h = 3 * h + 1;
    while(h >= 1) {
        for (i = l + h; i <= r; i++) {
            j = i;
            x = A[i];
            while(j >= l + h && strcmp(x->codice, A[j-h]->codice)<0) {
                A[j] = A[j-h];
                j -=h;
            }
            A[j] = x;
        }
        h = h/3;
    }
}

void ordinaPartenza (s_log **A, int N) {
    int i, j, l=0, r=N-1, h=1;
    s_log *x;
    while (h < N/3)
        h = 3 * h + 1;
    while(h >= 1) {
        for (i = l + h; i <= r; i++) {
            j = i;
            x = A[i];
            while(j >= l + h && strcmp(x->partenza, A[j-h]->partenza)<0) {
                A[j] = A[j-h];
                j -=h;
            }
            A[j] = x;
        }
        h = h/3;
    }
}

void ordinaArrivo (s_log **A, int N) {
    int i, j, l=0, r=N-1, h=1;
    s_log *x;
    while (h < N/3)
        h = 3 * h + 1;
    while(h >= 1) {
        for (i = l + h; i <= r; i++) {
            j = i;
            x = A[i];
            while(j >= l + h && strcmp(x->destinazione, A[j-h]->destinazione)<0) {
                A[j] = A[j-h];
                j -=h;
            }
            A[j] = x;
        }
        h = h/3;
    }
}
