#ifndef __queue_h__
#define __queue_h__

typedef struct TN {
    char data;
    int freq;
    struct TN *left, *right;
} TREENODE;


// Node
typedef struct node {
    TREENODE *data; // gia tri
    int priority; // do uu tien
    struct node *next;
} Node;

typedef struct  {
    char data; // gia tri
    int freq; // do uu tien
    char code[20]; // ma hoa cua tu "1011"
} WCode;


// cap phat bo nho tao nut moi
Node *newNode(TREENODE *d, int p);

// lay ra phan tu o dau hang doi head
// vi co thay doi gia tri head trong ham
// nen truy vao la **head
Node *dequeue(Node **head);

// them phan tu vao hang doi theo do uu tien
void enqueue(Node **head, TREENODE *d, int p);

// tra ve 1 neu hang doi rong và 0 neu nguoc lai
int isEmpty(Node *head);

#endif