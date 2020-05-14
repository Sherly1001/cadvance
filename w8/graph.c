#include "stack.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
GRAPH * initGraphFromFile(char *filename)
{
    const int MAXCHAR = 100;
    FILE *fp;
    char str[MAXCHAR];

    fp = fopen(filename, "r");

    GRAPH *myGraph;
    myGraph = (GRAPH*) malloc(sizeof(GRAPH));
    
    int nVertexes;
    fscanf(fp,"%d", &nVertexes);
    myGraph->nvertices = nVertexes;
    
    //int i=0;
    while (fgets(str, MAXCHAR, fp) != NULL )
    {
        if(strcmp(str,"\r\n")==0) continue;
        
        int indexVertex = str[0]-'A';
        myGraph->edges[indexVertex] = NULL;
        // tao danh sach ke
        for(int i=strlen(str)-1;i>0;i--)
        {
            if(str[i]==' '|| str[i]=='\n'||str[i]=='\r') continue;
            //printf("%c",str[i]);
            int adjnode = str[i]-'A';
            
            NODE *aNode = (NODE*) malloc(sizeof(NODE));
            aNode->label = str[i];
            aNode->index = adjnode;
            aNode->next = myGraph->edges[indexVertex];
            myGraph->edges[indexVertex] = aNode;
        }
        //printf("%s", str);
    }
    fclose(fp);

    // test in GRAPH
    /*
    NODE *aNode = myGraph->edges[0];
    while(NULL!=aNode)
    {
        printf("%d %c, ",aNode->index,aNode->label);
        aNode=aNode->next;
    }
    */
    
    return myGraph;
}


void DFS(GRAPH *myGraph, int start)
{
    printf("DFS tai %d: \n",start);
    
    STACK * mStack = NULL;
    int color[MAXV+1];
    // gan nhan cac dinh ve mau trang
    for(int i=0;i<myGraph->nvertices; i++)
    {
        color[i]=0;
    }
    
    push(&mStack,start);
    color[start]=1;
    
    int countstep = 1; // buoc tham
    while(!isEmpty(mStack))
    {
        countstep++;
        
        int top = getTop(mStack);
        
        NODE *adjlist = myGraph->edges[top];
        
        while(adjlist!=NULL) 
        {
            //printf("%d ",adjlist->index);
            if(color[adjlist->index]!=0) adjlist =adjlist->next;
            else break;
        }
            
            
        if(adjlist==NULL) // khong con dinh nao chua tham
        {
            color[top]=2;
            pop(&mStack);
            printf("finish %d %c at step %d\n",top,top+'A', countstep);
            
            // them thoi diem ket thuc tham vao mang
            
            
        }
        else // con tham duoc tiep
        {
            printf("Start %d %c at step %d\n",adjlist->index,adjlist->label,countstep);
            push(&mStack,adjlist->index);
            color[adjlist->index]=1; //dang duoc tham
        }
    }
    
    printf(" done\n ");
}

void topoDFS(GRAPH *g) {
    int *visited = calloc(g->nvertices, sizeof(int));
    int *finish = malloc(g->nvertices * sizeof(int));
    STACK *st = NULL;

    int counter = 1;
    int print = 0;


    int *degree = calloc(g->nvertices, sizeof(int));

    for (int i = 0; i < g->nvertices; ++i) {
        NODE *adjlist = g->edges[i];
        while (adjlist) {
            ++degree[adjlist->index];

            adjlist = adjlist->next;
        }
    }

    for (int i = 0; i < g->nvertices; ++i) {
        if (degree[i] || visited[i]) continue;
        degree[i] = -1;
        print && printf("Push %c, step %d\n", i + 'A', counter);
        push(&st, i);

        while (!isEmpty(st)) {
            ++counter;
            
            int top = getTop(st);
            visited[top] = 1;
            
            NODE *adjlist = g->edges[top];

            // printf("top: %d, node: %p, step: %d\n", top, adjlist, counter);

            while (adjlist) {
                if (visited[adjlist->index]) adjlist = adjlist->next;
                else break;
            }

            if (!adjlist) {
                finish[top] = counter;
                pop(&st);

                print && printf("pop: %c, step: %d\n", top + 'A', counter);
            } else {
                push(&st, adjlist->index);
                visited[adjlist->index] = 1;

                print && printf("Push: %c, step: %d\n", adjlist->index + 'A', counter);
            }
        }
    }

    if (print) for (int i = 0; i < g->nvertices; ++i) printf("%d ", finish[i]);
    print && printf("\n");

    for (int i = 0; i < g->nvertices; ++i) {
        int i_m = 0;
        while (finish[i_m] < 0 && i_m < g->nvertices) ++i_m;
        for (int j = i + 1; j < g->nvertices; ++j) {
            if (finish[j] > finish[i_m]) i_m = j;
        }
        finish[i_m] = -1;
        printf("%c, ", i_m + 'A');
    }
    printf("\n");

    free(degree);
    free(visited);
    free(finish);
}

// 0  1 2  3  4  5 6 7  8
// -1 9 11 15 -1 6 7 14 8

// 4 0

char *topoSort(GRAPH *myGraph)
{
    char tmp[20];
    char *s = malloc(500);
    s[0] = '\0';
    int degree[MAXV+1];
    
    for(int i=0;i<myGraph->nvertices; i++)
        degree[i]=0;
    // cap nhat ma tran bac cua dinh
    for(int i=0;i<myGraph->nvertices; i++)
    {
        NODE *adjlist = myGraph->edges[i];
        while(adjlist!=NULL) 
        {
            degree[adjlist->index]++;
            adjlist = adjlist->next;
        }
    }
    
    // testing
    /*
    for(int i=0;i<myGraph->nvertices; i++)
    {
        
        NODE *adjlist = myGraph->edges[i];
        printf("%c degree = %d\n", i+'A', degree[i]);
    }
    */
    // printf("\nTopo:\n");
    for(int i=0;i<myGraph->nvertices; i++)
    {
        for(int j=0; j<myGraph->nvertices; j++)
        if(degree[j]==0) 
        {
            // in ra dinh
            sprintf(tmp, "%c, ", j+'A');
            strcat(s, tmp);
            // printf("%c, ", j+'A');
            // gan nhan dinh da xet
            degree[j]=-1;
            
            // loai bo cac canh xuat phat tu dinh da xet
            NODE *adjlist = myGraph->edges[j];
            while(adjlist!=NULL) 
            {
                degree[adjlist->index]--;
                adjlist = adjlist->next;
            }
        }
    }
    return s;
}