typedef struct STACK
{
    int data;
    struct STACK *next;
} STACK;

int isEmpty(STACK *myStack);
void push(STACK **myStack, int data);
int getTop(STACK *myStack);// tra ve gia tri o dinh, ko lay ra
int pop(STACK **myStack);