// bm.c ... Bracket matching
// Written by jas@cse, May 2017

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

void fail(char *);

int main(int argc, char *argv[])
{
    int  ch;  // current input char
    Stack s;  // stack of brackets

    s = makeStack();
    while ((ch = getchar()) != EOF) {
		if (ch == '(' || ch == '[' || ch == '{') {
            pushStack(s, ch);
		} else if (ch == ')') {
		    if (emptyStack(s)) fail("(...)");
            if (popStack(s) != '(') fail("(...)");
		} else if (ch == ']') {
		    if (emptyStack(s)) fail("[...]");
            if (popStack(s) != '[') fail("[...]");
		} else if (ch == '}') {
            if (popStack(s) != '{') fail("{...}");
        }
	}
    if (!emptyStack(s)) fail("close brackets");
    return EXIT_SUCCESS;
}

void fail(char *bracket)
{
    fprintf(stderr, "Mismatch on %s\n", bracket);
    exit(EXIT_FAILURE);
}
