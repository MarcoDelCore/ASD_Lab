#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char c;
    int v;
} tube_t;

typedef struct {
    tube_t hor;
    tube_t ver;
    int r;
} tile_t;

tile_t *readTiles();
tile_t **readBoard (tile_t *tiles, int *check);
tile_t **malloc2d (int r, int c);
void dispSempl (int pos, tile_t **sol, int *check, tile_t **board, tile_t *tiles);
void boardScore(tile_t **sol);
void printWinningBoard ();

int n_tiles, row, col, best = 0;
tile_t **winning_board;


int main() {
    int *check;
    tile_t *tiles, **board, **sol;

    tiles = readTiles();
    check = calloc(n_tiles, sizeof(int));
    board = readBoard(tiles, check);
    sol = malloc2d(row, col);
    winning_board = malloc2d(row, col);

    dispSempl(0, sol, check, board, tiles);

    printf("Best score: %d\n", best);
    printWinningBoard();
    return 0;
}


tile_t *readTiles() {
    FILE *fp;
    int i;
    tile_t *tiles;

    if ((fp = fopen("../tiles.txt", "r")) == NULL){
        printf("Error. File tiles.txt not found.\n");
        exit(1);
    }

    fscanf(fp, "%d ", &n_tiles);
    tiles = (tile_t *) malloc(n_tiles * sizeof(tile_t));

    for (i=0; i<n_tiles; i++) {
        fscanf(fp, "%c %d %c %d ", &tiles[i].hor.c, &tiles[i].hor.v, &tiles[i].ver.c, &tiles[i].ver.v);
    }
    fclose(fp);
    return tiles;
}

tile_t **readBoard(tile_t *tiles, int *check) {
    FILE *fp;
    tile_t **board;
    int i, j, index, rot;

    if ((fp = fopen("../board.txt", "r")) == NULL) {
        printf("Error. File board.txt not found.\n");
        exit(2);
    }

    fscanf(fp, "%d %d ", &row, &col);

    board = malloc2d(row, col);

    for (i=0; i<row; i++) {
        for (j=0; j<col; j++) {
            board[i][j].hor.c = 'X';
            board[i][j].ver.c = 'X';
        }
    }

    for (i=0; i<row; i++) {
        for (j=0; j<col; j++) {
            fscanf(fp, "%d/%d ", &index, &rot);
            if (index != -1) {
                check[index] = 1;
                // completo board con tutte le tessere nello stasso orientamento
                if (rot != 1)
                    board[i][j] = tiles[index];
                else {
                    board[i][j].ver= tiles[index].hor;
                    board[i][j].hor = tiles[index].ver;
                }
            }
        }
    }
    fclose(fp);
    return board;
}

tile_t **malloc2d (int r, int c) {
    int i;
    tile_t **m;
    m = (tile_t **) malloc(r * sizeof(tile_t *));
    for (i=0; i<r; i++) {
        m[i] = malloc(c * sizeof (tile_t));
    }
    return m;
}

void dispSempl (int pos, tile_t **sol, int *check, tile_t **board, tile_t *tiles) {
    int i, r, c;

    if (pos >= row * col) {
            boardScore(sol);
            return;
    }

    r = pos / col;
    c = pos % col;

    for (i = 0; i < n_tiles; i++) {
        if (check[i] == 0) { //tessere non presenti nella scacchiera iniziale
            if (board[r][c].hor.c == 'X') {
                check[i] = 1;
                sol[r][c] = tiles[i];
                sol[r][c].r = 0;
                dispSempl(pos+1, sol, check, board, tiles);

                //rotazione tessere
                sol[r][c].ver = tiles[i].hor;
                sol[r][c].hor = tiles[i].ver;
                sol[r][c].r = 1;
                dispSempl(pos+1, sol, check, board, tiles);
                check[i] = 0;
            }
            else { //tessere presenti nella scacchiera iniziale
                sol[r][c] = board[r][c];
                dispSempl(pos+1, sol, check, board, tiles);
            }
        }
    }
}

void boardScore(tile_t **sol) {
    int i, j;
    int r_val=0, c_val=0, t;

    for (i = 0; i < row; i++) {
        t = 0;
        for (j = 0; j < col; j++) {
            if (j==0 || sol[i][j-1].hor.c == sol[i][j].hor.c)
                t += sol[i][j].hor.v;
            else {
                t = 0;
                break;
            }
        }
        r_val += t;
    }
    for (j = 0; j < col; j++) {
        t = 0;
        for (i = 0; i < row; i++) {
            if (i==0 || sol[i-1][j].ver.c == sol[i][j].ver.c)
                t += sol[i][j].ver.v;
            else {
                t = 0;
                break;
            }
        }
        c_val += t;
    }

    if (r_val + c_val > best) {
        best = r_val+c_val;
        for (i=0; i<row; i++) {
            for (j=0; j<col; j++) {
                winning_board[i][j] = sol[i][j];
            }
        }
    }
}

void printWinningBoard () {
    int i, j;
    for (i=0; i<row; i++) {
        for (j=0; j<col; j++) {
            printf("%c%d %c%d\t", winning_board[i][j].hor.c, winning_board[i][j].hor.v, winning_board[i][j].ver.c, winning_board[i][j].ver.v);
        }
        printf("\n");
    }
}