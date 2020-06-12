#include <stdio.h>
#include <stdlib.h>

int **input_from_file(int ***a, int *r, int *c, const char *fn) {
    FILE *f = fopen(fn, "r");
    if (!f) {
        printf("Can't open file '%s'\n", fn);
        return NULL;
    }

    fscanf(f, "%d %d\n", r, c);
    *a = malloc(*r * sizeof(int*));
    for (int i = 0; i < *r; ++i) {
        *(*a + i) = malloc(*c * sizeof(int));
        for (int j = 0; j < *c; ++j) fscanf(f, "%d", *(*a + i) + j);
    }
    return *a;
}

void prt(int **a, int r, int c) {
    printf("%d %d\n", r, c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) printf("%2d ", a[i][j]);
        printf("\n");
    }
}


void update(int **path, int **best, int r, int c) {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            best[i][j] = path[i][j];
        }
    }
}

void try(int **a, int **path, int **best, int r, int c, int i, int j, int acc, int *best_acc) {
    acc += a[i][j];
    if (i == r - 1) {
        while (j != c - 1) {
            acc += a[i][++j];
        }
        if (acc > *best_acc) {
            update(path, best, r, c);
            *best_acc = acc;
        }
    } else {
        if (j == c - 1) {
            while (i != r - 1) {
                acc += a[++i][j];
            }
            if (acc > *best_acc) {
                update(path, best, r, c);
            }
        } else {
            path[i][j + 1] = 1;
            try(a, path, best, r, c, i, j + 1, acc + ) 
        }
    }
}


void sher(int **a, int r, int c) {
    int **path = malloc(sizeof(int*));
    int **best = malloc(sizeof(int*));

    for (int i = 0; i < r; ++i) {
        path[i] = calloc(c, sizeof(int));
        best[i] = calloc(c, sizeof(int));
    }

    int best_acc = -(1 << 16);
    path[0][0] = 1;

    try(a, path, best, r, c, 0, 0, 0, &best_acc);

    prt(best, r, c);

    for (int i = 0; i < r; ++i) {
        free(path[i]);
        free(best[i]);
    }

    free(path);
    free(best);
}

int main() {
    int **a = NULL;
    int r, c;
    input_from_file(&a, &r, &c, "input2.txt");

    prt(a, r, c);

    sher(a, r, c);
}