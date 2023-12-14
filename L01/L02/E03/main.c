#include <stdio.h>
#include <stdlib.h>
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

typedef enum {
    data,
    tratta,
    partenza,
    arrivo,
    lettura,
    fine,
    errore
} e_comando;

e_comando scegliComando();
void menuParola(s_log **ordData, s_log **ordTratta, s_log **ordPartenza, s_log **ordArrivo, int nr, e_comando comando);
void print(s_log **tab, int n);
void ordinaStruct (s_log **A, int N, e_comando comando);
void ordinaOra (s_log **A, int N, int l, int r);
int stringCompare (s_log *s1, s_log *s2, e_comando campo);

int main() {
    FILE *fp;
    int nr, i;
    char nome[MAXN], buff[MAXN];
    s_log *tab;
    s_log **ordData, **ordTratta, **ordPartenza, **ordArrivo;
    e_comando comando;

    do {
        printf("Inserire nome file da leggere:");
        scanf("%s", nome);

        if ((fp = fopen(nome, "r")) == NULL)
            exit(1);

        fscanf(fp, "%d", &nr);
        tab = malloc(nr * sizeof (s_log));
        ordData = malloc(nr * sizeof (s_log *));
        ordTratta = malloc(nr * sizeof (s_log *));
        ordPartenza = malloc(nr * sizeof (s_log *));
        ordArrivo = malloc(nr * sizeof (s_log *));

        for (i=0; i<nr; i++) {
            fscanf(fp, "%s %s %s %s %s %s %d", tab[i].codice, tab[i].partenza,
                   tab[i].destinazione, tab[i].data, tab[i].ora_p, tab[i].ora_a, &tab[i].ritardo);
        }

        for (i=0; i<nr; i++) {
            ordData[i] = ordTratta[i] = ordPartenza[i] = ordArrivo[i] = &tab[i];
        }

        printf("Menu opzioni:\n-Ordina_data\n-Ordina_tratta\n-Ordina_partenza\n-Ordina_arrivo\n-Lettura\n-Fine\n");
        comando = scegliComando();
        gets(buff);
        do {
            if (comando==errore) {
                printf("Comando errato.\n");
                gets(buff);
            }
            else {
                menuParola(ordData, ordTratta, ordPartenza, ordArrivo, nr, comando);
                gets(buff);
            }
            comando = scegliComando();
            gets(buff);
        } while (comando!=fine && comando!=lettura);

        free(tab);
        free(ordData);
        free(ordTratta);
        free(ordPartenza);
        free(ordArrivo);
        fclose(fp);

    } while (comando == lettura);

    return 0;
}

e_comando scegliComando() {
    char com[MAXN];
    e_comando c;
    char tabella[errore][MAXN] = {
            "Ordina_data", "Ordina_tratta", "Ordina_partenza", "Ordina_arrivo", "Lettura", "Fine"
    };
    printf("Inserire comando:");
    scanf("%s", com);
    c = data;
    while (c<errore && strcmp(com, tabella[c])!=0)
        c++;
    return c;
}

void menuParola(s_log **ordData, s_log **ordTratta, s_log **ordPartenza, s_log **ordArrivo, int nr, e_comando comando) {
    switch (comando) {
        case data:
            ordinaStruct(ordData, nr, comando);
            break;
        case tratta:
            ordinaStruct(ordTratta, nr, comando);
            break;
        case partenza:
            ordinaStruct(ordPartenza, nr, comando);
            break;
        case arrivo:
            ordinaStruct(ordArrivo, nr, comando);
            break;
        default:
            break;
    }
}

void print(s_log **tab, int n) {
    FILE *f_out;
    int i;
    char nome[MAXN];
    char scelta;
    printf("Stampare su file (F) o a video (V)?");
    scanf("%c", &scelta);
    switch (scelta) {
        case 'F':
            printf("Inserire nome file: ");
            scanf("%s", nome);
            printf("Stai stampando su: %s", nome);
            f_out = fopen(nome, "w");
            for (i=0; i<n; i++) {
                fprintf(f_out, "%s %s %s %s %s %s %d\n", tab[i]->codice, tab[i]->partenza,
                        tab[i]->destinazione, tab[i]->data, tab[i]->ora_p, tab[i]->ora_a, tab[i]->ritardo);
            }
            fclose(f_out);
            break;
        case 'V':
            for (i=0; i<n; i++) {
                printf("%s %s %s %s %s %s %d\n", tab[i]->codice, tab[i]->partenza,
                       tab[i]->destinazione, tab[i]->data, tab[i]->ora_p, tab[i]->ora_a, tab[i]->ritardo);
            }
            break;
        default:
            printf("Comando errato.\n");
            break;
    }
}

void ordinaStruct (s_log **A, int N, e_comando comando) {
    int i, j, l=0, r=N-1, h=1;
    s_log *x;
    while (h < N/3)
        h = 3 * h + 1;
    while(h >= 1) {
        for (i = l + h; i <= r; i++) {
            j = i;
            x = A[i];
            while(j >= l + h && stringCompare(x, A[j-h], comando)<0) {
                A[j] = A[j-h];
                j -=h;
            }
            A[j] = x;
        }
        h = h/3;
    }

    if (comando == data) {
        for (i = 0; i < N; i++) {
            j = 0;
            if (i + j + 1 < N) {
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

    print(A, N);
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

int stringCompare (s_log *s1, s_log *s2, e_comando campo) {
    switch (campo) {
        case data:
            return strcmp(s1->data, s2->data);
        case tratta:
            return strcmp(s1->codice, s2->codice);
        case partenza:
            return strcmp(s1->partenza, s2->partenza);
        case arrivo:
            return strcmp(s1->destinazione, s2->destinazione);
    }
}


