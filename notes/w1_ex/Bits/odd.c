// Playing with bit-strings
// John Shepherd, July 2017

#include <stdlib.h>
#include <stdio.h>

typedef unsigned char Bits8;
typedef unsigned int  Bits32;

int isOdd(int n) { return ((n % 2) == 1); }

int main(int argc, char *argv[])
{
   int num;

   if (argc < 2) {
      fprintf(stderr,"Usage: %s num\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   num = atoi(argv[1]);

   if (isOdd(num))
      printf("It's odd\n");
   else
      printf("It's even\n");

   return EXIT_SUCCESS;
}
