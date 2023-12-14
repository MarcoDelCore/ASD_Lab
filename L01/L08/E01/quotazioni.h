//
// Created by Marco on 03/02/2022.
//

#ifndef E01_QUOTAZIONI_H
#define E01_QUOTAZIONI_H


#include "dati.h"

typedef struct {
    data_t data;
    float val;
    int q;
} quotazione_t;

typedef struct BSTquotazioni_ *BSTquotazioni;

BSTquotazioni BSTinit();
quotazione_t quotazioneNEW (data_t d) ;
void BSTinsertQuotazione (BSTquotazioni bst, data_t data, float val, int qta);
int quotazioneCheckNull (quotazione_t t);
data_t dataQuotazione (quotazione_t t);
quotazione_t quotazioneSetNull();
float valQuotazione (quotazione_t t);
quotazione_t BSTquotazioneSearch (BSTquotazioni bst, data_t data);
void BSTsearchMinMax (BSTquotazioni bst, float *min, float *max);

#endif //E01_QUOTAZIONI_H
