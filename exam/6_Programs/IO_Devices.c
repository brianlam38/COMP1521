

Comparison between two methods to perform I/O buffering:


=== 'METHOD 1: FILE *' ===

#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 10000

int main(void)
{
   int  n;
   char ch[BUFSIZE];

   while ((n = read(0, &ch, BUFSIZE)) != 0)
      write(1, &ch, n);

   return 0;
}

=== 'METHOD 2: open File Descriptor' ===

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
   int ch;

   printf("%d\n", BUFSIZ);
   while ((ch = getchar()) != EOF)
      putchar(ch);

   return 0;
}

