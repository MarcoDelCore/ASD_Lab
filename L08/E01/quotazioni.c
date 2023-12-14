//
// Created by Marco on 03/02/2022.
//

#include "quotazioni.h"
#include "titoli.h"
#include "dati.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct nodo *link;

struct nodo {
    quotazione_t quotazione;
    link l, r;
    int n;
};

struct BSTquotazioni_ {
    link root;
    int count;
    link z;
};

BSTquotazioni BSTinit() {
    BSTquotazioni t = malloc(sizeof(*t));
    t->count = 0;
    t->root = NULL;
    t->z = NULL;
    return t;
}

quotazione_t quotazioneNEW (data_t d) {
    quotazione_t t;
    t.data = d;
    t.val = 0;
    t.q = 0;
    return t;
}

int quotazioneCheckNull (quotazione_t t) {
    return (t.q == 0);
}

quotazione_t quotazioneSetNull() {
    quotazione_t t = {{-1, -1, -1}, 0.0, 0};
    return t;
}

data_t dataQuotazione (quotazione_t t) {
    if (quotazioneCheckNull(t))
        return quotazioneSetNull().data;
    return t.data;
}

float valQuotazione (quotazione_t t) {
    if (quotazioneCheckNull(t))
        return -1.0;
    return t.val/(float)t.q;
}

static link NEW (data_t data, float val, int qta, link l, link r) {
    link x = malloc(sizeof(*x));
    x->quotazione.data = data;
    x->quotazione.q = qta;
    x->quotazione.val = val*(float)qta;
    x->l = l;
    x->r = r;
    x->n = 1;
    return x;
}

static link insertR (link root, data_t data, float val, int qta) {
    if (root == NULL)
        return NEW(data, val, qta, NULL, NULL);
    if (datacmp(data, dataQuotazione(root->quotazione))<0)
        root->l = insertR(root->l, data, val, qta);
    else if (datacmp(data, dataQuotazione(root->quotazione))>0)
        root->r = insertR(root->r, data, val, qta);
    else {
        root->quotazione.val += qta*val;
        root->quotazione.q += qta;
    }
    (root->n)++;
    return root;
}

void BSTinsertQuotazione (BSTquotazioni bst, data_t data, float val, int qta) {
    bst->root = insertR(bst->root, data, val, qta);
    bst->count++;
}

static quotazione_t BSTsearchR(link root, data_t data) {
    int cmp;
    if (root == NULL) {
        return quotazioneSetNull();
    }
    cmp = datacmp(data, root->quotazione.data);
    if (cmp == 0)
        return root->quotazione;
    if (cmp<0) {
        return BSTsearchR(root->l, data);
    }
    return BSTsearchR(root->r, data);
}

quotazione_t BSTquotazioneSearch (BSTquotazioni bst, data_t data) {
    return BSTsearchR(bst->root, data);
}

static void BSTsearchMinMaxR (link root, float *min, float *max) {
    float val = valQuotazione(root->quotazione);
    if (*min<0 || val<*min)
        *min = val;
    if (*max<0 || val>*max)
        *max = val;
    if (root->l)
        BSTsearchMinMaxR(root->l, min, max);
    if (root->r)
        BSTsearchMinMaxR(root->r, min, max);
}

void BSTsearchMinMax (BSTquotazioni bst, float *min, float *max) {
    if (bst->root == NULL)
        return;
    BSTsearchMinMaxR(bst->root, min, max);
}

