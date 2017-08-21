// stk.c ... manipulate stacks
// Written by jas@cse, May 2017

#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

void printHelp();

// main program reads/executes stack commands

int main(void)
{
   Stack stk;       // the Stack
   char line[BUFSIZ]; // input line buffer
   char cmd;        // current command
   char val;        // value for current command
   int  nargs;      // # args for command
   int  changed;    // did last cmd change stack?
   int  done = 0;   // flag to indicate finished

   // create empty stack
   stk = makeStack();

   // read/execute commands
   printf("Stacks 1.0\n");
   printf("> ");
   while (fgets(line, BUFSIZ, stdin) != NULL) {
      changed = 0;
      nargs = sscanf(line, "%c %c", &cmd, &val);
      switch (cmd) {
      case '+':
         if (nargs == 2) {
            pushStack(stk, val);
            changed = 1;
         }
         break;
      case '-':
         if (isEmptyStack(stk))
            printf("Can't pop\n");
         else {
            val = popStack(stk);
            printf("Popped '%c'\n", val);
            changed = 1;
         }
         break;
      case '?':
         if (isEmptyStack(stk))
            printf("Empty\n");
         else
            printf("Not empty\n");
         break;
      case '#':
         printf("Size is %d\n", sizeOfStack(stk));
         break;
      case 'd':
         freeStack(stk);
         break;
      case 'p':
         changed = 1;
         break;
      case 'q':
         done = 1;
         break;
      default:
         printf("Invalid command!\n");
         printHelp();
      }
      if (done) break;
      if (changed) showStack(stk);
      printf("> ");
   }
   freeStack(stk);
   printf("\n");
   return EXIT_SUCCESS;
}

void printHelp()
{
   printf("Possible commands:\n");
   printf("+ N ... push N onto stack\n");
   printf("-   ... pop top element\n");
   printf("?   ... check whether stack is empty\n");
   printf("#   ... show height of stack\n");
   printf("p   ... show current stack\n");
   printf("d   ... destroy current stack\n");
   printf("q   ... quit the program\n");
}
