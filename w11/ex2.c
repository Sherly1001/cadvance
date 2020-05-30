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

int max(int a, int b) {
    return a > b ? a : b;
}

void trace(int **dp, int r, int c) {
    int **tmp = malloc(r * sizeof(int*));
    for (int i = 0; i < r; ++i) tmp[i] = calloc(c, sizeof(c));

    tmp[0][0] = 1;
    tmp[r - 1][c - 1] = 1;
    for (int i = r - 1, j = c - 1;;) {
        if (i == 0) {
            while (j) {
                tmp[i][j] = 1;
                --j;
            }
            break;
        } else if (j == 0) {
            while (i) {
                tmp[i][j] = 1;
                --i;
            }
            break;
        }

        if (dp[i - 1][j] > dp[i][j - 1]) {
            tmp[--i][j] = 1;
        } else {
            tmp[i][--j] = 1;
        }
    }

    prt(tmp, r, c);
    for (int i = 0; i < r; ++i) free(tmp[i]);
    free(tmp);
}

void sher(int **a, int r, int c) {
    int **dp = malloc(r * sizeof(int*));
    for (int i = 0; i < r; ++i) dp[i] = malloc(c * sizeof(c));

    dp[0][0] = a[0][0];
    for (int j = 1; j < c; ++j) dp[0][j] = dp[0][j - 1] + a[0][j];
    for (int i = 1; i < r; ++i) dp[i][0] = dp[i - 1][0] + a[i][0];

    for (int i = 1; i < r; ++i) {
        for (int j = 1; j < c; ++j) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + a[i][j];
        }
    }

    trace(dp, r, c);
    for (int i = 0; i < r; ++i) free(dp[i]);
    free(dp);
}

int main() {
    int **a = NULL;
    int r = 0, c = 0;
    
    input_from_file(&a, &r, &c, "input2.txt");

    prt(a, r, c);
    sher(a, r, c);
}
