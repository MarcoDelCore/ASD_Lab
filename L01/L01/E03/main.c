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

typedef enum {
    stampa, ordina_data, ordina_tratta, ordina_partenza, ordina_arrivo, ricerca, fine, errore
} e_comandi;

void menuParola(s_log tab[], int nr, e_comandi comando);
void print(s_log tab[], int n);
e_comandi scegliComando();
int stringCompare (s_log s1, s_log s2, e_comandi campo);
void shellSort(s_log A[], int N, e_comandi comando);
void shellSort_ora (s_log A[], int N, int l, int r);
void ricercaLineare(s_log A[], int N, char src[]);
void ricercaDicotomica (s_log A[], int N, char src[]);

int main() {
    FILE *fp;
    int nr, i;
    char buff[100];
    s_log tab[MAXN];
    e_comandi comando;

    if ((fp = fopen("../corse.txt", "r")) == NULL)
        return 1;

    fscanf(fp, "%d", &nr);
    for (i=0; i<nr; i++) {
        fscanf(fp, "%s %s %s %s %s %s %d", tab[i].codice, tab[i].partenza,
               tab[i].destinazione, tab[i].data, tab[i].ora_p, tab[i].ora_a, &tab[i].ritardo);
    }
    printf("Menu opzioni:\n-Stampa\n-Ordina_data\n-Ordina_tratta\n-Ordina_partenza\n-Ordina_arrivo\n-Ricerca\n-Fine\n");
    comando = scegliComando();
    do {
        if (comando==errore) {
            printf("Comando errato.\n");
            gets(buff);
        }
        else {
            menuParola(tab, nr, comando);
            gets(buff);
        }
        comando = scegliComando();
    } while (comando!=fine);

    return 0;
}

e_comandi scegliComando() {
    char com[MAXN];
    e_comandi c;
    char tabella[errore][MAXN] = {
            "Stampa", "Ordina_data", "Ordina_tratta", "Ordina_partenza", "Ordina_arrivo", "Ricerca", "Fine"
    };
    printf("Inserire comando:");
    gets(com);
    c = stampa;
    while (c<errore && strcmp(com, tabella[c])!=0)
        c++;
    return c;
}

void menuParola(s_log tab[], int nr, e_comandi comando) {
    char src[MAXN];
    switch (comando) {
        case stampa:
            print(tab, nr);
            break;
        case ricerca:
            printf("Inserire prefisso:");
            scanf("%s", src);
            printf("Risultato ricerca lineare:\n");
            ricercaLineare(tab, nr, src);
            printf("Risultato ricerca dicotomica:\n");
            shellSort(tab, nr, ordina_partenza);
            ricercaDicotomica(tab, nr, src);
            break;
        default:
            shellSort(tab, nr, comando);
            print(tab, nr);
            break;
    }
}

void print(s_log tab[], int n) {
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
                fprintf(f_out, "%s %s %s %s %s %s %d\n", tab[i].codice, tab[i].partenza,
                        tab[i].destinazione, tab[i].data, tab[i].ora_p, tab[i].ora_a, tab[i].ritardo);
            }
            fclose(f_out);
            break;
        case 'V':
            for (i=0; i<n; i++) {
                printf("%s %s %s %s %s %s %d\n", tab[i].codice, tab[i].partenza,
                        tab[i].destinazione, tab[i].data, tab[i].ora_p, tab[i].ora_a, tab[i].ritardo);
            }
            break;
        default:
            printf("Comando errato.\n");
            break;
    }
}

void shellSort(s_log A[], int N, e_comandi comando) {
    int i, j, l=0, r=N-1, h=1;
    s_log x;
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

    if (comando == ordina_data) {
        for (i = 0; i < N; i++) {
            j = 0;
            while (strcmp(A[i + j].data, A[i + j + 1].data) == 0) {
                j++;
            }
            if (j != 0) {
                shellSort_ora(A, N, i, i + j);
                i += j;
            }
        }
    }
}


void shellSort_ora (s_log A[], int N, int l, int r) {
    int i, j, h=1;
    s_log x;
    while (h < N/3)
        h = 3 * h + 1;
    while(h >= 1) {
        for (i = l + h; i <= r; i++) {
            j = i;
            x = A[i];
            while(j >= l + h && strcmp(x.ora_p, A[j-h].ora_p)<0) {
                A[j] = A[j-h];
                j -=h;
            }
            A[j] = x;
        }
        h = h/3;
    }
}

int stringCompare (s_log s1, s_log s2, e_comandi campo) {
    switch (campo) {
        case ordina_data:
            return strcmp(s1.data, s2.data);
        case ordina_tratta:
            return strcmp(s1.codice, s2.codice);
        case ordina_partenza:
            return strcmp(s1.partenza, s2.partenza);
        case ordina_arrivo:
            return strcmp(s1.destinazione, s2.destinazione);
    }
}

void ricercaLineare(s_log A[], int N, char src[]) {
    int i, j, check, found;
    found = 0;
    for (i=0; i<N; i++) {
        check = 0;
        for (j=0; j<strlen(src); j++) {
            if(src[j] == A[i].partenza[j])
                check++;
        }
        if (check == strlen(src)) {
            printf("%s %s %s %s %s %s %d\n", A[i].codice, A[i].partenza,
                   A[i].destinazione, A[i].data, A[i].ora_p, A[i].ora_a, A[i].ritardo);
            found = 1;
        }
    }
    if (found == 0)
        printf("Nessuna corrispondenza trovata.\n");
}

void ricercaDicotomica (s_log A[], int N, char src[]) {
    int l=0, r=N;
    int i, j, found, count;
    i = (l+r)/2;
    while (src[0] != A[i].partenza[0] && l!=r) {
        if (src[0]<A[i].partenza[0])
            r = i;
        else
            l = i;
        i = (l+r)/2;
    }
    found = 0;
    count = 0;
    while (src[0] == A[i].partenza[0] && i<N) {
        for (j=1; src[j]!='\0' && src[j] == A[i].partenza[j]; j++);
        if (j == strlen(src)) {
            printf("%s %s %s %s %s %s %d\n", A[i].codice, A[i].partenza,
                   A[i].destinazione, A[i].data, A[i].ora_p, A[i].ora_a, A[i].ritardo);
            found = 1;
            count++;
        }
        i++;
    }
    i = i-(count+1);
    while (src[0] == A[i].partenza[0] && i>=0) {
        for (j=1; src[j]!='\0' && src[j] == A[i].partenza[j]; j++);
        if (j == strlen(src)) {
            printf("%s %s %s %s %s %s %d\n", A[i].codice, A[i].partenza,
                   A[i].destinazione, A[i].data, A[i].ora_p, A[i].ora_a, A[i].ritardo);
            found = 1;
        }
        i--;
    }
    if (found == 0) {
        printf("Nessuna corrispondenza trovata.\n");
    }

}
