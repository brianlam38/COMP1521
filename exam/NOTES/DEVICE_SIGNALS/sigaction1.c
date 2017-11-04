// Example of using sigaction() to set up
// a signal handler with 1 signal arg
 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

// ############################################################################
// Write a signal handler that catches signals HUP and TERM and print a message.
// ############################################################################

// A signal handler with 1 signal arg
void handler (int sig)
{
   printf ("Signal has been caught %d\n", sig);
}
 
int main (int argc, char *argv[])
{
   // declare sigaction struct object
   // struct sigaction {
   //    sa_handler
   //    sa_sigaction
   //    sa_mask
   //    sa_flags
   // }
   struct sigaction act;
 
   // write sizeof(act) bytes of '\0' to the string &act
   // Basically initialising the act object = 0
   memset (&act, '\0', sizeof(act));
 
   // Set up signal handler
   act.sa_handler = &handler;

   // handle HUP signal -> default action: termination
   if (sigaction(SIGHUP, &act, NULL) < 0) {
      perror ("sigaction");
      return EXIT_FAILURE;
   }
 
   // handle TERM signal -> default action: termination
   if (sigaction(SIGTERM, &act, NULL) < 0) {
      perror ("sigaction");
      return EXIT_FAILURE;
   }
 
   while (1) sleep (10);
 
   return EXIT_SUCCESS;
} 

