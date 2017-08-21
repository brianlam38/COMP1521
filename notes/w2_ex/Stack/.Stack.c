// Stack.c ... Stack ADT implementation
// - uses linked list representation
// Written by JOhn Shepherd, July 2017

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Stack.h"

// internal data types

typedef struct _stackNode StackNode;

struct _stackNode {
   char val;       // value of item
   StackNode *next;  // ptr to next item
};

// concrete representation of Stack
struct _stackRep {
   StackNode *items;  // linked list
   int nitems;      // counter
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
   StackNode *new;
   new = malloc(sizeof (struct _stackNode));
   assert(new != NULL);
   new->val = item;
   new->next = s->items;
   s->items = new;
   s->nitems++;
}

// remove top item from stack and return it
char popStack(Stack s)
{
   StackNode *old;
   char value;
   old = s->items;
   s->items = old->next;
   s->nitems--;
   value = old->val;
   free(old);
   return value;
}

// return true if stack is empty
int isEmptyStack(Stack s)
{
   return (s->nitems == 0);
}

// return number elements in stack
int sizeOfStack(Stack s)
{
   return s->nitems;
}

// free a stack
void freeStack(Stack s)
{
   StackNode *cur, *next;
   cur = s->items;
   while (cur != NULL) {
      next = cur->next;
      free(cur);
      cur = next;
   }
   free(s);
}

//display contents of stack
void showStack(Stack s)
{
   StackNode  *cur;
   printf("Top");
   cur = s->items;
   while (cur != NULL) {
      printf(" '%c'", cur->val);
      cur = cur->next;
   }
   printf("\n");
}
