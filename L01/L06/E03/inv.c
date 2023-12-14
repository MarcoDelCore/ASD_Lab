#include "inv.h"


void inv_print(inv_t *x) {
    printf("Nome: %s Tipo: %s\n", x->nome, x->tipo);
    statOggetto(x);
}

void statOggetto(inv_t *x) {
    printf("hp: %d\nmp: %d\natk: %d\ndef: %d\nmag: %d\nspr: %d\n", x->stat.hp, x->stat.mp, x->stat.atk,
           x->stat.def, x->stat.mag, x->stat.spr);
}