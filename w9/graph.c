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
            
            
            NODE *aNode = (NODE*) malloc(sizeof(NODE));
            
             //trong so
            aNode->weight = str[i]-'0';
            i=i-2;
            
            int adjnode = str[i]-'A';
            
            aNode->label = str[i];
            aNode->index = adjnode;
            
            aNode->next = (struct NODE *)myGraph->edges[indexVertex];
            myGraph->edges[indexVertex] = aNode;
            
            
        }
        //printf("%s", str);
    }
    fclose(fp);

    // test in GRAPH
    /*
    NODE *aNode = myGraph->edges[3];
    while(NULL!=aNode)
    {
        printf("%d %c %d, ",aNode->index,aNode->label,aNode->weight);
        aNode=aNode->next;
    }
    */
    
    return myGraph;
}

void dijkstra(GRAPH *myGraph, int startVertex, int endVertex)
{
    int M[MAXE][MAXV];
    int nVertex =  myGraph->nvertices;

    char mark[MAXV] = {0};
    
    for(int i=0;i<myGraph->nvertices;i++)
        for(int j=0; j<MAXE;j++)
            M[j][i]=999;
    
    M[1][startVertex]=0;
    int i=1;
    while(1==1)
    {
        
        int minVertex = 0;
        for(int j=0;j<myGraph->nvertices;j++)
            if(M[i][j]<M[i][minVertex]) minVertex =j;
        
        int weightAtCurr = M[i][minVertex];
        // printf("Dinh duoc chon : %c voi trong so %d\n", minVertex+'A',weightAtCurr);
        if(minVertex==endVertex)
        {
            // printf("Tim duoc duong di ngan nhat trong so: %d\n",weightAtCurr);
            break;
        }
        // lay lai gia tri cu
        for(int j=0;j<myGraph->nvertices;j++)
            M[i+1][j] = M[i][j];
            
        // bo cot da chon
        M[i+1][minVertex] = 8888;
        
            
        // cap nhat trong so canh ke tuong ung
        NODE *aNode = myGraph->edges[minVertex];
        while(NULL!=aNode)
        {
            int adjVertex = aNode->index;
            int weight = aNode->weight;
            // check de cap nhat
            if(M[i][adjVertex]!=8888)
                if(M[i][adjVertex]>(weightAtCurr+weight)) {
                    M[i+1][adjVertex] = weightAtCurr+weight;
                    mark[adjVertex] = minVertex;
                } else
                    M[i+1][adjVertex] = M[i][adjVertex];
                
            aNode=aNode->next;
        }
        
        i++;
    }

    printf("%c from %c\n", endVertex + 'A', startVertex + 'A');

    while (endVertex != startVertex) {
        printf("%c <- ", endVertex + 'A');
        endVertex = mark[endVertex];
    }
    printf("%c\n", startVertex + 'A');
}

