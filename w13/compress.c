#include "compress.h"

void processinput(const char *str, WCode myCode[128], int *myCodeSize) {
    *myCodeSize = 0;
    for (int i = 0; str[i]; ++i) {
        int j = 0;
        for (; j < *myCodeSize; ++j) {
            if (myCode[j].data == str[i]) {
                ++myCode[j].freq;
                break;
            }
        }
        if (j == *myCodeSize) {
            myCode[j].data = str[i];
            myCode[j].freq = 1;
            ++(*myCodeSize);
        }
    }

    for (int i = 0; i < *myCodeSize; ++i) {
        printf("%c: %d\n", myCode[i].data, myCode[i].freq);
    }
    printf("\n");
}

void treeTravel(TREENODE *root, char rootcode[]) {
    if (NULL == root) return;
    if (root->left == NULL && root->right == NULL) {
        //strcpy(root->code,rootcode);
        printf("%c %d %s\n", root->data, root->freq, rootcode);
    } else {
        char codewordleft[100], codewordright[100];
        strcpy(codewordleft, rootcode);
        strcpy(codewordright, rootcode);
        treeTravel(root->left, strcat(codewordleft, "0"));
        treeTravel(root->right, strcat(codewordright, "1"));
    }
}
TREENODE *buildHuffmanTree(WCode myCode[128], int myCodeSize) {
    Node *head = NULL;

    // tao heap chua cac nut la tu ma ban dau
    for (int j = 0; j < myCodeSize; j++) {
        TREENODE *newNode = malloc(sizeof(TREENODE));
        newNode->data = myCode[j].data;
        newNode->freq = myCode[j].freq;
        newNode->left = NULL;
        newNode->right = NULL;

        enqueue(&head, newNode, newNode->freq);
    }

    // tao cay ma huffman
    for (int i = 0; i < myCodeSize - 1; i++) {
        // lay ra 2 nut nho nhat
        Node *node1 = dequeue(&head);
        Node *node2 = dequeue(&head);

        TREENODE *newNode = (TREENODE *)malloc(sizeof(TREENODE));
        newNode->data = '#';
        newNode->freq = node1->data->freq + node2->data->freq;
        newNode->left = node1->data;
        newNode->right = node2->data;
        free(node1);
        free(node2);

        enqueue(&head, newNode, newNode->freq);
    }

    // nut goc cua cay ma huffman
    Node *root = dequeue(&head);
    TREENODE *hTree = root->data;
    free(root);
    treeTravel(hTree, "");
    return hTree;
}
