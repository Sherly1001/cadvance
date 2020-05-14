#ifndef __sher_queue_h__
#define __sher_queue_h__

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} node;

typedef struct queue {
    node *first, *rear;
} queue;

int enqueue(queue *q, int val);
int dequeue(queue *q);

#endif