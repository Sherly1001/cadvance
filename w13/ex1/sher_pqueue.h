#ifndef __sher_pqueue__
#define __sher_pqueue__

#include <stdlib.h>

typedef struct node_pq {
    void *data;
    int priority;
    struct node_pq *next;
} node_pq;

typedef struct pqueue {
    node_pq *first;
    node_pq *last;
} pqueue_t;

void *pq_copy_data(void *data); // user define to make a copy of data
void pq_free_data(void *data); // user define to free a data
void *pq_enqueue(pqueue_t *q, void *data, int priority);
void *pq_dequeue(pqueue_t *q);

#endif
