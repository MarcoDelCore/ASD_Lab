//
// Created by Marco on 04/02/2022.
//

#include "ST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct symbletable {
    char **id;
    int N;
    int maxN;
};

ST STinit(int maxN) {
    ST st = malloc(sizeof (*st));
    st->id = malloc(maxN*sizeof (char *));
    st->N = 0;
    st->maxN = maxN;
    return st;
}

void STfree(ST st) {
    int i;
    for (i=0; i<st->maxN; i++) {
        free(st->id[i]);
    }
    free(st->id);
    free(st);
}

int STsearch (ST st, char *id) {
    int i;
    for (i=0; i<st->N; i++) {
        if (strcmp(st->id[i], id) == 0)
            return i;
    }
    return -1;
}

void STinsert (ST st, char *id) {
    st->id[(st->N)++] = strdup(id);
}

char *STsearchByIndex (ST st, int index) {
    return st->id[index];
}