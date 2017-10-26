// mysh.c ... a very simple shell
// Started by John Shepherd, October 2017
// Completed by <<YOU>>, October 2017

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

extern char *strdup(const char *);
void trim(char *);
char **tokenise(char *, char *);
void freeTokens(char **);
int isExecutable(char *);
void execute(char **, char **, char **);

int main(int argc, char *argv[], char *envp[])
{
   pid_t pid;   // pid of child process
   int stat;    // return status of child
   char **path; // array of directory names

   /* set up command PATH from environment variable */

   // find enviro variable = PATH
   int i;
   for (i = 0; envp[i] != NULL; i++) {
      if (strncmp(envp[i], "PATH", 4) == 0) break;
   }
   // non-existent enviro var PATH
   if (envp[i] == NULL) {
      path = tokenise("/bin:/usr/bin",":");
   }
   // enviro var PATH
   else {
      // &envp[i][5] ignores "PATH="
      // split path by ":" delim
      path = tokenise(&envp[i][5],":");
   }

// --------------- DEBUGGING
#ifdef DBUG
   for (i = 0; path[i] != NULL;i++)
      printf("dir[%d] = %s\n",i,path[i]);
#endif
// --------------- END DEBUGGING

   /* FORM MY OWN SHELL - main loop: print prompt, read line, execute command */

   // shell line of size BUFSIZ (stdio.h defined value)
   // BUFSIZ = gcc default size of 1024 bytes?
   char line[BUFSIZ];
   // print shell name
   printf("mysh$ ");
   // read from stdin and store in line
   while (fgets(line, BUFSIZ, stdin) != NULL) {
      // remove leading/trailing space
      trim(line);
      // user quits shell or enters nothing (re-load shell)
      if (strcmp(line,"exit") == 0) break;          
      if (strcmp(line,"") == 0) { printf("mysh$ "); continue; }

      // tokenise the command
      char **tokens = tokenise(line, " ");
      // Parent process starts
      pid = fork();
      if (pid != 0) {
         wait(&stat);
         //printf("I am the parent.\n");
         //printf("The child has pid %d\n",pid);
      // Child process starts
      } else {
         execute(tokens, path, envp);
         //printf("I am the child.\n");
         //printf("My process id is %d\n",getpid());
         //printf("My parent is %d\n",getppid());
      }

      // cleans up tokens and prints another prompt
      printf("mysh$ ");
      freeTokens(tokens);
   }
   printf("\n");
   return(EXIT_SUCCESS);
}

// execute: run a program, given command-line args, path and envp
void execute(char **args, char **path, char **envp)
{
   // TODO: implement the find-the-executable and execve() it code
   char *command = NULL;
   char *arg0 = args[0];
   if (arg0[0] == '/' || arg0[0] == '.') {
      // cmd = args[0]
      if (isExecutable(args[0])) {
         command = args[0];
      }
   } else {
      for (int i = 0; path[i] != NULL; i++) {
         char *cmd = malloc(strlen(args[0]) + strlen(path[i])+1);
         strcpy(cmd, path[i]);   // "dir"
         strcat(cmd, "/");       // "/"
         strcat(cmd, args[0]);   // "args[0"
         if (isExecutable(cmd)) {
            command = cmd;
            break;
         }
      }
   }





   if (command == NULL) {
      printf("Command not found\n");
   } else {
      printf("Executing %s\n", command);
      printf("envp: %s\n", *envp);
      int stat = execve(command, args, envp);
      if(stat == -1){
        perror("Exec failed");
     }
   }
   _Exit(EXIT_SUCCESS);
}

// isExecutable: check whether this process can execute a file
int isExecutable(char *cmd)
{
   struct stat s;
   // must be accessible
   if (stat(cmd, &s) < 0)
      return 0;
   // must be a regular file
   //if (!(s.st_mode & S_IFREG))
   if (!S_ISREG(s.st_mode))
      return 0;
   // if it's owner executable by us, ok
   if (s.st_uid == getuid() && s.st_mode & S_IXUSR)
      return 1;
   // if it's group executable by us, ok
   if (s.st_gid == getgid() && s.st_mode & S_IXGRP)
      return 1;
   // if it's other executable by us, ok
   if (s.st_mode & S_IXOTH)
      return 1;
   return 0;
}

// tokenise: split a string around a set of separators
// create an array of separate strings
// final array element contains NULL
char **tokenise(char *str, char *sep)
{
   // temp copy of string, because strtok() mangles it
   char *tmp;
   // count tokens
   tmp = strdup(str);
   int n = 0;
   strtok(tmp, sep); n++;
   while (strtok(NULL, sep) != NULL) n++;
   free(tmp);
   // allocate array for argv strings
   char **strings = malloc((n+1)*sizeof(char *));
   assert(strings != NULL);
   // now tokenise and fill array
   tmp = strdup(str);
   char *next; int i = 0;
   next = strtok(tmp, sep);
   strings[i++] = strdup(next);
   while ((next = strtok(NULL,sep)) != NULL)
      strings[i++] = strdup(next);
   strings[i] = NULL;
   free(tmp);
   return strings;
}

// freeTokens: free memory associated with array of tokens
void freeTokens(char **toks)
{
   for (int i = 0; toks[i] != NULL; i++)
      free(toks[i]);
   free(toks);
}

// trim: remove leading/trailing spaces from a string
void trim(char *str)
{
   int first, last;
   first = 0;
   while (isspace(str[first])) first++;
   last  = strlen(str)-1;
   while (isspace(str[last])) last--;
   int i, j = 0;
   for (i = first; i <= last; i++) str[j++] = str[i];
   str[j] = '\0';
}