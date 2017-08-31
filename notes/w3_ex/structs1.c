#include <stdio.h>
#include <stdlib.h>

#ifdef COMPACT
struct _s1 {
   int a; int c; int e; char b; char d; char f;
};
#else
struct _s1 {
   int a; char b; int c; char d; int e; char f;
};
#endif

typedef void *addr;

int main(void)
{
   addr       p1;
   struct _s1 s1;

   p1 = &s1;
   printf("sizeof(s1) = %ld\n", sizeof(s1));
   printf("d offset = %ld\n", (addr)&(s1.d) - p1);
   printf("e offset = %ld\n", (addr)&(s1.e) - p1);

   return 0;
}
