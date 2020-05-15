/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    GRAPH *myGraph;    
    myGraph = initGraphFromFile("input.txt");
    dijkstra(myGraph,2,10);
    return 0;
}
