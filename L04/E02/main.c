#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50

typedef struct {
    int giorno, mese, anno;
} s_data;

typedef struct {
    char c;
    int num;
} s_codice;

typedef struct {
    s_codice codice;
    char nome[MAXN];
    char cognome[MAXN];
    s_data data;
    char via[MAXN];
    char citta[MAXN];
    int cap;
} Item;

typedef struct node {
    Item val;
    struct node *next;
} *link;

typedef enum {
    Inserire_dato, Ricerca_dato, Cancellazione_dato, Stampa_lista, Fine, Errore
} e_comando;

e_comando scegliComando();
link menuParola(link h, e_comando comando);
void stampaLista(link h);
Item ricercaElemento (link h, s_codice cod);
link leggiListaOrdinata(link head);
link newNode(Item val, link next);
int compara_data (s_data data1, s_data data2);
link sortListIns(link h, Item val);
int comparaCodice (s_codice cod1, s_codice cod2);
Item ITEMsetvoid();
int isVoid(Item item);
Item listExtrKeyP_codice(link *hp, s_codice k);
Item listExtrKeyP_date(link *hp, s_data data1, s_data data2);

int main() {
    link head = NULL;
    char buff[MAXN];
    e_comando comando;

    head = leggiListaOrdinata(head);

    printf("Menu opzioni:\n-Inserire_dato\n-Ricerca_dato\n-Cancellazione_dato\n-Stampa_lista\n-Fine\n");
    gets(buff);
    comando = scegliComando();
    do {
        if (comando==Errore) {
            printf("Comando errato.\n");
        }
        else {
            head = menuParola(head, comando);
            gets(buff);
        }
        comando = scegliComando();
    } while (comando!=Fine);

    return 0;
}

e_comando scegliComando() {
    char tab[Errore][MAXN] = {"Inserire_dato", "Ricerca_dato", "Cancellazione_dato", "Stampa_lista", "Fine"};
    char comando[MAXN];
    e_comando c;
    printf("Inserire comando:");
    gets(comando);
    c =Inserire_dato;
    while (c<Errore && strcmp(comando, tab[c])!=0)
        c++;
    return c;
}

link menuParola(link h, e_comando comando) {
    char buff[MAXN];
    switch (comando) {
        case Inserire_dato: {
            char c;
            printf("Acquisizione da FILE (F) o da tastiera (T)?");
            scanf("%c", &c);
            if (c == 'F') {
                h = leggiListaOrdinata(h);
            } else {
                Item val;
                gets(buff);
                printf("Inserire dati:");
                scanf("%c%d%s%s%d/%d/%d%s%s%d", &val.codice.c, &val.codice.num, val.nome, val.cognome, &val.data.giorno,
                      &val.data.mese, &val.data.anno,
                      val.via, val.citta, &val.cap);
                h = sortListIns(h, val);
            }
            break;
        }
        case Ricerca_dato: {
            s_codice cod;
            Item item;
            printf("Inserire codice per ricerca:");
            scanf("%c%d", &cod.c, &cod.num);
            item = ricercaElemento(h, cod);
            if (!isVoid(item)) {
                printf("L'elemento cercato e':\n");
                printf("%c%04d %s %s %02d/%02d/%d %s %s %05d\n", item.codice.c, item.codice.num, item.nome,
                       item.cognome, item.data.giorno,
                       item.data.mese, item.data.anno, item.via, item.citta, item.cap);
            } else
                printf("Nessun elemento corrispondente trovato.\n");
            break;
        }
        case Cancellazione_dato: {
            Item item;
            char c;
            printf("Canzellazione per codice(C) o per date(D)?");
            scanf("%c", &c);
            gets(buff);
            if (c=='C') {
                s_codice cod;
                printf("Inserire codice per cancellazione:");
                scanf("%c%d", &cod.c, &cod.num);
                item = listExtrKeyP_codice(&h, cod);
                if (!isVoid(item)) {
                    printf("L'elemento estratto e cacellato e':\n");
                    printf("%c%04d %s %s %02d/%02d/%d %s %s %05d\n", item.codice.c, item.codice.num, item.nome,
                           item.cognome, item.data.giorno,
                           item.data.mese, item.data.anno, item.via, item.citta, item.cap);
                }
                else
                    printf("Nessun elemento corrispondente trovato.\n");
                }
            else {
                s_data d1, d2;
                printf("Inserire intervallo date in formato gg/mm/aaaa:");
                scanf("%d/%d/%d%d/%d/%d", &d1.giorno, &d1.mese, &d1.anno, &d2.giorno, &d2.mese, &d2.anno);
                while (!isVoid(item = listExtrKeyP_date(&h, d1, d2))) {
                    printf("L'elemento estratto e cacellato e':\n");
                    printf("%c%04d %s %s %02d/%02d/%d %s %s %05d\n", item.codice.c, item.codice.num, item.nome,
                           item.cognome, item.data.giorno,
                           item.data.mese, item.data.anno, item.via, item.citta, item.cap);
                }
            }
            break;
        }
        case Stampa_lista: {
            stampaLista(h);
        }
    }
    return h;
}

link leggiListaOrdinata(link head) {
    Item val;
    FILE *fp;
    char nome_file[MAXN];

    printf("Inserire nome file per acquisizione dato:");
    scanf("%s", nome_file);
    if ((fp = fopen(nome_file, "r")) == NULL)
        exit(1);
    while ((fscanf(fp, "%c%d%s%s%d/%d/%d%s%s%d\n", &val.codice.c, &val.codice.num, val.nome, val.cognome, &val.data.giorno, &val.data.mese, &val.data.anno,
                   val.via, val.citta, &val.cap)) != EOF) {
        head = sortListIns(head, val);
    }
    fclose(fp);
    return head;
}

link sortListIns(link h, Item val) {
    link x, p;
    s_data k = val.data;
    if (h==NULL || compara_data(h->val.data, k)<0)
        return newNode(val, h);
    for (x=h->next, p=h; x!=NULL && compara_data(x->val.data, k)>0; p=x, x=x->next);
    p->next = newNode(val, x);
    return h;
}

int compara_data (s_data data1, s_data data2) {
    if (data1.anno != data2.anno)
        return (data1.anno-data2.anno);
    else if (data1.mese != data2.mese)
        return (data1.mese-data2.mese);
    else if (data1.giorno != data2.giorno)
        return (data1.giorno-data2.giorno);
    else return 0;
}

link newNode(Item val, link next) {
    link x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    x->val = val;
    x->next = next;
    return x;
}

void stampaLista(link h) {
    FILE *fp;
    link x;
    char output[MAXN];
    printf("Inserire nome file output:");
    scanf("%s", output);
    if ((fp = fopen(output, "w")) == NULL)
        exit(2);
    for (x = h; x!=NULL; x=x->next)
        fprintf(fp,"%c%04d %s %s %02d/%02d/%d %s %s %05d\n", x->val.codice.c,x->val.codice.num, x->val.nome, x->val.cognome, x->val.data.giorno,
                x->val.data.mese, x->val.data.anno, x->val.via, x->val.citta, x->val.cap);
    fclose(fp);
}

Item ricercaElemento (link h, s_codice cod) {
    Item i = ITEMsetvoid();
    link x;
    int found=0;
    for (x=h; x!=NULL && found==0; x = x->next) {
        if (comparaCodice(cod, x->val.codice)) {
            i=x->val;
            found=1;
        }
    }
    return i;
}

int comparaCodice (s_codice cod1, s_codice cod2) {
    if (cod1.c == cod2.c && cod1.num == cod2.num)
        return 1;
    return 0;
}

Item ITEMsetvoid() {
    Item t;
    strcpy(t.citta, "\0");
    return t;
}

int isVoid(Item item) {
    if (strcmp(item.citta, "\0")==0) {
        return 1;
    }
    return 0;
}

Item listExtrKeyP_codice(link *hp, s_codice k) {
    link *xp, t;
    Item i = ITEMsetvoid();
    for (xp = hp; (*xp) != NULL; xp = &((*xp)->next)) {
        if (comparaCodice((*xp)->val.codice, k)){
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}

Item listExtrKeyP_date(link *hp, s_data data1, s_data data2) {
    link *xp, t;
    Item i = ITEMsetvoid();
    for (xp = hp; (*xp) != NULL; xp = &((*xp)->next)) {
        if (compara_data((*xp)->val.data, data1)>=0 && compara_data((*xp)->val.data, data2)<=0){
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}