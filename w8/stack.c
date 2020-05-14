#include "stack.h"
#include <stdlib.h>

int isEmpty(STACK *myStack)
{
    return (NULL==myStack);
}

void push(STACK **myStack, int data)
{
    STACK *newNode = (STACK*)malloc(sizeof(STACK));
    newNode->data = data;
    
    if(NULL==*myStack)
    {
        newNode->next = NULL;
        *myStack=newNode;
    }
    else
    {
        newNode->next = *myStack;
        (*myStack) = newNode;
    }
}

int getTop(STACK *myStack)
{
    return myStack->data;
}

int pop(STACK **myStack)
{
    STACK *newNode = *myStack;
    *myStack = (*myStack)->next;
    return newNode->data;
}

