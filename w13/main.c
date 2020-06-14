#include <stdio.h>
#include <stdlib.h>
#include "compress.h"

int main() {
    WCode myCode[128];
    int myCodeSize;

    char s[100];
    printf("Enter string: ");
    scanf("%[^\n]s\n", s);
    printf("Process string: '%s'\n", s);

    processinput(s, myCode, &myCodeSize);
    buildHuffmanTree(myCode, myCodeSize);
    return 0;
}
