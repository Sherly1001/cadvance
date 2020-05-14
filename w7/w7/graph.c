#include "stack.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sher_queue.h"

GRAPH * initGraphFromFile(char *filename)
{
    const int MAXCHAR = 100;
    FILE *fp;
    char str[MAXCHAR];

    fp = fopen(filename, "r");

    GRAPH *myGraph = malloc(sizeof(GRAPH));
    
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

        int degree = 0;
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
            ++degree;
        }
        myGraph->degree[indexVertex] = degree;
        //printf("%s", str);
    }
    fclose(fp);

    // test in GRAPH
    /*
    NODE *aNode = myGraph->edges[5];
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
    printf("DFS at %d %c: \n", start, start + 'A');
    
    STACK * mStack = NULL;

    int *visitingTimes = malloc(myGraph->nvertices * sizeof(int));
    int *finishTimes = malloc(myGraph->nvertices * sizeof(int));
    int color[MAXV+1];
    // gan nhan cac dinh ve mau trang
    for(int i=0;i<myGraph->nvertices; i++)
    {
        color[i]=0;
        visitingTimes[i] = 0;
    }
    
    push(&mStack,start);
    color[start]=1;

    queue q = {0};
    enqueue(&q, start);
    
    int countstep = 1; // buoc tham
    while(!isEmpty(mStack))
    {
        countstep++;
        int top = getTop(mStack);
        if (!visitingTimes[top]) visitingTimes[top] = countstep - 1;
        
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
            finishTimes[top] = countstep;
        }
        else // con tham duoc tiep
        {
            push(&mStack,adjlist->index);
            enqueue(&q, adjlist->index);
            color[adjlist->index]=1; //dang duoc tham
        }
    }
    
    while (q.first) {
        int i = q.first->val;
        printf("%c %d %d\n", i + 'A', visitingTimes[i], finishTimes[i]);
        dequeue(&q);
    }


    free(visitingTimes);
    free(finishTimes);
}

int sher_dfs(GRAPH *g, int s) {
    printf("\nDeepest of %d %c is ", s, s + 'A');
    STACK * mStack = NULL;
    int color[MAXV+1];
    // gan nhan cac dinh ve mau trang
    for(int i=0;i<g->nvertices; i++)
    {
        color[i]=0;
    }
    
    push(&mStack,s);
    color[s]=1;
    
    int countstep = 1; // buoc tham
    while(!isEmpty(mStack))
    {
        countstep++;
        int top = getTop(mStack);
        
        NODE *adjlist = g->edges[top];
        
        while(adjlist!=NULL) 
        {
            //printf("%d ",adjlist->index);
            if(color[adjlist->index]!=0) adjlist =adjlist->next;
            else break;
        }

        if(adjlist==NULL) // khong con dinh nao chua tham
        {
            printf("%d %c\n", top, top + 'A');
            while (!isEmpty(mStack)) pop(&mStack);
        }
        else // con tham duoc tiep
        {
            push(&mStack,adjlist->index);
            color[adjlist->index]=1; //dang duoc tham
        }
    }
}