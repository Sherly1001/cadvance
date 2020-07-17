#include "sher_graph.h"


int isAdj(const char *s1, const char *s2) {
    char diff = 0;

    for (; *s1 && *s2; ++s1, ++s2) {
        char l1 = tolower(*s1);
        char l2 = tolower(*s2);

        if (l1 != l2) ++diff;
        if (diff == 2) return 0;
    }

    return 1;
}

void load_graph(graph_t *g, const char *fn) {

}

void load_edges(graph_t *g) {

}