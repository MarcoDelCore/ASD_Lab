#ifndef E03_EQUIPARRAY_H
#define E03_EQUIPARRAY_H

#include <stdio.h>
#include <stdlib.h>

#include "invArray.h"

typedef struct tabEquip tabEquip_t;

tabEquip_t *equipArray_init();
void equipArray_free (tabEquip_t *tabEquip);
void equipArray_print(tabEquip_t *equipArray, tabInv_t *invArray);
inv_t equipArray_mod (tabEquip_t *tabEquip, tabInv_t *tabInv);

#endif //E03_EQUIPARRAY_H
