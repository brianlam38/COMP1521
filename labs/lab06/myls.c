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
   char uname[MAXNAME+1]; // UNCOMMENT this line
   char gname[MAXNAME+1]; // UNCOMMENT this line
   char mode[MAXNAME+1]; // UNCOMMENT this line

   // collect the directory name, with "." as default
   if (argc < 2)
      strlcpy(dirname, ".", MAXDIRNAME);
   else
      strlcpy(dirname, argv[1], MAXDIRNAME);

   // check that the name really is a directory
   struct stat info;
   if (lstat(dirname, &info) < 0)
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
                                                //    returns NULL at the end of the directory
      // if object is '.' skip
      if (strcmp(entry->d_name,".") == 0) continue;
      lstat(entry->d_name, &info);

      rwxmode(info.st_mode, mode);
      //printf("MODE = %s\n", mode);         // grab mode / type

      username(info.st_uid, uname);                // grab name of owner
      printf("UNAME = [%s]\n", uname);

      groupname(info.st_gid, gname);               // grab name of group
      printf("GNAME = [%s]\n", gname);

      printf("SIZE = [%lld]\n", info.st_size);     // grab file size
      printf("OBJ NAME = [%s]\n", entry->d_name);  // grab name of file
      printf("\n");
   }                                            // 3. Loo through each entry and print struct value.
                                                //    d_name[] is a struct component: a null-terminated file name



   // finish up
   closedir(df);                                // 1. Close DIR object.
   return EXIT_SUCCESS;
}

// convert octal mode to -rwxrwxrwx string
char *rwxmode(mode_t mode, char *str)
{   

    printf("OCTAL MODE = %o\n", mode);

    // Bitwise & operations to determine file type
    // S_IFMT = octal code for "Type of file"
    if ((mode & S_IFMT) == S_IFDIR) {
        printf("directory\n");
    } else if ((mode & S_IFMT) == S_IFREG) {
        printf("regular file\n");
    } else if ((mode & S_IFMT) == S_IFLNK) {
        printf("symbolic link\n");
    } else {
        printf("OTHER\n");
    }

    // print correct filename + read/write privileges

     //#define S_IFMT 0170000           /* type of file */
     //#define        S_IFIFO  0010000  /* named pipe (fifo) */
     //#define        S_IFCHR  0020000  /* character special */
     //#define        S_IFDIR  0040000  /* directory */
     //#define        S_IFBLK  0060000  /* block special */
     //#define        S_IFREG  0100000  /* regular */
     //#define        S_IFLNK  0120000  /* symbolic link */
     //#define        S_IFSOCK 0140000  /* socket */
     //#define        S_IFWHT  0160000  /* whiteout */
    return str;
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
