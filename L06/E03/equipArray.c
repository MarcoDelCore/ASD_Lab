#include "equipArray.h"

struct tabEquip {
    int inUso;
    int vettEq[8];
};

tabEquip_t *equipArray_init() {
    int i;
    tabEquip_t *temp;
    temp = malloc(sizeof *temp);
    temp->inUso = 0;
    for (i=0; i<8; i++) {
        temp->vettEq[i] = -1;
    }
    return temp;
}

void equipArray_free (tabEquip_t *tabEquip) {
    free(tabEquip);
}

void equipArray_print(tabEquip_t *equipArray, tabInv_t *invArray) {
    int i;
    if (equipArray->inUso == 0) {
        printf("\nNessun oggetto equipaggiato.\n");
        return;
    }
    printf("\nOggetti equipaggiati:\n");
    for (i = 0; i < equipArray->inUso; i++) {
        printf("%d.\t", i + 1);
        invArray_print_index(invArray, equipArray->vettEq[i]);
    }
}

inv_t equipArray_mod (tabEquip_t *tabEquip, tabInv_t *tabInv) {
    inv_t obj;
    int i;
    char name[MAXN];
    if (tabEquip->inUso < 8) {
        invArray_print(tabInv);
        equipArray_print(tabEquip, tabInv);
        printf("Inserire nome oggetto da equipaggiare:");
        scanf("%s", name);
        i = cercaOggetto(tabInv, name);
        if (i != -1) {
            tabEquip->vettEq[tabEquip->inUso] = i;
            obj = cercaOggetto_ByIndex(tabInv, i);
            tabEquip->inUso++;
            return obj;
        }
    }
    else
        printf("Inventario pieno!\n");
    strcpy(obj.nome, "NULL");
    return obj;
}
