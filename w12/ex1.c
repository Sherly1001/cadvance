#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void _sher_dfs(graph_t *g, char *visited, int start) {
    for (node_t *node = g->edges[start]; node; node = node->next) {
        if (!visited[node->index]) {
            visited[node->index] = 1;
            _sher_dfs(g, visited, node->index);
        }
    }
}

void sher_dfs(graph_t *g, int start) {
    char *visited = calloc(g->nV, sizeof(char));

    visited[start] = 1;
    _sher_dfs(g, visited, start);
    
    char all_visited = 1;
    for (int i = 0; i < g->nV; ++i) {
        if (!visited[i]) {
            all_visited = 0;
            break;
        }
    }

    printf("From %c we %s visit all another vertics\n", start + 'A', all_visited ? "can" : "can't");
    
    free(visited);
}

int main() {
    graph_t *g = NULL;
    load_from_file(&g, "input.txt");

    sher_dfs(g, 0);
}