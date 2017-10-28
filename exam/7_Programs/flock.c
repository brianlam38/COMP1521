#include <unistd.h>
#include <stdio.h>
#include <sys/file.h>

-> A program that forks a child, then both child + parent writes to stdout()
-> Without controls, output is interleaved which can cause problems
-> The program uses flock() to control file access, so that each process writes a full line of output before the other.

int main(void)
{
   int pid;
   // fork child
   if ((pid = fork()) != 0) {
      int i; char c;
      setbuf(stdout, NULL);
      // acquire exclusive lock on fd#1 = stdout
      flock(1, LOCK_EX);
      // write to output to alphabet
      for (i = 0; i < 100; i++) {
         c = 'a' + i%26;
         putchar(c);
         if (c == 'z') putchar('\n');
      }
      putchar('\n');
      // unlock
      flock(1, LOCK_UN);
   }
   else {
      int i; char c;
      setbuf(stdout, NULL);
      // acquire exclusive lock on fd#1 = stdout
      flock(1, LOCK_EX);
      for (i = 0; i < 100; i++) {
         c = 'A' + i%26;
         putchar(c);
         if (c == 'Z') putchar('\n');
      }
      putchar('\n');
      // unlock
      flock(1, LOCK_UN);
   }
   return 0;
}

======================================================

#include <unistd.h>
#include <stdio.h>
#include <sys/file.h>

int main(void)
{
   int pid;

   FILE *fp = fopen("Out","w");
   if ((pid = fork()) != 0) {
      int i, j; char c;
      setbuf(fp, NULL);
      for (i = 0; i < 5; i++) {
         flock(fileno(fp), LOCK_EX);
         for (j = 0; j < 26; j++) {
            c = 'a' + j;
            fputc(c,fp);
         }
         fputc('\n',fp);
         flock(fileno(fp), LOCK_UN);
      }
   }
   else {
      int i, j; char c;
      setbuf(fp, NULL);
      for (i = 0; i < 5; i++) {
         flock(fileno(fp), LOCK_EX);
         for (j = 0; j < 26; j++) {
            c = 'A' + j;
            fputc(c,fp);
         }
         fputc('\n',fp);
         flock(fileno(fp), LOCK_UN);
      }
   }
   return 0;
}