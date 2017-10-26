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
      // ignore if object is '.'
      if (strcmp(entry->d_name,".") == 0) continue;

      // fill meta-data from entry into stat info
      lstat(entry->d_name, &info);

      // grab read write permissions
      mode_t ModeInfo = info.st_mode;
      rwxmode(ModeInfo, mode);       

      //printf("==============================\n");

      printf("%s  %-8.8s %-8.8s %8lld  %s\n",
        rwxmode(info.st_mode, mode),     // rwx mode
        username(info.st_uid, uname),   // user
        groupname(info.st_gid, gname),  // group
        info.st_size,                 // file size
        entry->d_name);                 // name of file

      //printf("==============================\n");
    }

    // Close DIR * file pointer object
    closedir(df);
    return EXIT_SUCCESS;
}

// convert octal mode to -rwxrwxrwx string
char *rwxmode(mode_t mode, char *str)
{   

    //printf("OCTAL MODE = %o\n", mode);

    // Bitwise & operations to determine file type
    // S_IFMT = octal code for "Type of file"

    // mode & IFMT -> remove lower bits to determine file type
    if ((mode & S_IFMT) == S_IFDIR) {            
        str[0] = 'd';
        //printf("directory\n");
    } else if ((mode & S_IFMT) == S_IFREG) {
        str[0] = '-';
        //printf("regular file\n");
    } else if ((mode & S_IFMT) == S_IFLNK) {
        str[0] = '1';
        //printf("symbolic link\n");
    } else {
        str[0] = '?';
        //printf("OTHER\n");
    }

    // Mask mode code with 0x1FF (0b111111111) to cut out last 3 octal permission digits
    unsigned mask = 0x1FF;
    printf("MASK = %o\n", mask);
    printf("MODE = %o\n", mode);
    unsigned bits = mode & mask;
    printf("BITS = %o\n", bits);

    // bits & mask, then bitshift 3 positions to remove extra 0's
    unsigned owner = bits & 0x07;           // 0x07  = 0b111
    unsigned group = (bits & 0x38) >> 3;    // 0x38  = 0b111111
    unsigned other = (bits & 0x1C0) >> 6;   // 0x1C0 = 0b111111111
    //printf("owner = %o\n", owner);
    //printf("group = %o\n", group);
    //printf("other = %o\n", other);

    int init_pos = 0;
    int owner_pos = 0;
    int group_pos = 3;
    int other_pos = 6;

    for (int i = 0; i < 3; i++) {
      unsigned type;
      unsigned type_pos;
      if (i == 0) {
        type = owner;
        type_pos = owner_pos;
      }
      if (i == 1) {
        type = group;
        type_pos = group_pos;
      }
      if (i == 2) {
        type = other;
        type_pos = other_pos;
      }
      int true_pos = init_pos + type_pos;
      switch (type) {
        case 0:
          str[1 + true_pos] = '-';
          str[2 + true_pos] = '-';
          str[3 + true_pos] = '-';
          break;
        case 1:
          str[1 + true_pos] = '-';
          str[2 + true_pos] = '-';
          str[3 + true_pos] = 'x';
          break;
        case 2:
          str[1 + true_pos] = '-';
          str[2 + true_pos] = 'w';
          str[3 + true_pos] = '-';
          break;
        case 3:
          str[1 + true_pos] = '-';
          str[2 + true_pos] = 'w';
          str[3 + true_pos] = 'x';
          break;
        case 4:
          str[1 + true_pos] = 'r';
          str[2 + true_pos] = '-';
          str[3 + true_pos] = '-';
          break;
        case 5:
          str[1 + true_pos] = 'r';
          str[2 + true_pos] = '-';
          str[3 + true_pos] = 'x';
          break;
        case 6:
          str[1 + true_pos] = 'r';
          str[2 + true_pos] = 'w';
          str[3 + true_pos] = '-';
          break;
        case 7:
          str[1 + true_pos] = 'r';
          str[2 + true_pos] = 'w';
          str[3 + true_pos] = 'x';
          break;
      }      
    }


//----------  0000    no permissions
//-rwx------  0700    read, write, & execute only for owner
//-rwxrwx---  0770    read, write, & execute for owner and group
//-rwxrwxrwx  0777    read, write, & execute for owner, group and others SECURITY RISK
//---x--x--x  0111    execute
//--w--w--w-  0222    write
//--wx-wx-wx  0333    write & execute
//-r--r--r--  0444    read
//-r-xr-xr-x  0555    read & execute
//-rw-rw-rw-  0666    read & write
//-rwxr-----  0740


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
