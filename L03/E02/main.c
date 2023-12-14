#include <stdio.h>
#include <stdlib.h>

#define MAX 255

typedef struct {
    int n_canzoni;
    char **nome;
} t_canzoni;

char **malloc2dR (int nr);
int trovaSoluzioni(int pos, t_canzoni *livelli, int n, char** sol, int count);
void freeMalloc (char **m, int nr);

int main() {
    int n_amici, i, j, sol = 1;
    t_canzoni *vet;
    char **playlist;
    FILE *fp;

    if ((fp = fopen("C:/Users/ASUS/Desktop/PoliTo/II Anno/I Semestre/Algoritmi e Strutture Dati/Projects/L03/E02/brani.txt", "r")) == NULL) {
        printf("Errore apertura file.\n");
        return -1;
    }

    fscanf(fp, "%d", &n_amici);
    vet = malloc(n_amici*sizeof (t_canzoni));
    playlist = malloc(n_amici * sizeof(char *));

    for (i=0; i<n_amici; i++) {
        fscanf(fp, "%d", &vet[i].n_canzoni);
        vet[i].nome = malloc2dR(vet[i].n_canzoni);
        sol = sol * vet[i].n_canzoni;
        for (j=0; j<vet[i].n_canzoni; j++) {
            fscanf(fp, "%s", vet[i].nome[j]);
        }
    }
    printf("E' possibile generare %d playlist.\n", sol);
    printf("%d playlist possibili generate.\n", trovaSoluzioni(0, vet, n_amici, playlist, 0));

    for (i=0; i<n_amici; i++) {
        freeMalloc(vet[i].nome, vet[i].n_canzoni);
    }
    free(playlist);

    return 0;
}

char **malloc2dR (int nr) {
    char **m;
    int i;
    m = malloc(nr * sizeof (char *));
    for (i=0; i<nr; i++)
        m[i] = malloc (MAX * sizeof (char));
    return m;
}

void freeMalloc (char **m, int nr) {
    int i;
    for (i=0; i<nr; i++) {
        free(m[i]);
    }
    free(m);
}

int trovaSoluzioni(int pos, t_canzoni *livelli, int n, char** sol, int count){
    int i;
    if(pos >= n){
        printf("Playlist possibile n. %d: \n", ++count);
        for(i = 0; i < n; i++){
            printf("\tAmico %d:  %s\n", i+1, sol[i]);
        }
        return count ;
    }

    for(i = 0; i < livelli[pos].n_canzoni; i++){
        sol[pos] = livelli[pos].nome[i];
        count = trovaSoluzioni(pos+1, livelli, n, sol, count);
    }
    return count;
}
