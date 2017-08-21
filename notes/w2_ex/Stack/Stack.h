// Stack.h ... interface to Stack ADT
// Written by John Shepherd, May 2017

#ifndef STACK_H
#define STACK_H

typedef struct _stackRep *Stack;

// create a new stack
Stack makeStack(void);
// free a stack
void freeStack(Stack);
// add new item to stack
void pushStack(Stack, char);
// remove top item from stack and return it
char popStack(Stack);
// return true if stack is empty
int isEmptyStack(Stack);
// return number elements in stack
int sizeOfStack(Stack);
// display contents of stack
void showStack(Stack);

#endif
