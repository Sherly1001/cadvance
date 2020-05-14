#include "btree/bTree.h"

int main(int ag, char **av) {
    bTree t = btCreate();

    btInsert(t, 1);
    btInsert(t, 4);
    btInsert(t, 7);
    btInsert(t, 5);
    btInsert(t, 3);
    btInsert(t, 2);
    btInsert(t, 8);
    btInsert(t, 9);
    btInsert(t, 10);
    btInsert(t, 0);

    btPrintKeys_preoder(t);

    btDestroy(t);
}
