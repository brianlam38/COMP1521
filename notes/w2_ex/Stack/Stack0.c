// Stack.c ... Stack ADT implementation
// - uses linked list representation
// Written by JOhn Shepherd, July 2017

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

// internal data types
typedef struct _stackNode StackNode;

struct _stackNode {
   char val;         // value of item
   StackNode *next;  // ptr to next item
};

// concrete representation of Stack
struct _stackRep {
   StackNode *items;  // linked list
   int nitems;        // counter
};

// create a new stack
Stack makeStack(void)
{
   struct _stackRep *new;
   new = malloc(sizeof (struct _stackRep));
   if (new == NULL) {
      fprintf(stderr, "Out of memory\n");
      exit(EXIT_FAILURE);
   }
   new->items = NULL;
   new->nitems = 0;
   return new;   
}

// add new item to stack
void pushStack(Stack s, char item)
{
   // TODO
}

// remove top item from stack and return it
char popStack(Stack s)
{
   // TODO
}

// return true if stack is empty
int isEmptyStack(Stack s)
{
   // TODO
}

// return number elements in stack
int sizeOfStack(Stack s)
{
   // TODO
}

// free a stack
void freeStack(Stack s)
{
   // TODO
}

//display contents of stack
void showStack(Stack s)
{
   // TODO
}
