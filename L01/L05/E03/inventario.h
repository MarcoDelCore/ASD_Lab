#ifndef E03_INVENTARIO_H
#define E03_INVENTARIO_H

#define MAXN 50

typedef struct {
    int m_hp;
    int m_mp;
    int m_atk;
    int m_def;
    int m_mag;
    int m_spr;
} mod_t;

typedef struct {
    char nome[MAXN];
    char tipo[MAXN];
    mod_t stat;
} inv_t;

typedef struct {
    inv_t *vettInv;
    int nInv;
} tabInv_t;

void creaInventario(tabInv_t *TabInv);
void stampaInventario(tabInv_t *tabInv);
inv_t *cercaOggetto (tabInv_t *tabInv, char nome[MAXN]);
void statOggetto(inv_t *x);

#endif //E03_INVENTARIO_H
