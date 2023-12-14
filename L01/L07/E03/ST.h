//
// Created by ASUS on 13/01/2022.
//

#ifndef E03_ST_H
#define E03_ST_H

typedef struct symboltable *ST;

ST STinit(int maxN);

void STfree(ST st);

int STsize(ST st);

void STinsert(ST st, char *str, char *network_id, int i);

int STsearch(ST st, char *str);

char *STsearchByIndex(ST st, int i);

#endif //E03_ST_H
