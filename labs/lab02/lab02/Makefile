CC=dcc
CFLAGS=-g -Wall -Werror -std=c99

bitops : bitops.o Bits.o
	$(CC) -o bitops bitops.o Bits.o

bitops.o : bitops.c Bits.h
Bits.o : Bits.c Bits.h

clean :
	rm -f core bitops bitops.o Bits.o

