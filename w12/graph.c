#include "graph.h"

#define MS 100

graph_t *load_from_file(graph_t **g, const char *fn) {
    char tmp[MS] = "";

    FILE *f = fopen(fn, "r");

    graph_t *gp = *g = malloc(sizeof(graph_t));

    fscanf(f, "%d\n", &gp->nV);

    while (fgets(tmp, MS - 1, f)) {
        if (!strcmp(tmp, "\n")) continue;

        int index = tmp[0] - 'A';
        gp->edges[index] = NULL;

        for (int i = strlen(tmp) - 1; i > 0; --i) {
            if (tmp[i] == ' ' || tmp[i] == '\r' || tmp[i] == '\n') continue;

            node_t *node = malloc(sizeof(node_t));
            // node->weight = tmp[i] - '0';
            // i -= 2;
            int adjnode = tmp[i] - 'A';

            node->label = tmp[i];
            node->index = adjnode;
            node->next = gp->edges[index];
            gp->edges[index] = node;
        }
    }

    fclose(f);

    return gp;
}