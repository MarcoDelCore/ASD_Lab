
#include "ST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct symboltable {
    char **a;
    char **network_id;
    int maxN;
    int N;
};

ST STinit (int maxN) {
    ST st;
    st = malloc (sizeof *st);
    if (st == NULL) {
        return NULL;
    }
    st->a = calloc(maxN, sizeof (char *));
    st->network_id = calloc(maxN, sizeof (char *));
    st->maxN = maxN;
    st->N = 0;
    return st;
}

void STfree (ST st) {
    int i;
    for (i=0; i<st->N; i++) {
        free(st->a[i]);
        free(st->network_id[i]);
    }
    free(st->a);
    free(st->network_id);
    free(st);
}

int STsize (ST st) {
    return st->N;
}

int STsearch (ST tab, char *label) {
    int i;
    for (i=0; i < tab->N; i++){
        if (strcmp(label, tab->a[i]) == 0)
            return i;
    }
    return -1;
}

void STinsert(ST tab, char *label, char *net_id, int index) {
    tab->a[index] = strdup(label);
    tab->network_id[index] = strdup(net_id);
    tab->N++;
}

char *STsearchByIndex(ST st, int index) {
    if (index<0 || index>=st->N)
        return NULL;
    return st->a[index];
}