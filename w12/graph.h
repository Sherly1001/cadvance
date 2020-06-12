#ifndef __graph_h__
#define __graph_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxE 100
#define MaxV 1000

typedef struct node {
    char label;
    int index;
    int weight;
    struct node *next;
} node_t;

typedef struct graph {
    node_t *edges[MaxE];
    int nV;
    int nE;
} graph_t;

graph_t *load_from_file(graph_t **g, const char *fn);

#endif