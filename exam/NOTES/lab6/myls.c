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
   if (stat(dirname, &info) < 0)
      { perror(argv[0]); exit(EXIT_FAILURE); }
   if ((info.st_mode & S_IFMT) != S_IFDIR)
      { fprintf(stderr, "%s: Not a directory\n",argv[0]); exit(EXIT_FAILURE); }

   // open the directory to start reading
   DIR *df; // UNCOMMENT this line
   df = opendir(dirname);

   // read directory entries
   struct dirent *entry; // UNCOMMENT this line
   
   while ((entry = readdir(df)) != NULL) {
      // get file object name
      char *name = entry->d_name;
      printf("NAME = %s\n", name);
      // get file object meta-data
      lstat(name, &info);
      // convert meta-data to strings
      printf("%s  %-8.8s %-8.8s %8lld  %s\n",
       rwxmode(info.st_mode, mode),
       username(info.st_uid, uname),
       groupname(info.st_gid, gname),
       (long long)info.st_size,
       entry->d_name);
   }



   // finish up
   closedir(df); // UNCOMMENT this line
   return EXIT_SUCCESS;
}

// convert octal mode to -rwxrwxrwx string
char *rwxmode(mode_t mode, char *str)
{
   char rwx[10];
   // Find type of file.
   mode_t type;
   uint mask1 = 56;      // 0b00111000
   type = mask1 & mode;  // remove rwx bits to find out file type
   switch(type) {
      case S_IFDIR:
         rwx[0] = 'd';
         break;
      case S_IFREG:
         rwx[0] = '-';
         break;
      case S_IFLNK:
         rwx[0] = 'l';
         break;
      default:
         rwx[0] = '?';
         break;
   }

   uint mask2 = 0x1FF;   // 0b11111111
   mode = mask2 & mode;  // remove excess bits
   printf("rwx = %o\n", mode);

   //int ownerPos = 0;
   //int groupPos = 3;
   //int otherPos = 6;
   
   /*
   for (int i = 0; i < 9; i++) {
      switch(mode) {
         case 0:
            rwx[i] = 'd';
            break;
         case 1:
            rwx[i] = '-';
            break;
         case 2:
            rwx[i] = 'l';
            break;
         case 3:
            rwx[i] = '?';
            break;
         case 4:
            break;
         case 5:
            break;
         case 6:
            break;
      }
   }
   */




   return NULL;
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
