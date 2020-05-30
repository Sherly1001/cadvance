/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "fileprocess.h"

//[i][j] tu [0][0] toi [row-1][col-1]
//tesst 1 [i][j+1], 2 [i+1][j], 3 [i][j-1], 4 [i-1][j]
// tra ve 1 neu co duong vaf 0 neu ko ton tai
int countTry = 0;
int try(char **Graph, int row, int col, int currow, int curcol) {
    ++countTry;
    if (currow == row - 1 && curcol == col - 1) {
        Graph[currow][curcol] = 3;
        return 1;
    }
    if (Graph[currow][curcol] == 0 || Graph[currow][curcol] == 3) return 0;
    Graph[currow][curcol] = 3; // danh dau de ko quay lai
    if (currow == 0) { // hang dau
        // dau hang, dau cot
        if (curcol == 0) return try(Graph, row, col, currow, curcol + 1) ||
                                        try(Graph, row, col, currow + 1, curcol);
        else if (curcol == col - 1) // dau hang, cot cuoi
            return try(Graph, row, col, currow + 1, curcol) ||
                       try(Graph, row, col, currow, curcol - 1);
        else // giua hang tren cung
            return try(Graph, row, col, currow, curcol + 1) ||
                       try(Graph, row, col, currow + 1, curcol) ||
                           try(Graph, row, col, currow, curcol - 1);

    } else if (currow == row - 1) { // hang cuoi
        // cuoi hang, dau cot
        if (curcol == 0) return try(Graph, row, col, currow, curcol + 1) ||
                                        try(Graph, row, col, currow - 1, curcol);
        else if (curcol == col - 1) // cuoi hang, cot cuoi  (bo qua)
            return try(Graph, row, col, currow - 1, curcol) ||
                       try(Graph, row, col, currow, curcol - 1);
        else // hang cuoi, giua cot
            return try(Graph, row, col, currow, curcol + 1) ||
                       try(Graph, row, col, currow, curcol - 1) ||
                           try(Graph, row, col, currow - 1, curcol);
    } else { // giua hang
        if (curcol == 0) return try(Graph, row, col, currow, curcol + 1) ||
                                        try(Graph, row, col, currow - 1, curcol) ||
                                            try(Graph, row, col, currow + 1, curcol);
        else if (curcol == col - 1) // giua hang, cot cuoi
            return try(Graph, row, col, currow + 1, curcol) ||
                       try(Graph, row, col, currow, curcol - 1) ||
                           try(Graph, row, col, currow - 1, curcol);
        else // hang cuoi, giua cot
            return try(Graph, row, col, currow, curcol + 1) ||
                       try(Graph, row, col, currow + 1, curcol) ||
                           try(Graph, row, col, currow, curcol - 1) ||
                               try(Graph, row, col, currow - 1, curcol);
    }
}

void printGraphToFile(char **g, int r, int c, const char *fn) {
    FILE *f = fopen(fn, "w");
    fprintf(f, "%d %d\n", r, c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) fprintf(f, "%d ", g[i][j]);
        fprintf(f, "\n");
    }
}

int countTry2 = 0;
int try2(char **Graph, int row, int col, int currow, int curcol) {
    ++countTry2;
    if (currow == row - 1 && curcol == col - 1) {
        Graph[currow][curcol] = 3;
        return 1;
    }
    if (Graph[currow][curcol] == 0 || Graph[currow][curcol] == 3) return 0;
    Graph[currow][curcol] = 3; // danh dau de ko quay lai
    if (currow == 0) { // hang dau
        // dau hang, dau cot
        if (curcol == 0) return try2(Graph, row, col, currow, curcol + 1) || // phai
                                    try2(Graph, row, col, currow + 1, curcol); // xuong
        else if (curcol == col - 1) // dau hang, cot cuoi
            return  try2(Graph, row, col, currow, curcol - 1) || // trai
                    try2(Graph, row, col, currow + 1, curcol); // xuong
        else // giua hang tren cung
            return try2(Graph, row, col, currow, curcol + 1) || // phai
                   try2(Graph, row, col, currow, curcol - 1) || // trai
                   try2(Graph, row, col, currow + 1, curcol); // xuong

    } else if (currow == row - 1) { // hang cuoi
        // cuoi hang, dau cot
        if (curcol == 0) return try2(Graph, row, col, currow, curcol + 1) || // phai
                                    try2(Graph, row, col, currow - 1, curcol); // len
        else if (curcol == col - 1) // cuoi hang, cot cuoi  (bo qua)
            return try2(Graph, row, col, currow, curcol - 1) || // trai
                   try2(Graph, row, col, currow - 1, curcol); // len
        else // hang cuoi, giua cot
            return try2(Graph, row, col, currow, curcol + 1) || // phai
                   try2(Graph, row, col, currow, curcol - 1) || // trai
                   try2(Graph, row, col, currow - 1, curcol); // len
    } else { // giua hang
        if (curcol == 0) return try2(Graph, row, col, currow, curcol + 1) || // phai
                                    try2(Graph, row, col, currow - 1, curcol) || // len
                                    try2(Graph, row, col, currow + 1, curcol); // xuong
        else if (curcol == col - 1) // giua hang, cot cuoi
            return try2(Graph, row, col, currow, curcol - 1) || // trai
                   try2(Graph, row, col, currow - 1, curcol) || // len
                   try2(Graph, row, col, currow + 1, curcol); // xuong
        else // hang cuoi, giua cot
            return try2(Graph, row, col, currow, curcol + 1) || // phai
                   try2(Graph, row, col, currow, curcol - 1) || // trai
                   try2(Graph, row, col, currow - 1, curcol) || // len
                   try2(Graph, row, col, currow + 1, curcol); // xuong
    }
}

int checkPath(char **Graph, int row, int col) {
    // int retval = try(Graph,row,col,0,0);
    int retval = try2(Graph, row, col, 0, 0);
    if (retval == 1)
        printf("Ton tai duong di!\n");
    else
        printf("KHONG ton tai duong di!\n");
    return retval;
}

int available(int r, int c, int i, int j) {
    return 0 <= i && i < r && 0 <= j && j < c;
}

int move_i[] = {0, 1, 0, -1};
int move_j[] = {1, 0, -1, 0};

int trySher(char **Graph, char **tmp, int row, int col, int currow, int curcol) {
    // printf("(%d, %d) %d\n", currow, curcol, Graph[currow][curcol]);
    if (currow == row - 1 && curcol == col - 1) {
        Graph[currow][curcol] = 3;
        tmp[currow][curcol] = 1;
        printGraph(tmp, row, col);
        return 1;
    }
    if (Graph[currow][curcol] == 0 || Graph[currow][curcol] == 3) return 0;
    Graph[currow][curcol] = 3; // danh dau de ko quay lai

    for (int i = 0; i < 4; ++i) {
        int nr = currow + move_i[i];
        int nc = curcol + move_j[i];
        if (available(row, col, nr, nc)) {
            tmp[currow][curcol] = 1;
            int ts = trySher(Graph, tmp, row, col, nr, nc);
            tmp[currow][curcol] = 0;

            if (ts) return 1;
        }
    }
    return 0;
}

void sher(char **a, int r, int c) {
    char **tmp = malloc(r * sizeof(char *));
    for (int i = 0; i < r; ++i) tmp[i] = malloc(c * sizeof(char));

    trySher(a, tmp, r, c, 0, 0);

    for (int i = 0; i < r; ++i) free(tmp[i]);
    free(tmp);
}

int main() {
    char **Graph;
    int row, col;
    Graph = readFile("input1.txt", &row, &col);
    // printGraph(Graph, row, col);
    // int canGo = checkPath(Graph, row, col);
    // printGraph(Graph, row, col);

    // if (canGo) printGraphToFile(Graph, row, col, "output1.txt");


    // printf("So lan thu try: %d\n", countTry);   // 128
    // printf("So lan thu try2: %d\n", countTry2); // 215
    // tang so voi voi try 1

    // printGraph(Graph, row, col);
    sher(Graph, row, col);
    return 0;
}
