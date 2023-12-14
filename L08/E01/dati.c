//
// Created by Marco on 03/02/2022.
//

#include "dati.h"
#include <stdio.h>
#include <stdlib.h>

data_t dataTitolo (char *d) {
    data_t data;
    sscanf(d, "%d/%d/%d", &data.anno, &data.mese, &data.giorno);
    return data;
}

ora_t oraTitolo (char *s) {
    ora_t ora;
    sscanf(s, "%d:%d", &ora.ora, &ora.minuti);
    return ora;
}

int datacmp (data_t data1, data_t data2) {
    if (data1.anno == data2.anno) {
        if (data1.mese == data2.mese) {
            if (data1.giorno == data2.giorno)
                return 0;
            if (data1.giorno < data2.giorno)
                return -1;
            return 1;
        }
        if (data1.mese < data2.mese)
            return -1;
        else
            return 1;
    }
    if (data1.anno < data2.anno)
        return -1;
    return 1;
}
