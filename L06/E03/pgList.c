#include "pgList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pg.h"

struct nodo {
    pg_t pg;
    link next;
};

struct tabpg {
    link headPg;
    link tailPg;
    int nPg;
};

tabPg_t *tabPg_init() {
    tabPg_t *temp;
    temp = malloc(sizeof *temp);
    temp->nPg = 0;
    temp->headPg = NULL;
    temp->tailPg = NULL;
    return temp;
}

void tabPg_free (tabPg_t *tabPg) {
    link x, p;
    for (x=tabPg->headPg->next, p=tabPg->headPg; x!=tabPg->tailPg->next; p=x, x=x->next) {
        equipArray_free(p->pg.equip);
        free(p);
    }
    free(tabPg);
}

void leggiPersonaggi(tabPg_t *tabPg) {
    FILE *fp;
    pg_t pg;

    if ((fp = fopen("../pg.txt", "r")) == NULL)
        exit(1);

    while (pg_read(fp, &pg)) {
        pg.equip = equipArray_init();
        listIns(&(tabPg->headPg), &(tabPg->tailPg), pg);
        (tabPg->nPg)++;
        equipArray_free(pg.equip);
    }
    fclose(fp);
}


link newNode (link next, pg_t pg) {
    link x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->pg = pg;
        x->next = next;
    }
    return x;
}

void listIns(link *head, link *tail, pg_t pg) {
    if (*head == NULL)
        *head = *tail = newNode(NULL, pg);
    else {
        (*tail)->next = newNode(NULL, pg);
        *tail = (*tail)->next;
    }
}

void pushPg(tabPg_t *tabPg) {
    pg_t temp;
    temp.equip = equipArray_init();
    printf("\nInserire dati personaggio nel formato:\n");
    printf("<codice> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>");
    scanf("%c%c%d %s %s %d %d %d %d %d %d", &temp.codice.cod[0], &temp.codice.cod[1], &temp.codice.num, temp.nome, temp.classe, &temp.stat.hp,
          &temp.stat.mp, &temp.stat.atk, &temp.stat.def, &temp.stat.mag, &temp.stat.spr);
    listIns(&(tabPg->headPg), &(tabPg->tailPg), temp);
    equipArray_free(temp.equip);
}

void listPop(tabPg_t *tabPg, char *src) {
    link x, p;
    int i, found=0;
    x = tabPg->headPg;
    p = NULL;
    for (i=0; i<tabPg->nPg; i++) {
        if (strcmp(src, x->pg.nome)==0)
            found = 1;
        p = x;
        x = x->next;
        if (found)
            break;
    }
    if (found == 0) {
        printf("Nessun elemento da cancellare trovato.\n");
        return;
    }
    if (x == tabPg->headPg)
        tabPg->headPg = tabPg->headPg->next;
    else if (x == NULL)
        tabPg->tailPg = p;
    else
        p->next = x->next;
    equipArray_free(x->pg.equip);
    free(x);
    tabPg->nPg--;
}

void stampaLista (tabPg_t *tabPg) {
    int i;
    link x;
    x = tabPg->headPg;
    for (i = 0; i < tabPg->nPg; i++) {
        x->pg.equip = equipArray_init();
        pg_print(&x->pg);
        equipArray_init(x->pg.equip);
        x = x->next;
    }
}

pg_t *cercaPg(tabPg_t *tabPg, codice_t codice) {
    link x;
    for (x = tabPg->headPg; x!= NULL; x = x->next) {
        if (codice.num == x->pg.codice.num)
            return &x->pg;
    }
    return NULL;
}
