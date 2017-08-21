// stack_list.c ... Stack ADT implementation
// - uses linked list ADT to implement Stack
// Written by jas@cse, May 2017

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "list.h"

struct stack {
    list_t vals;  // linked list of stacked values
};


// create a new stack
stack_t create(void)
{
    struct stack *new;
    new = malloc(sizeof (struct stack));
    if (new == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
    new->vals = NULL;
    return new;   
}

// add new item to stack
void push(stack_t stack, int item)
{
    stack->vals = list_insert(item, stack->vals);
}

// remove top item from stack and return it
int pop(stack_t stack)
{
    int val = list_head(stack->vals);
    stack->vals = list_delete(val, stack->vals);
    return val;
}

// return true if stack is empty
int is_empty(stack_t stack)
{
    return (stack->vals == NULL);
}

// return top item from stack but don't remove it
int top(stack_t stack)
{
    return list_head(stack->vals);
}

// return number elements in stack
int size(stack_t stack)
{
    return list_length(stack->vals);
}

// free a stack
void destroy(stack_t stack)
{
    free_list(stack->vals);
    free(stack);
}

//display contents of stack
void show(stack_t stack)
{
     printf("Stack: TOP");
     show_list(stack->vals);
}
