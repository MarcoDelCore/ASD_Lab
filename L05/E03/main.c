#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "personaggi.h"

#define MAXN 50

typedef enum {
    r_aggiungi, r_elimina, r_modifica, r_dettagli, r_fine, r_err
} comando_e;

comando_e leggiComando();
void menuComandi (tabPg_t *tabPg, tabInv_t *tabInv, comando_e cmd);

int main() {
    tabInv_t tabInv;
    tabPg_t tabPg;
    creaInventario(&tabInv);
    leggiPersonaggi(&tabPg);
    menuComandi(&tabPg, &tabInv, leggiComando());
    return 0;
}

comando_e leggiComando(){
    comando_e c;
    char cmd[21];
    char *tabella[r_err] = {"aggiungi", "elimina", "modifica_equip", "dettagli_equip", "fine"};
    int i;
    printf("Inserire comando (aggiungi/elimina/modifica_equip/dettagli_equip/fine): ");
    scanf("%s", cmd);
    for (i = 0; cmd[i] != '\0'; i++)
        cmd[i] = tolower(cmd[i]);
    c = r_aggiungi;
    while (c < r_err && strcmp(cmd, tabella[c]) != 0)
        c++;
    return (c);
}

void menuComandi (tabPg_t *tabPg, tabInv_t *tabInv, comando_e cmd) {
    int continua = 1;
    char src[MAXN];
    codice_t codice;
    while (continua) {
        switch (cmd) {
            case r_aggiungi:
                pushPg(tabPg);
                cmd = leggiComando();
                break;
            case r_elimina:
                printf("\nInserire nome personaggio:");
                scanf("%s", src);
                listPop(tabPg, src);
                cmd = leggiComando();
                break;
            case r_modifica:
                printf("\nAggiungi o rimuovi un oggetto dall'equipaggiamento di un personaggio.\n");
                printf("Inserire codice personaggio da modificare:");
                scanf("\n%c%c%d", &codice.cod[0], &codice.cod[1], &codice.num);
                modificaEquip(tabPg, codice, tabInv);
                cmd = leggiComando();
                break;
            case r_dettagli:
                printf("Inserire codice personaggio per mostrare dettagli:");
                scanf("\n%c%c%d", &codice.cod[0], &codice.cod[1], &codice.num);
                dettagliPersonaggio(tabPg, codice);
                cmd = leggiComando();
                break;
            case r_fine:
                continua = 0;
                break;
            case r_err:
            default:
                printf("comando errato\n");
                cmd = leggiComando();
                break;
        }
    }
}