// File permissions
// John Shepherd, July 2017

#include <stdlib.h>
#include <stdio.h>

typedef unsigned short Permissions;  // 16 bits

#define OWNER_READ   0x100  // 100000000
#define OWNER_WRITE  0x080  // 010000000
#define OWNER_EXEC   0x040  // 001000000
#define GROUP_READ   0x020  // 000100000
#define GROUP_WRITE  0x010  // 000010000
#define GROUP_EXEC   0x008  // 000001000
#define PUBLIC_READ  0x004  // 000000100
#define PUBLIC_WRITE 0x002  // 000000010
#define PUBLIC_EXEC  0x001  // 000000001

int main(int argc, char *argv[])
{
   Permissions p = 0;

   if (argc < 2) {
      fprintf(stderr,"Usage: %s permissions\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // read permissions as short octal string
   sscanf(argv[1], "%ho", &p);

   printf("Owner:");
   if (p & OWNER_READ)  printf(" read");
   if (p & OWNER_WRITE) printf(" write");
   if (p & OWNER_EXEC)  printf(" execute");
   printf("\n");

   printf("Group:");
   if (p & GROUP_READ)  printf(" read");
   if (p & GROUP_WRITE) printf(" write");
   if (p & GROUP_EXEC)  printf(" execute");
   printf("\n");

   printf("Public:");
   if (p & PUBLIC_READ)  printf(" read");
   if (p & PUBLIC_WRITE) printf(" write");
   if (p & PUBLIC_EXEC)  printf(" execute");
   printf("\n");

   return EXIT_SUCCESS;
}
