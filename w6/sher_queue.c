#include "sher_queue.h"

int enqueue(queue *q, int val) {
    if (!q) return -1;
    if (q->first) {
        q->rear->next = malloc(sizeof(node));
        q->rear = q->rear->next;
    } else {
        q->first = q->rear = malloc(sizeof(node));
    }

    q->rear->next = NULL;
    return q->rear->val = val;
}

int dequeue(queue *q) {
    if (!q || !q->first) return -1;
    int val = q->first->val;
    node *tmp = q->first;
    q->first = tmp->next;
    free(tmp);
    return val;
}