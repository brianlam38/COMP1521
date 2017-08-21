#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned long long int BigInt;

// compute x^y

BigInt raise(int x, int y)
{
   BigInt product = 1;
   for (int i = 0; i < y; i++)
      product *= x;
   return product;
}

// efficient 2^n

BigInt powOf2(int n)
{
   assert(n < 64);
   BigInt x = 1;
   return (x << n);
}

int main(void)
{
   int x,y;

   x = 3;
   for (y = 0; y < 5; y++)
      printf("%d^%d = %lld\n",x,y,raise(x,y));

   x = 99;
   for (y = 0; y < 5; y++)
      printf("%d^%d = %lld\n",x,y,raise(x,y));

   for (y = 0; y < 64; y += 3)
      printf("2^%d = %lld\n",y,powOf2(y));
   
}
