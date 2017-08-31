#include <stdlib.h>
#include <stdio.h>

int main(void)
{
   char a[9] = "a string";
   printf("%p %s\n", a, a);

   char *b = "a string";
   printf("%p %s\n", b, b);

   char c[9] = {'a',' ','s','t','r','i','n','g','\0'};
   printf("%p %s\n", c, c);

#if 0
   char *d = {'a',' ','s','t','r','i','n','g','\0'};
   printf("%p %s\n", d, d);
#endif

   return 0;
}