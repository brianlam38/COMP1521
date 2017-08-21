// stk.c ... manipulate stacks
// Written by jas@cse, May 2017

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

void printHelp();

// main program reads/executes stack commands

int main(void)
{
    stack_t stack;     // the Stack
    char line[BUFSIZ]; // input line buffer
    char cmd;          // current command
    int  val;          // value for current command
    int  nargs;        // # args for command
    int  changed;      // did last cmd change stack?

    // create empty stack
    stack = create();

    // read/execute commands
    printf("Stacks 1.0\n");
    printf("> ");
    while (fgets(line, BUFSIZ, stdin) != NULL) {
        changed = 0;
        nargs = sscanf(line, "%c %d", &cmd, &val);
        if (cmd == '+' && nargs == 2) {
            push(stack, val);
            changed = 1;
        }
        else if (cmd == '-') {
            if (is_empty(stack)) {
                printf("Can't pop\n");
            } else {
                val = pop(stack);
                printf("Popped %d\n", val);
                changed = 1;
            }
        } 
        else if (cmd == 't') {
            val = top(stack);
            printf("Top is %d\n", val);
            changed = 0;
        }

        else if (cmd == '?') {
            if (is_empty(stack)) {
                printf("Empty\n");
            } else {
                printf("Not empty\n");
            }
        }
        else if (cmd == '#') {
            printf("Size is %d\n", size(stack));
        }
        else if (cmd == 'd') {
            destroy(stack);
            //stack = create();
        }
        else if (cmd == 'p') {
            changed = 1;
        }
        else if (cmd == 'q') {
            break;
        }
        else {
            printf("Invalid command!\n");
            printHelp();
        }
        if (changed) {
            show(stack);
        }
        printf("> ");
    }
    destroy(stack);
    printf("\n");
    return EXIT_SUCCESS;
}

void printHelp()
{
     printf("Possible commands:\n");
     printf("+ N ... push N onto stack\n");
     printf("-   ... pop top element\n");
     printf("t   ... show top element\n");
     printf("?   ... check whether stack is empty\n");
     printf("#   ... show height of stack\n");
     printf("p   ... show current stack\n");
     printf("d   ... destroy current stack\n");
     printf("q   ... quit the program\n");
}
