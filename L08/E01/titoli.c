//
// Created by Marco on 03/02/2022.
//

#include "titoli.h"
#include "dati.h"
#include "quotazioni.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo *link;

struct nodo {
    titolo_t titolo;
    link next;
};

struct titolo {
    char *cod;
    float min, max;
    BSTquotazioni bst;
};

struct titoli {
    link head;
    int n;
};

titoli_t titoliInit() {
    titoli_t t = malloc(sizeof (*t));
    t->head = NULL;
    t->n = 0;
    return t;
}

void titoliFree (titoli_t t) {
    link h = t->head;
    while (h != NULL) {
        h = t->head;
        t->head = t->head->next;
        free(h);
    }
}

titolo_t titoloSetVoid() {
    titolo_t t = malloc(sizeof (titolo_t));
    strcpy(t->cod, "NULL");
    return t;
}

titolo_t titoliSearch(char *cod, titoli_t titoli) {
    link x;
    for (x = titoli->head; x!=NULL; x=x->next) {
        if (strcmp(x->titolo->cod, cod) == 0)
            return x->titolo;
    }
    return NULL;
}

titolo_t titoloNew (char *cod) {
    titolo_t t = malloc(sizeof (*t));
    t->cod = strdup(cod);
    t->min = t->max = -1.0;
    t->bst = BSTinit();
    return t;
}

static link NEWnode (titolo_t titolo, link next) {
    link x = malloc(sizeof(*x));
    x->titolo = titolo;
    x->next = next;
    return x;
}

static link listInsert (link head, titolo_t titolo) {
    link x, p;
    if (head == NULL || strcmp(head->titolo->cod, titolo->cod)<0) {
        return NEWnode(titolo, NULL);
    }
    for (x = head->next, p = head; x != NULL && strcmp(x->titolo->cod, titolo->cod)>0; p = x, x = x->next);
    p->next = NEWnode(titolo, x);
    return head;
}

void titoliInsert(titoli_t titoli, titolo_t titolo) {
    titoli->head = listInsert(titoli->head, titolo);
    titoli->n++;
}


char *getKey (titolo_t t) {
    return t->cod;
}

void insertTransazione (titolo_t t, data_t data, float val, int qta) {
    BSTinsertQuotazione(t->bst, data, val, qta);
    //updateMinMax(t);
}

void bilanciaBST (titolo_t t, int s) {
    int diff;
    if ((diff = BTSgetDiff(t->bst)) > s) {
        printf("Bilancio il BST. %d\n", diff);
        BSTbalance(t->bst);
    }
    printf("Il BST non necessita bilanciamneto, diff = %d", diff);
}