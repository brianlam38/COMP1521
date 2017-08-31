#include <stdio.h>
#include <stdlib.h>

int main(void)
{
   double x, y, z;

   x = 1.0;
   y = 7.0;
   z = x/y;
   printf("x = %lf\n", x);
   printf("y = %lf\n", y);
   printf("z = %lf\n", z);

   for (int i = 0; i < 100; i++) x = x * y;
   for (int i = 0; i < 100; i++) x = x / y;
   printf("x = %0.20lf\n", x);

   x = 1.0;
   for (int i = 0; i < 200; i++) {
      if (i%2 == 0)
         x = x * y;
      else
         x = x / y;
   }
   printf("x = %0.20lf\n", x);
}
