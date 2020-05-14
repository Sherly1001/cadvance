#include "sher_stack.h"

st_type push(stack **st, st_type val) {
    stack *nst = malloc(sizeof(stack*));
    nst->val = val;
    nst->prev = *st;
    *st = nst;
    return val;
}


st_type pop(stack **st) {
    if (*st) {
        st_type val = (*st)->val;
        stack *fst = *st;
        *st = fst->prev;
        free(fst);
        return val;
    } else return -1;
}

