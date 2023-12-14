#ifndef E03_PG_H
#define E03_PG_H

#include <stdio.h>
#include "equipArray.h"

#define MAXN 50

typedef struct {
    char cod[2];
    int num;
} codice_t;

typedef struct {
    codice_t codice;
    char nome[MAXN];
    char classe[MAXN];
    tabEquip_t *equip;
    stat_t stat;
} pg_t;

void pg_print(pg_t *pg);
void stat_print(stat_t *stat);
int pg_read(FILE *fp, pg_t *pg);
void pg_equipMod(pg_t *pg, tabInv_t *tabInv);

#endif //E03_PG_H
