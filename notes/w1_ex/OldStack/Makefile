# Makefile for week 09 examples

CC=gcc
CFLAGS=-Wall -Werror
BINS=ll bm stk1 stk2 stk3 que1 que2

all : $(BINS)

ll : ll.o list.o
ll.o : ll.c list.h
list.o : list.c list.h

cl : cl.o clists.c
cl.o : cl.c clists.h
clists.o : clists.c clists.h

stk.o : stk.c stack.h
stack_array.o : stack_array.c stack.h
stack_list.o : stack_list.c stack.h list.h
stack_realloc.o : stack_realloc.c stack.h

stk1 : stk.o stack_array.o
	$(CC) -o stk1 stk.o stack_array.o
stk2 : stk.o stack_list.o list.o
	$(CC) -o stk2 stk.o stack_list.o list.o
stk3 : stk.o stack_realloc.o
	$(CC) -o stk3 stk.o stack_realloc.o

bm : bm.o stack_array.o
bm.o : bm.c stack.h

que.o : que.c queue.h
queue_array.o : queue_array.c queue.h
queue_list.o : queue_list.c queue.h

que1 : que.o queue_array.o
que2 : que.o queue_list.o

clean :
	rm -f $(BINS) *.o
