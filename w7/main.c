#include <stdio.h>
#include "sher_stack.h"

int main() {
    stack *st = NULL;
    for (int i = 0; i < 10; ++i) push(&st, i);

    while (st) {
        printf("\033[02;34m%d\n\033[0m", pop(&st));
    }
}