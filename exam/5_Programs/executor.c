#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main(void)
{  
   pid_t pid;   // process ID
   int stat;    // status

   printf("Parent process starts ...\n");
   if ((pid = fork()) != 0) {
      printf("Parent is waiting ...\n");
      wait(&stat);
      printf("Child status = %08x\n", stat);
   }
   else {
      int   i = 0;
      char  line[50];       // input line buffer
      char *args[100];      // cmd line args
      char *envs[1];        // no env vars
      printf("Give me the argv list (1 per line):\n");
      // until '\n', read 50 bytes from stdin and store in line.
      while (fgets(line, 50, stdin) != NULL) {
         //
         line[strlen(line)-1] = '\0';
         // copy line str and return a ptr to it.
         args[i++] = strdup(line);
      }
      args[i] = NULL; // strip
      envs[0] = NULL; // passes no envp[] values
      // invoke the program, return status
	   stat = execve(args[0], args, envs);
      // only reach here if exec fails
      perror("Exec failed");
   }
   return 0;
}