#include "btree/bTree.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ag, char **av) {
    srand(time(0));
    bTree b = btCreate();

    for (int i = 0; i < 100; ++i) btInsert(b, rand());

    printf("Height of b tree: %d\n", btHeight(b));
    btPrintKeys(b);
    printf("\n");
    btPrintKeys_preoder(b);

    btDestroy(b);
}