#include <stdio.h>
#include "dati.h"
#include "titoli.h"
#include "quotazioni.h"

int main() {
    return 0;
}


void leggiFile (FILE *fp, titoli_t titoli) {
    int i, n, qta, n_tot, j;
    float val;
    char cod[21], data[11], ora[6];
    titolo_t t;

    fscanf(fp, "%d", &n_tot);
    for (i = 0; i < n_tot; i++) {
        fscanf(fp, "%s %d\n", cod, &n);
        t = titoliSearch(cod, titoli);
        if (t == NULL) {
            t = titoloNew(cod);
            titoliInsert(titoli, t);
        }
        for (j=0; j<n; j++) {
            fscanf(fp, "%s %s %f %d", data, ora, &val, &qta);

    }

}
