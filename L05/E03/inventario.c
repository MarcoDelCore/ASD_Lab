#include "inventario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void creaInventario(tabInv_t *tabInv) {
    FILE *fp;
    int i;

    if ((fp = fopen("../inventario.txt", "r")) == NULL)
        exit(1);

    fscanf(fp, "%d", &tabInv->nInv);
    tabInv->vettInv = malloc(tabInv->nInv * sizeof (inv_t));

    for (i=0; i < tabInv->nInv; i++) {
        fscanf(fp, "%s%s%d%d%d%d%d%d", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipo, &tabInv->vettInv[i].stat.m_hp, &tabInv->vettInv[i].stat.m_mp,
               &tabInv->vettInv[i].stat.m_atk, &tabInv->vettInv[i].stat.m_def, &tabInv->vettInv[i].stat.m_mag, &tabInv->vettInv[i].stat.m_spr);
    }
    fclose(fp);
    stampaInventario(tabInv);
}

void stampaInventario(tabInv_t *tabInv) {
    for (int i=0; i < tabInv->nInv; i++) {
        printf("%s %s %d %d %d %d %d %d\n", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipo, tabInv->vettInv[i].stat.m_hp,
               tabInv->vettInv[i].stat.m_mp, tabInv->vettInv[i].stat.m_atk, tabInv->vettInv[i].stat.m_def,
               tabInv->vettInv[i].stat.m_mag, tabInv->vettInv[i].stat.m_spr);
    }
    printf("\n");
}

inv_t *cercaOggetto (tabInv_t *tabInv, char nome[MAXN]) {
    int i;
    for (i=0; i<tabInv->nInv; i++) {
        if (strcmp(nome, tabInv->vettInv[i].nome) == 0) {
            printf("Elemento trovato: ");
            printf("%s %s\n", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipo);
            return &(tabInv->vettInv[i]);
        }
    }
    printf("Nessun elemento trovato.\n");
    return NULL;
}

void statOggetto(inv_t *x) {
    printf("hp: %d\nmp: %d\natk: %d\ndef: %d\nmag: %d\nspr: %d\n", x->stat.m_hp, x->stat.m_mp, x->stat.m_atk,
           x->stat.m_def, x->stat.m_mag, x->stat.m_spr);
}
