#ifndef __sher_graph__
#define __sher_graph__

#include <stdlib.h>
#include <ctype.h>

typedef struct node {
    char word[30];
    int nAdj;
    struct *node adjs;
    struct *node next;
} node_t;

typedef struct graph {
    int nV;
    int nE;
    node_t *vetices;
} graph_t;


int isAdj(const char *s1, const char *s2);
void load_graph(graph_t *g, const char *fn);
void load_edges(graph_t *g);

#endif