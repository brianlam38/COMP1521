// Example of using sigaction() to set up
// a signal handler
 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
 
// Write a signal handler that catches SEGV (segfault) when an invalid memory reference occurs

// Signal handler with 1 signal arg
void handler (int sig)
{
   printf ("Invalid memory reference!!\n");
   exit(1);
}
 
int main (int argc, char *argv[])
{
   // create sigaction object
   struct sigaction act;
 
   // set sigaction object = 0 -> initialising to 0
   memset (&act, '\0', sizeof(act));
 
   // Use the sa_sigaction field because
   // the handler has two additional parameters
   act.sa_handler = &handler;  // <- pass in handler function

   if (sigaction(SIGSEGV, &act, NULL) < 0) {
      perror ("sigaction");
      return EXIT_FAILURE;
   }
 
   int *p = NULL;
   *p = 3;
 
   return EXIT_SUCCESS;
} 