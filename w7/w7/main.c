#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include "graph.h"
int main()
{
    GRAPH *myGraph;    
    myGraph = initGraphFromFile("input.txt");
    DFS(myGraph,0);

    sher_dfs(myGraph, 1);
    return 0;
}
