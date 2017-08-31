#include <stdio.h>
#include <stdlib.h>

struct _s1 {
   char   a[6];
   int    b;
   char   c;
   double d;
   int    e;
   char   f;
};
typedef
struct _s2 {
   char   aa;
   struct _s1 bb;
   char   cc;
} s2;

typedef unsigned char *addr;

int main(void)
{
   struct _s1 s1;
   struct _s2 s2;
   addr p1, p2;

   p1 = (addr)&s1;
   printf("&s1 = %p\n", p1);
   printf("a offset = %ld\n", (addr)&(s1.a) - p1);
   printf("b offset = %ld\n", (addr)&(s1.b) - p1);
   printf("c offset = %ld\n", (addr)&(s1.c) - p1);
   printf("d offset = %ld\n", (addr)&(s1.d) - p1);
   printf("e offset = %ld\n", (addr)&(s1.e) - p1);
   printf("f offset = %ld\n", (addr)&(s1.f) - p1);

#if 0
   p2 = (addr)&s2;
   printf("&s2 = %p\n", p2);
   printf("a offset = %d\n", &(s2.aa) - p2);
   printf("b offset = %d\n", &(s2.bb) - p2);
   printf("c offset = %d\n", &(s2.cc) - p2);
#endif
   return 0;
}
