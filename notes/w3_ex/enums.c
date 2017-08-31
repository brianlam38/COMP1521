#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, YELLOW, BLUE } PrimaryColours;

int main(void)
{
   printf("size = %ld\n", sizeof(PrimaryColours)); 
   for (int col = RED; col <= BLUE; col++)
      printf("%d\n", col);

   return 0;
}
