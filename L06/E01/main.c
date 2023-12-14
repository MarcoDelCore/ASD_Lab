#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int s, f;
} att;

att *attLeggi(FILE *in, int *n);
void mergeSort(att *v, int n);
void mergeSortR (att *v, att *b, int l, int r);
void merge(att *v, att *b, int l, int q, int r);
int dA(att a);
void cercaSol(att *val, int n);
void solPrint(att *val, int *P, int i);

int main() {
    int n;
    FILE *in;
    att *v;

    in = fopen("../att.txt", "r");
    if (in == NULL)
        exit(1);
    v = attLeggi(in, &n);
    mergeSort(v, n);
    fclose(in);

    cercaSol(v,n);

    return 0;
}


att *attLeggi(FILE *in, int *n) {
    int i;
    att *v;
    fscanf(in, "%d\n", n);
    v = calloc(*n, sizeof(att));
    for (i=0; i<*n; i++)
        fscanf(in, "%d %d\n", &v[i].s, &v[i].f);
    return v;
}

void mergeSort(att *v, int n) {
    int l=0, r=n-1;
    att *temp;
    temp = calloc(n, sizeof (att));
    mergeSortR(v, temp, l, r);
    free(temp);
}

void mergeSortR (att *v, att *b, int l, int r) {
    int q = (l+r)/2;
    if (l>=r)
        return;
    mergeSortR(v, b, l, q);
    mergeSortR(v, b, q+1, r);
    merge(v, b, l, q, r);
}

void merge(att *v, att *b, int l, int q, int r) {
    int i, j, k;
    i = l;
    j = q+1;
    for (k=l; k<=r; k++) {
        if (i>q)
            b[k] = v[j++];
        else if (j>r)
            b[k] = v[i++];
        else if (v[i].s < v[j].s)
            b[k] = v[i++];
        else if (v[i].s == v[j].s) {
            if (v[i].f < v[j].f)
                b[k] = v[i++];
            else
                b[k] = v[j++];
        }
        else
            b[k] = v[j++];
    }
    for (k=l; k<=r; k++)
        v[k] = b[k];
}

int dA(att a) {
    return a.f - a.s;
}

void cercaSol(att *val, int n) {
    int i, j, ris=1, *L, *P, last=1;
    int durata;
    L = calloc(n, sizeof (int ));
    P = calloc(n, sizeof (int ));
    L[0] = 0;
    P[0] = -1;
    for (i=1; i<n; i++) {
        L[i] = 0;
        P[i] = -1;
        for (j=0; j<i; j++) {
            if (val[i].s >= val[j].f && L[i] < L[j]+ dA(val[j])) {
                L[i] += dA(val[j]);
                P[i] = j;
            }
        }
        if (ris < L[i]) {
            ris = L[i]; last = i;
        }
    }
    printf("Soluzione a durata complessiva massima %d:\n", ris);
    solPrint(val, P, last);
    free(P); free(L);
}

void solPrint(att *val, int *P, int i) {
    if (P[i] == -1) {
        printf("(%d %d) ", val[i].s, val[i].f);
        return;
    }
    solPrint(val, P, P[i]);
    printf("(%d %d) ", val[i].s, val[i].f);
}
