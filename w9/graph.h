#define MAXV 100 /* maximum number of vertices */
#define MAXE 1000
typedef struct NODE {
    char label; /* adjacency info */
    int index;
    int weight; /* edge weight, if any */
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
void dijkstra(GRAPH *myGraph, int startVertex, int endVertex);
