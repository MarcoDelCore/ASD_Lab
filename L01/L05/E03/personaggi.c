#include "personaggi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leggiPersonaggi(tabPg_t *tabPg) {
    FILE *fp;
    pg_t pg;

    if ((fp = fopen("../pg.txt", "r")) == NULL)
        exit(1);

    tabPg->headPg = NULL;
    tabPg->tailPg = NULL;
    tabPg->nPg = 0;
    while ((fscanf(fp, "%c%c%d%s%s%d%d%d%d%d%d\n", &pg.codice.cod[0], &pg.codice.cod[1], &pg.codice.num, pg.nome, pg.classe, &pg.stat.hp, &pg.stat.mp,
                   &pg.stat.atk, &pg.stat.def, &pg.stat.mag, &pg.stat.spr)) != EOF) {
        pg.equip.inUso = 0;
        listIns(&(tabPg->headPg), &(tabPg->tailPg), pg);
        (tabPg->nPg)++;
    }
    fclose(fp);
    stampaLista(tabPg);
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
    printf("\nInserire dati personaggio nel formato:\n");
    printf("<codice> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>");
    scanf("%c%c%d %s %s %d %d %d %d %d %d", &temp.codice.cod[0], &temp.codice.cod[1], &temp.codice.num, temp.nome, temp.classe, &temp.stat.hp,
          &temp.stat.mp, &temp.stat.atk, &temp.stat.def, &temp.stat.mag, &temp.stat.spr);
    temp.equip.inUso = 0;
    listIns(&(tabPg->headPg), &(tabPg->tailPg), temp);
}

void listPop(tabPg_t *tabPg, char src[MAXN]) {
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
    free(x);
    tabPg->nPg--;
}

link cercaPersonaggio(tabPg_t *tabPg, codice_t codice) {
    int i;
    link x = tabPg->headPg;
    for (i=0; i<tabPg->nPg; i++) {
        if (codice.num == x->pg.codice.num) {
            printf("Elemento trovato:\n");
            printf("%c%c%04d %s %s\n", x->pg.codice.cod[0], x->pg.codice.cod[1], x->pg.codice.num, x->pg.nome, x->pg.classe);
            return x;
        }
        x = x->next;
    }
    return NULL;
}

void dettagliPersonaggio (tabPg_t *tabPg, codice_t codice) {
    int i;
    link x;
    x = cercaPersonaggio(tabPg, codice);
    if (x != NULL) {
        printf("Dettagli personaggio %s:\n", x->pg.nome);
        printf("hp: %d\nmp: %d\natk: %d\ndef: %d\nmag: %d\nspr: %d\n", x->pg.stat.hp, x->pg.stat.mp, x->pg.stat.atk,
               x->pg.stat.def, x->pg.stat.mag, x->pg.stat.spr);
        if (x->pg.equip.inUso == 0)
            printf("Nessun equipaggiamento presente.\n");
        else {
            printf("Dettagli equipaggiamento personaggio:\n");
            for (i = 0; i < x->pg.equip.inUso; i++) {
                printf("Caratteristiche oggetto %s:\n", x->pg.equip.vettEq[i]->nome);
                statOggetto(x->pg.equip.vettEq[i]);
            }
        }
    }
}

void modificaEquip(tabPg_t *tabPg, codice_t codice, tabInv_t *tab) {
    link x;
    char nome[MAXN], scelta[MAXN], buff[MAXN];
    inv_t *obj;
    int i, j, found=0;
    x = cercaPersonaggio(tabPg, codice);
    printf("Aggiungere o rimuovere?");
    scanf("%s", scelta);
    if (strcmp(scelta, "aggiungere") == 0){
        if (x->pg.equip.inUso < 8) {
            printf("Inserire nome oggetto da aggiungere:");
            scanf("%s", nome);
            obj = cercaOggetto(tab, nome);
            if (obj != NULL) {
                x->pg.equip.vettEq[x->pg.equip.inUso++] = obj;
                modificaStat(*obj, x);
            }
        }
        else
            printf("Inventario pieno.\n");
    }
    else if (strcmp(scelta, "rimuovere") == 0) {
        if (x->pg.equip.inUso > 0) {
            printf("Inserire nome oggetto da rimuovere:");
            scanf("%s", nome);
            obj = cercaOggetto(tab, nome);
            if (obj != NULL) {
                for (i = 0; i < x->pg.equip.inUso && !found; i++) {
                    if (obj == x->pg.equip.vettEq[i]) {
                        for (j = i; j < x->pg.equip.inUso; j++)
                            x->pg.equip.vettEq[j] = x->pg.equip.vettEq[j + 1];
                        x->pg.equip.inUso--;
                        found = 1;
                    }
                }
                if (!found)
                    printf("Oggetto non presente nell'equipaggiamento del personaggio scelto.\n");
            }
        }
    }
    else
        printf("Comando errato.\n");
}

void modificaStat (inv_t obj, link x) {
    x->pg.stat.hp += obj.stat.m_hp;
    x->pg.stat.mp += obj.stat.m_mp;
    x->pg.stat.atk += obj.stat.m_atk;
    x->pg.stat.def += obj.stat.m_def;
    x->pg.stat.mag += obj.stat.m_mag;
    x->pg.stat.spr += obj.stat.m_spr;
}

void stampaLista (tabPg_t *tabPg) {
    int i;
    link x;
    x = tabPg->headPg;
    for (i = 0; i < tabPg->nPg; i++) {
        printf("%c%c%04d %s %s %d %d %d %d %d %d\n", x->pg.codice.cod[0],x->pg.codice.cod[1], x->pg.codice.num, x->pg.nome, x->pg.classe, x->pg.stat.hp, x->pg.stat.mp,
               x->pg.stat.atk, x->pg.stat.def, x->pg.stat.mag, x->pg.stat.spr);
        x = x->next;
    }
    printf("\n");
}
