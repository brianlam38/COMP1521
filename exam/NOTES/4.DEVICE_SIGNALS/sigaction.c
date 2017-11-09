#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

// ############################################################################
// Write a signal handler that catches signals HUP and TERM and print a message
// ############################################################################

// Using sigaction() t set up a signal handler with 1 signal arg

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
 
   // Set ptr to handler functions
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

// ###########################################################################################
// Write a signal handler that catches SEGV (segfault) when an invalid memory reference occurs
// ###########################################################################################

// Signal handler with 1 signal arg
void handler (int sig)
{
   printf ("Invalid memory reference!!\n");

   exit(1);   // exit(1) = EXIT_FAILURE, exit(0) = EXIT_SUCCESS
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

   // Set up signal action
   if (sigaction(SIGSEGV, &act, NULL) < 0) {
      perror ("sigaction");
      return EXIT_FAILURE;
   }
   
   // testing out triggering of segmentation fault -> sending a SIGSEV signal which should be caught
   int *p = NULL;
   *p = 3;
 
   return EXIT_SUCCESS;
}

// #############################################################################
// Write a signal handler that catches TERM, but uses a sa_sigaction to show uid
// #############################################################################

// Handler with 3 args including siginfo_t
void handler (int sig, siginfo_t *siginfo, void *context)
{
   printf ("PID: %ld, UID: %ld\n",
         (long)siginfo->si_pid, (long)siginfo->si_uid);
}
 
int main (int argc, char *argv[])
{
   struct sigaction act;
 
   memset (&act, '\0', sizeof(act));
 
   // Use the sa_sigaction field because
   // the handler has two additional parameters
   act.sa_sigaction = &handler;
 
   // The SA_SIGINFO flag tells sigaction() to use
   // the sa_sigaction field, not sa_handler
   act.sa_flags = SA_SIGINFO;
 
   // Set up signal action
   if (sigaction(SIGTERM, &act, NULL) < 0) {
      perror ("sigaction");
      return EXIT_FAILURE;
   }
 
   while (1) sleep (10);
 
   return EXIT_SUCCESS;
}


===============
'SIGACTION'
===============

int main() {
   struct sigaction act;
   memset(&act, 0, sizeof(act));
   act.sa_handler = SIG_IGN;     -> SIG_IGN is a macro that tells process to ignore signals.
                                       i.e. CTRL+C signal will be ignored if SIG_IGN is used.
                                    Used in place of a handler function.

   if (fork() != 0) {
      // Parent Process
      sigaction(SIGINT, &act, NULL);
      copyInput("Parent");
   } else if (fork() != 0) {
      // Child Process
      sigaction(SIGINT, &act, NULL);
      copyInput("Child");
   } else {
      // Grandchild Process
      copyInput("Grand-child");
   }

   return 0;
}

void copyInput(char *name) {
   pid_t mypid = getpid();
   char line[MAXLINE]
   printf("%s (%d) ready\n", name, mypid);
   while (fgets(line, MAXLINE, stdin) != NULL) {
      printf("%s: %s", name, line);
      sleep(random()%3);
   }
}






