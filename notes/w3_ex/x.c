#include <stdlib.h>
#include <stdio.h>

typedef unsigned long long bits64;

int main(void)
{
   double x = 2.718281828459;
   printf("%20.20lf\n",(double)4.0/7);
   printf("%10.4lf\n", x);
   printf("%llx\n", (bits64)x);
   return 0;
}
