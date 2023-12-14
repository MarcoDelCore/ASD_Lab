#include <stdio.h>
#include <stdlib.h>

#define MAXN 31

int **malloc2dR (int nr, int nc);
void leggiMatrice (int **mat, int nr, int nc, FILE *fp);
void separa (int **mat, int nr, int nc, int *bianco, int *nero);

int main() {
    FILE *fp;
    int nr, nc, i;
    char name[MAXN];
    int **mat;
    int *bianco, *nero;

    printf("Inserire nome file:");
    scanf("%s", name);
    if ((fp = fopen(name, "r")) == NULL ) {
        exit(1);
    }
    fscanf(fp, "%d %d", &nr, &nc);

    mat = malloc2dR(nr, nc);

    leggiMatrice(mat, nr, nc, fp);

    bianco = malloc ((nr*nc)/2 * sizeof (int));
    nero = malloc (((nr*nc)/2+1) * sizeof (int));

    separa(mat, nr, nc, bianco, nero);

    printf("Celle bianche:\n");
    for (i=0; i<(nr*nc)/2; i++) {
        printf("%d ", bianco[i]);
    }

    printf("\nCelle nere:\n");
    for (i=0; i<(nr*nc)/2+1; i++) {
        printf("%d ", nero[i]);
    }

    free(bianco);
    free(nero);
    for (i=0; i<nr; i++)
        free(mat[i]);
    free(mat);
    fclose(fp);
}

int **malloc2dR (int nr, int nc) {
    int **m;
    int i;
    m = malloc (nr * sizeof(int *));
    for (i=0; i<nr; i++) {
        m[i] = malloc (nc * sizeof(int));
    }
    return m;
}

void leggiMatrice (int **mat, int nr, int nc, FILE *fp) {
    int i, j;
    for (i=0; i<nr; i++) {
        for (j=0; j<nc; j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
}

void separa (int **mat, int nr, int nc, int *bianco, int *nero) {
    int i, j, counter=1, b=0, n=0;
    for (i=0; i<nr; i++) {
        for (j=0; j<nc; j++) {
            if (counter%2==0)
                bianco[b++] = mat[i][j];
            else
                nero[n++] = mat[i][j];
            counter++;
        }
    }
}
