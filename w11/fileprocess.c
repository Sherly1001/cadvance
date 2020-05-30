#include <stdio.h>
#include <stdlib.h>
#include "fileprocess.h"

// doc noi dung tu file va luu vao Graph
char** readFile(const char* filename, int *row, int *col)
{
    int n, m;
    FILE *fp;
    fp = fopen(filename,"r");
    if(NULL == fp) return NULL;
    
    fscanf(fp,"%d%d",&n, &m);
    *row = n;
    *col=m;
    char **Graph  = (char**)malloc(n * sizeof(char*));
    for(int i=0;i< n;i++)
    {
        Graph[i] = (char*)malloc(m * sizeof(char));
        for(int j=0;j< m;j++)
            fscanf(fp,"%d",&Graph[i][j]);
    }
    fclose(fp);
    return Graph;
}

void  printGraph(char **Graph, int row, int col)
{
    printf("%d %d\n",row,col);
    for(int i=0;i< row;i++)
    {
        for(int j=0;j< col;j++)
            printf("%2d",Graph[i][j]);
        printf("\n");
    }
}

