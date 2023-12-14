//
// Created by Marco on 04/02/2022.
//

#ifndef E01_ST_H
#define E01_ST_H

typedef struct symbletable *ST;

void STfree(ST st);
ST STinit(int maxN);
int STsearch (ST st, char *id);
void STinsert (ST st, char *id);
char *STsearchByIndex (ST st, int index);

#endif //E01_ST_H
