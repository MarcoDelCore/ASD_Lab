//
// Created by Marco on 03/02/2022.
//

#ifndef E01_DATI_H
#define E01_DATI_H


typedef struct {
    int anno;
    int mese;
    int giorno;
} data_t;

typedef struct {
    int ora;
    int minuti;
} ora_t;

data_t dataTitolo (char *d);
ora_t oraTitolo (char *s);
int datacmp (data_t data1, data_t data2);

#endif //E01_DATI_H
