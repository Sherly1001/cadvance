#define MAXV 1000 /* maximum number of vertices */
typedef struct NODE {
    char label; /* adjacency info */
    int index;
    //int weight; /* edge weight, if any */
    struct NODE *next; /* next edge in list */
} NODE;

typedef struct {
    NODE *edges[MAXV+1]; /* adjacency info */
    int degree[MAXV+1]; /* outdegree of each vertex */
    int nvertices; /* number of vertices in graph */
    int nedges; /* number of edges in graph */
    //bool directed; /* is the graph directed? */
} GRAPH;

GRAPH *initGraphFromFile(char *filename);
void DFS(GRAPH *myGraph, int start);
int sher_dfs(GRAPH *g, int s);