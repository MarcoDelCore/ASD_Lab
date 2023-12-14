#include "pg.h"


void pg_print(pg_t *pg) {
    printf("Codice: %c%c%04d\t Nome: %s\tClasse: %s\n", pg->codice.cod[0], pg->codice.cod[1], pg->codice.num, pg->nome, pg->classe);
    stat_print(&pg->stat);
}

void stat_print(stat_t *stat) {
    int stats[6], i;
    stats[0] = stat->hp;
    stats[1] = stat->mp;
    stats[2] = stat->atk;
    stats[3] = stat->def;
    stats[4] = stat->mag;
    stats[5] = stat->spr;
    for (i=0; i<6; i++) {
        if (stats[i]<1)
            stats[i] = 1;
    }
    printf("hp: %d\nmp: %d\natk: %d\ndef: %d\nmag: %d\nspr: %d\n", stat->hp, stat->mp, stat->atk,
           stat->def, stat->mag, stat->spr);
}

int pg_read(FILE *fp, pg_t *pg) {
    pg->equip = equipArray_init();
    if ((fscanf(fp, "%c%c%d%s%s%d%d%d%d%d%d\n", &pg->codice.cod[0], &pg->codice.cod[1], &pg->codice.num, pg->nome, pg->classe, &pg->stat.hp, &pg->stat.mp,
                &pg->stat.atk, &pg->stat.def, &pg->stat.mag, &pg->stat.spr)) != EOF) {
        equipArray_free(pg->equip);
        return 1;
    }
    equipArray_free(pg->equip);
    return 0;
}

void pg_equipMod(pg_t *pg, tabInv_t *tabInv) {
    inv_t obj;
    obj = equipArray_mod(pg->equip, tabInv);
    if (strcmp(obj.nome, "NULL")!=0) {
        pg->stat.hp += obj.stat.hp;
        pg->stat.mp += obj.stat.mp;
        pg->stat.atk += obj.stat.atk;
        pg->stat.def += obj.stat.def;
        pg->stat.mag += obj.stat.mag;
        pg->stat.spr += obj.stat.spr;
    }
}
