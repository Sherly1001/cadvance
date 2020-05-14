/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include "graph.h"

int main()
{
    GRAPH *myGraph;    
    myGraph = initGraphFromFile("input.txt");
    char *s = topoSort(myGraph);
    printf("%s\n", s);

    printf("\nDFS\n");
    topoDFS(myGraph);
    return 0;
}
