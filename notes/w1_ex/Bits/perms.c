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

   if (argc > 1) {
      if (argv[1][0] == 'r') p = p | OWNER_READ;
      if (argv[1][1] == 'w') p = p | OWNER_WRITE;
      if (argv[1][2] == 'x') p = p | OWNER_EXEC;
   }
   if (argc > 2) {
      if (argv[2][0] == 'r') p = p | GROUP_READ;
      if (argv[2][1] == 'w') p = p | GROUP_WRITE;
      if (argv[2][2] == 'x') p = p | GROUP_EXEC;
   }
   if (argc > 3) {
      if (argv[3][0] == 'r') p = p | PUBLIC_READ;
      if (argv[3][1] == 'w') p = p | PUBLIC_WRITE;
      if (argv[3][2] == 'x') p = p | PUBLIC_EXEC;
   }

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
