#ifndef __sher_stack__
#define __sher_stack__

#include <stdlib.h>

typedef int st_type;

typedef struct stack {
    st_type val;
    struct stack *prev;
} stack;

st_type push(stack **st, st_type val);
st_type pop(stack **st);

#endif