
#define MAXV 100 /* maximum number of vertices */


typedef struct {
    char nodename[MAXV+1][50]; // index starts from 1
    int edges[MAXV+1][MAXV+1]; /* adjacency info */
    int degree[MAXV+1]; /* outdegree of each vertex */
    int nvertices; /* number of vertices in graph */
} GRAPH;
