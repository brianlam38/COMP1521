# Makefile for Stack ADT Examples

CC=gcc
CFLAGS=-g -Wall -Werror
BINS=stk1 bm

all : $(BINS)

stk.o : stk.c Stack.h
Stack2.o : Stack2.c Stack.h
Stack.o : Stack.c Stack.h
Stack3.o : Stack3.c Stack.h

stk1 : stk.o Stack.o
	$(CC) -o stk1 stk.o Stack.o
stk2 : stk.o Stack2.o list.o
	$(CC) -o stk2 stk.o Stack2.o
stk3 : stk.o Stack3.o
	$(CC) -o stk3 stk.o Stack3.o

bm : bm.o Stack.o
bm.o : bm.c Stack.h

clean :
	rm -f $(BINS) *.o
