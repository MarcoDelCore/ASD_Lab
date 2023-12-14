#include "invArray.h"

struct invArray {
    inv_t *vettInv;
    int nInv;
};

tabInv_t *tabInv_init() {
    tabInv_t *temp;
    temp = malloc(sizeof *temp);
    temp->nInv = 0;
    return temp;
}

void tabInv_free (tabInv_t *tabInv) {
    free(tabInv->vettInv);
    free(tabInv);
}

void creaInventario(tabInv_t *tabInv) {
    FILE *fp;
    int i;

    if ((fp = fopen("../inventario.txt", "r")) == NULL)
        exit(1);

    fscanf(fp, "%d", &tabInv->nInv);
    tabInv->vettInv = malloc(tabInv->nInv * sizeof (inv_t));

    for (i=0; i < tabInv->nInv; i++) {
        fscanf(fp, "%s%s%d%d%d%d%d%d", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipo, &tabInv->vettInv[i].stat.hp, &tabInv->vettInv[i].stat.mp,
               &tabInv->vettInv[i].stat.atk, &tabInv->vettInv[i].stat.def, &tabInv->vettInv[i].stat.mag, &tabInv->vettInv[i].stat.spr);
    }
    fclose(fp);
}

void stampaInventario(tabInv_t *tabInv) {
    for (int i=0; i < tabInv->nInv; i++) {
        printf("%s %s %d %d %d %d %d %d\n", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipo, tabInv->vettInv[i].stat.hp,
               tabInv->vettInv[i].stat.mp, tabInv->vettInv[i].stat.atk, tabInv->vettInv[i].stat.def,
               tabInv->vettInv[i].stat.mag, tabInv->vettInv[i].stat.spr);
    }
    printf("\n");
}

int cercaOggetto (tabInv_t *tabInv, char *nome) {
    int i;
    for (i=0; i<tabInv->nInv; i++) {
        if (strcmp(nome, tabInv->vettInv[i].nome) == 0) {
            printf("Elemento trovato: ");
            printf("%s %s\n", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipo);
            return i;
        }
    }
    printf("Nessun elemento trovato.\n");
    return -1;
}

void invArray_print(tabInv_t *tabInv) {
    int i;
    printf("Inventario:\n");
    for (i=0; i<tabInv->nInv; i++)
        inv_print(&tabInv->vettInv[i]);
}

void invArray_print_index(tabInv_t *tabInv, int index) {
    inv_print(&tabInv->vettInv[index]);
}

inv_t cercaOggetto_ByIndex (tabInv_t *tabInv, int index) {
    return tabInv->vettInv[index];
}