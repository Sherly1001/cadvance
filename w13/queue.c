#include "queue.h"
#include <stdlib.h>

int isEmpty(Node *head) {
    return (head == NULL);
}


Node *newNode(TREENODE *d, int p) {
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;

    return temp;
}

void enqueue(Node **head, TREENODE *d, int p) {
    // Create new Node
    Node *temp = newNode(d, p);

    // TH1. Hang doi ban dau rong
    // TH2. do uu tien cua phan tu moi them
    // lon hon do uu tien o dau hang doi

    // chen phan tu moi truoc dau cu
    if ((*head) == NULL || (*head)->priority >= p) {
        temp->next = *head;
        (*head) = temp;
    }
    // TH3. Duyet tim vi tri chen thich hop
    // Vi tri chen thich hop voi do uu tien <= cac phan tu truoc
    // va do uu tien > do uu tien phan tu dung sau
    else {
        Node *start = (*head);
        while (start->next != NULL &&
                start->next->priority < p) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}

Node *dequeue(Node **head) {
    Node *temp = *head;
    (*head) = (*head)->next;
    return temp;
}