#include "graph.h"
#include "sher_queue.h"
#include <stdio.h>
#include <string.h>

void initGraph(GRAPH *myGraph) {
    myGraph->nvertices = 9;

    // gan ca trong so ve 0 truoc khi dung
    for (int i = 1; i <= myGraph->nvertices; i++)
        for (int j = 1; j <= myGraph->nvertices; j++) myGraph->edges[i][j] = 0;

    // gan gia tri cac canh
    myGraph->edges[1][2] = 1;
    myGraph->edges[1][3] = 1;
    myGraph->edges[1][6] = 1;

    myGraph->edges[2][1] = 1;
    myGraph->edges[2][7] = 1;
    myGraph->edges[2][8] = 1;

    myGraph->edges[3][5] = 1;

    myGraph->edges[4][3] = 1;

    myGraph->edges[5][3] = 1;
    myGraph->edges[5][4] = 1;
    myGraph->edges[5][9] = 1;

    myGraph->edges[6][3] = 1;

    myGraph->edges[7][2] = 1;
    myGraph->edges[7][6] = 1;
    myGraph->edges[7][8] = 1;
    myGraph->edges[7][9] = 1;

    myGraph->edges[8][7] = 1;

    myGraph->edges[9][7] = 1;
    myGraph->edges[9][3] = 1;

    strcpy(myGraph->nodename[1], "A");
    strcpy(myGraph->nodename[2], "B");
    strcpy(myGraph->nodename[3], "C");
    strcpy(myGraph->nodename[4], "D");
    strcpy(myGraph->nodename[5], "E");
    strcpy(myGraph->nodename[6], "F");
    strcpy(myGraph->nodename[7], "G");
    strcpy(myGraph->nodename[8], "H");
    strcpy(myGraph->nodename[9], "I");
}

void printMatrix(GRAPH *myGraph) {
    printf("Do thi duoi dang bang: \n");

    printf("  ");
    for (int i = 1; i <= myGraph->nvertices; i++)
        printf("%2s", myGraph->nodename[i]);
    printf("\n");

    for (int i = 1; i <= myGraph->nvertices; i++) {
        printf("%2s", myGraph->nodename[i]);
        for (int j = 1; j <= myGraph->nvertices; j++)
            printf("%2d", myGraph->edges[i][j]);
        printf("\n");
    }

    printf("\n");
}

void BFS(GRAPH *g, int v) {
    int *visited = calloc(g->nvertices, sizeof(int));
    queue q = {0};

    printf("Start BFS from vertex %2s\n", g->nodename[v]);

    visited[v - 1] = 1;
    enqueue(&q, v);

    while (q.first) {
        int nv = dequeue(&q);
        visited[nv - 1] = 1;

        for (int i = 1; i <= g->nvertices; ++i) {
            if (g->edges[nv][i] & !visited[i - 1]) {
                enqueue(&q, i);
                visited[i - 1] = 1;
            }
        }
        printf("%2s, ", g->nodename[nv]);
    }
    printf("\n");
    free(visited);
}

// ex1
void printDegree(GRAPH *g) {
    for (int i = 1; i <= g->nvertices; ++i) {
        int s = 0;
        for (int j = 1; j <= g->nvertices; ++j) s += g->edges[i][j];
        g->degree[i] = s;
        printf("Node %s has degree is %d\n", g->nodename[i], s);
    }
    printf("\n");
}

// ex2
void sher_bfs(GRAPH *g, int sv, int ev) {
    int *visited = calloc(g->nvertices, sizeof(int));
    queue q = {0};

    printf("Sher BFS from vertex %s to %s\n", g->nodename[sv], g->nodename[ev]);

    visited[sv - 1] = 1;
    enqueue(&q, sv);

    while (q.first) {
        int nv = dequeue(&q);
        visited[nv - 1] = 1;

        printf("%2s, ", g->nodename[nv]);

        for (int i = 1; i <= g->nvertices; ++i) {
            if (g->edges[nv][i] & !visited[i - 1]) {
                if (i == ev) {
                    printf("%s\n", g->nodename[i]);
                    while(q.first) dequeue(&q);
                    break;
                }
                enqueue(&q, i);
                visited[i - 1] = 1;
            }
        }
    }
    printf("\n");
    free(visited);
}

int main() {
    GRAPH myGraph;
    initGraph(&myGraph);
    printMatrix(&myGraph);
    printDegree(&myGraph);

    BFS(&myGraph, 1);

    sher_bfs(&myGraph, 8, 3);
    return 0;
}
