#include <stdio.h>
#include <stdlib.h>

struct _bit_fields {
   unsigned int first_bit    : 1,
                next_7_bits  : 7,
                last_24_bits : 24;
};

#if 1
// first attempt

int main(void)
{
   struct _bit_fields x;

   x.first_bit = x.next_7_bits = x.last_24_bits = 0;

   x.first_bit = 1;
   printf("first_bit %08x\n", x);
   x.first_bit = 0;

   return 0;
}

#else
// second attempt

union _bits {
   unsigned int ival;
   struct _bit_fields bval;
};

int main(void)
{
   union _bits x;

   x.bval.first_bit = x.bval.next_7_bits = x.bval.last_24_bits = 0;

   printf("initially %08x\n", x.ival);

   x.bval.first_bit = 1;
   printf("first_bit %08x\n", x.ival);
   x.bval.first_bit = 0;

   x.bval.next_7_bits = 0x7F;
   printf("nxt7_bits %08x\n", x.ival);
   x.bval.next_7_bits = 0;

   x.bval.last_24_bits = 0xFFFFFF;
   printf("last_bits %08x\n", x.ival);
   x.bval.last_24_bits = 0;

   return 0;
}
