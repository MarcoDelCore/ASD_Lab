#ifndef E03_PGLIST_H
#define E03_PGLIST_H

#include "pg.h"

typedef struct tabpg tabPg_t;
typedef struct nodo *link;

tabPg_t *tabPg_init();
void tabPg_free (tabPg_t *tabPg);
link newNode (link next, pg_t pg);
void listIns(link *head, link *tail, pg_t pg);
void leggiPersonaggi(tabPg_t *tabPg);
void stampaLista (tabPg_t *tabPg);
void pushPg(tabPg_t *tabPg);
void listPop(tabPg_t *tabPg, char src[MAXN]);
pg_t *cercaPg(tabPg_t *tabPg, codice_t codice);

#endif //E03_PGLIST_H
