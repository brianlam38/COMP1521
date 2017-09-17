// myls.c ... my very own "ls" implementation

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXDIRNAME 100
#define MAXFNAME   200
#define MAXNAME    20

char *rwxmode(mode_t, char *);
char *username(uid_t, char *);
char *groupname(gid_t, char *);

int main(int argc, char *argv[])
{
   // string buffers for various names
   char dirname[MAXDIRNAME];
   // char uname[MAXNAME+1]; // UNCOMMENT this line
   // char gname[MAXNAME+1]; // UNCOMMENT this line
   // char mode[MAXNAME+1]; // UNCOMMENT this line

   // collect the directory name, with "." as default
   if (argc < 2)
      strlcpy(dirname, ".", MAXDIRNAME);
   else
      strlcpy(dirname, argv[1], MAXDIRNAME);

   // check that the name really is a directory
   struct stat info;
   if (stat(dirname, &info) < 0)
      { perror(argv[0]); exit(EXIT_FAILURE); }
   if ((info.st_mode & S_IFMT) != S_IFDIR)
      { fprintf(stderr, "%s: Not a directory\n",argv[0]); exit(EXIT_FAILURE); }

   // open the directory to start reading       // BRIAN COMMENTS
   DIR *df;                                     // 1. Declare DIR object
   df = opendir(argv[1]);                       // 2. opendir() opens the dir by filename, associates a dir stream
                                                //    with it and returns a pointer to the directory stream.

   // read directory entries
   struct dirent *entry;                        // 1. Declare a Dirent struct, a special struct used to return info about dir entries
   while ((entry = readdir(df)) != NULL) {      // 2. readdir() returns a ptr to the next dir entry.
      printf("[%s]\n", entry->d_name);          //    returns NULL at the end of the directory
   }                                            // 3. Loo through each entry and print struct value.
                                                //    d_name[] is a struct component: a null-terminated file name



   // finish up
   closedir(df);                                // 1. Close DIR object.
   return EXIT_SUCCESS;
}

// convert octal mode to -rwxrwxrwx string
char *rwxmode(mode_t mode, char *str)
{
   return NULL;
   // ... TODO ...
}

// convert user id to user name
char *username(uid_t uid, char *name)
{
   struct passwd *uinfo = getpwuid(uid);
   if (uinfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)uid);
   else
      snprintf(name, MAXNAME, "%s", uinfo->pw_name);
   return name;
}

// convert group id to group name
char *groupname(gid_t gid, char *name)
{
   struct group *ginfo = getgrgid(gid);
   if (ginfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)gid);
   else
      snprintf(name, MAXNAME, "%s", ginfo->gr_name);
   return name;
}
