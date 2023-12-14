#ifndef E03_INV_H
#define E03_INV_H

#include <stdio.h>

#define MAXN 50

typedef struct {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

typedef struct {
    char nome[MAXN];
    char tipo[MAXN];
    stat_t stat;
} inv_t;

void statOggetto(inv_t *x);
void inv_print(inv_t *x);

#endif //E03_INV_H
