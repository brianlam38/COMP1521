#include <unistd.h>
#include <stdio.h>

int main(void)
{
   int pid;

   printf("Parent process starts ...\n");
   if ((pid = fork()) != 0) {
      printf("I am the parent.\n");
      printf("The child has pid %d\n",pid);
      // sleep(1); // added to try to get output to interleave
                   // otherwise parent tends to run to completion
                   // before child gets a chance to run
      printf("Parent: my pid is %d\n",getpid());
      printf("Parent: my parent is %d\n",getppid());
   }
   else {
      printf("I am the child.\n");
      printf("Child: my pid is %d\n",getpid());
      printf("Child: my parent is %d\n",getppid());
   }
   return 0;
}
