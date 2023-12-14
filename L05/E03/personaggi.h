#ifndef E03_PERSONAGGI_H
#define E03_PERSONAGGI_H

#include "inventario.h"

typedef struct nodo *link;

typedef struct {
    int inUso;
    inv_t *vettEq[8];
} tabEquip_t;

typedef struct {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

typedef struct {
    char cod[2];
    int num;
} codice_t;

typedef struct {
    codice_t codice;
    char nome[MAXN];
    char classe[MAXN];
    tabEquip_t equip;
    stat_t stat;
} pg_t;

struct nodo {
    pg_t pg;
    link next;
};

typedef struct {
    link headPg;
    link tailPg;
    int nPg;
} tabPg_t;

void leggiPersonaggi(tabPg_t *tabPg);
link newNode (link next, pg_t pg);
void listIns(link *head, link *tail, pg_t pg);
void pushPg(tabPg_t *tabPg);
void listPop(tabPg_t *tabPg, char src[MAXN]);
link cercaPersonaggio(tabPg_t *tabPg, codice_t codice);
void dettagliPersonaggio (tabPg_t *tabPg, codice_t codice);
void modificaEquip(tabPg_t *tabPg, codice_t codice, tabInv_t *tab);
void modificaStat (inv_t obj, link x);
void stampaLista (tabPg_t *tabPg);

#endif //E03_PERSONAGGI_H
