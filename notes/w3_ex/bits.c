#include <stdio.h>
#include <stdlib.h>

struct _bit_fields {
   unsigned int first_bit    : 1;
   unsigned int next_7_bits  : 7;
   unsigned int last_24_bits : 24;
};

int main(void)
{
   struct _bit_fields x;

   x.first_bit = 1;

   printf("%ld\n",sizeof(x));
   printf("%x\n",x.first_bit);
   printf("%x\n",x.last_24_bits);

   return 0;
}
