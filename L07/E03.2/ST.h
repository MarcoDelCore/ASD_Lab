//
// Created by ASUS on 26/01/2022.
//

#ifndef E03_2_ST_H
#define E03_2_ST_H

typedef struct symboltable *ST;

ST STinit (int maxN);
void STfree(ST st);
int STsize (ST st);
int STsearch (ST tab, char *label);
void STinsert(ST tab, char *label, char *net_id, int index);
char *STsearchByIndex(ST st, int index);


#endif //E03_2_ST_H
