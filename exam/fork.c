#include <unistd.h>
#include <stdio.h>

int main(void)
{
   int pid;

   printf("Parent process starts ...\n");
   if ((pid = fork()) != 0) {
      printf("I am the parent.\n");
      printf("The child has pid %d\n",pid);
   }
   else {
      printf("I am the child.\n");
      printf("My process id is %d\n",getpid());
      printf("My parent is %d\n",getppid());
   }
   return 0;
}