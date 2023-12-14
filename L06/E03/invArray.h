#ifndef E03_INVARRAY_H
#define E03_INVARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inv.h"

#define MAXN 50

typedef struct invArray tabInv_t;

tabInv_t *tabInv_init();
void tabInv_free (tabInv_t *tabInv);
void creaInventario(tabInv_t *tabInv);
void stampaInventario(tabInv_t *tabInv);
int cercaOggetto (tabInv_t *tabInv, char nome[MAXN]);
void invArray_print(tabInv_t *tabInv);
void invArray_print_index(tabInv_t *tabInv, int index);
inv_t cercaOggetto_ByIndex (tabInv_t *tabInv, int index);

#endif //E03_INVARRAY_H
