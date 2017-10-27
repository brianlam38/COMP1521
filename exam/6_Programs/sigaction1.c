// Example of using sigaction() to set up
// a signal handler with 1 signal arg
 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
 
void handler (int sig)
{
   printf ("Got signal %d\n", sig);
}
 
int main (int argc, char *argv[])
{
   struct sigaction act;
 
   memset (&act, '\0', sizeof(act));
 
   // Use the sa_sigaction field because
   // the handler has two additional parameters
   act.sa_handler = &handler;

   if (sigaction(SIGHUP, &act, NULL) < 0) {
      perror ("sigaction");
      return EXIT_FAILURE;
   }
 
   if (sigaction(SIGTERM, &act, NULL) < 0) {
      perror ("sigaction");
      return EXIT_FAILURE;
   }
 
   while (1) sleep (10);
 
   return EXIT_SUCCESS;
} 

