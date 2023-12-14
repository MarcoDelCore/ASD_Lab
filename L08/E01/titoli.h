//
// Created by Marco on 03/02/2022.
//

#ifndef E01_TITOLI_H
#define E01_TITOLI_H

typedef struct titolo *titolo_t;
typedef struct titoli *titoli_t;

titoli_t titoliInit();
void titoliFree (titoli_t t);
titolo_t titoloSetVoid();
titolo_t titoliSearch(char *cod, titoli_t titoli);
titolo_t titoloNew (char *cod);
void titoliInsert(titoli_t titoli, titolo_t titolo);


#endif //E01_TITOLI_H
