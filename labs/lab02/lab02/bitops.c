// A simple shell for doing bit-oriented operations
// COMP1521 17s2 Week 02 Lab
// Written by John Shepherd, July 2017

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "Bits.h"

#define  DEFAULT_NBITS 64
#define  MAX_LINE      500

#define  bad2Args(a,b,c,d)  ((c = opIndex(a)) < 0 || (d = opIndex(b)) < 0)

void processOptions(int, char **, int *);
int  argIndex(char name);
int  getArgs(char a, int *b, char c, int *d, char e, int *f);
void printHelp();
void trim(char *);

int main(int argc, char *argv[])
{
   int nbits;      // size of Bits objects
   Bits bits[26];  // array of Bits objects named a,b,c,d,...
   char b1;        // name of 1st Bits on input line
   int  i1;        // index of 1st Bits on input line
   char b2;        // name of 2nd Bits on input line
   int  i2;        // index of 2nd Bits on input line
   char b3;        // name of 3rd Bits on input line
   int  i3;        // index of 3rd Bits on input line
   int  shift;     // how far to shift
   char val[MAX_LINE];  // string for literal bit values
   char line[MAX_LINE]; // command line buffer
   
   // process Unix command-line args
   processOptions(argc, argv, &nbits);

   // set up zero'd Bits objects
   for (int i = 0; i < 26; i++) bits[i] = makeBits(nbits);

   // loop to read-and-execute commands on Bits objects
   
   printf("BitOps> ");
   while (fgets(line,MAX_LINE,stdin) != NULL) {
      // if running from a script, show the command
      if (!isatty(0)) fputs(line,stdout);
      // trim spurious spaces
      trim(line);
      // left shift
      if (sscanf(line, "%c = %c << %d", &b1, &b2, &shift) == 3) {
         if (!getArgs(b1,&i1,b2,&i2,0,0)) continue;
         if (shift < 0) { printf("Invalid shift\n"); continue; }
         leftShiftBits(bits[i2], shift, bits[i1]);
         showBits(bits[i1]); printf("\n");
      }
      // right shift
      else if (sscanf(line, "%c = %c >> %d", &b1, &b2, &shift) == 3) {
         if (!getArgs(b1,&i1,b2,&i2,0,0)) continue;
         if (shift < 0) { printf("Invalid shift\n"); continue; }
         rightShiftBits(bits[i2], shift, bits[i1]);
         showBits(bits[i1]); printf("\n");
      }
      // bitwise AND
      else if (sscanf(line, "%c = %c & %c", &b1, &b2, &b3) == 3) {
         if (!getArgs(b1,&i1,b2,&i2,b3,&i3)) continue;
         andBits(bits[i2], bits[i3], bits[i1]);
         showBits(bits[i1]); printf("\n");
      }
      // bitwise OR
      else if (sscanf(line, "%c = %c | %c", &b1, &b2, &b3) == 3) {
         if (!getArgs(b1,&i1,b2,&i2,b3,&i3)) continue;
         orBits(bits[i2], bits[i3], bits[i1]);
         showBits(bits[i1]); printf("\n");
      }
      // bitwise NEG
      else if (sscanf(line, "%c = ~ %c", &b1, &b2) == 2) {
         if (!getArgs(b1,&i1,b2,&i2,0,0)) continue;
         invertBits(bits[i2], bits[i1]);
         showBits(bits[i1]); printf("\n");
      }
      // assignment
      else if (sscanf(line, "set %c = %s", &b1, val) == 2) {
         if ((i1 = argIndex(b1)) < 0) continue;
         if (strlen(val) == 1 && islower(val[0])) {
            // assign from variable
            i2 = argIndex(val[0]);
            setBitsFromBits(bits[i2], bits[i1]);
         }
         else {
            // assign from constant bit-string
            setBitsFromString(bits[i1], val);
         }
      }
      // display
      else if (sscanf(line, "show %c", &b1) == 1) {
         if ((i1 = argIndex(b1)) < 0) continue;
         showBits(bits[i1]); printf("\n");
      }
      else if (line[0] == '?') {
         printHelp();
      }
      else if (line[0] == 'q') {
         break;
      }
      else if (line[0] == '\0') {
         /* ignore empty "command */ ;
      }
      else {
         printf("Invalid command\n");
      }
      printf("BitOps> ");
   }
   printf("\n");
   for (int i = 0; i < 26; i++) freeBits(bits[i]);
   return EXIT_SUCCESS;
}

// Process Unix command-line args
void processOptions(int argc, char **argv, int *nbits)
{
   int status;

   if (argc < 2) {
      *nbits = DEFAULT_NBITS;
      return;
   }
   // why don't we need &nbits??
   status = sscanf(argv[1], "%d", nbits);

   if (status < 1 || *nbits < 8) {
      fprintf(stderr,"%s: Need at least 8 bits\n", argv[0]);
      exit(EXIT_FAILURE);
   }
}

// Converts a Bits name (a,b,c,d,...,x,y,z) into an index
// Returns index or -1 if name not valid
int argIndex(char name)
{
   if ('a' <= name && name <= 'z')
      return (name-'a');
   else
      return -1;
}

// Processes Bits names from input line
// converts them to indexes in the Bits[] array
// if any name is invalid, returns false, otherwise true
int getArgs(char a, int *b, char c, int *d, char e, int *f)
{
   int bad = 0;
   *b = argIndex(a);
   if (*b < 0) {
      printf("Invalid object name: %c\n", a);
      bad++;
   }
   *d = argIndex(c);
   if (*d < 0) {
      printf("Invalid object name: %c\n", c);
      bad++;
   }
   if (e != 0) {
      *f = argIndex(e);
      if (*d < 0) {
         printf("Invalid object name: %c\n", e);
         bad++;
      }
   }
   return (bad == 0);
}

// Remove leading and trailing space from a string
void trim(char *str)
{
   char *s, *t, *w;
   if (str == NULL) return;
   // find first non-space
   s = str;
   while (isspace(*s) && *s != '\0') s++;
   // find last non-space
   t = &s[strlen(s)-1];
   // copy trimmed data into position
   while (isspace(*t) && t > s) t--;
   w = str;
   while (s <= t) { *w = *s; w++; s++; }
   *w = '\0';
}

// Print a help message
void printHelp()
{
   printf("BitOps has 26 bit-string registers named (a..z)\n");
   printf("You can perform various operations on those regisers\n");
   printf("\nCommands: \n");
   printf("X = Y << Number\n");
   printf("X = Y >> Number\n");
   printf("X = Y & Z\n");
   printf("X = Y | Z\n");
   printf("X = ~ Y\n");
   printf("set X = Y\n");
   printf("set X = Bit-string\n");
   printf("show X\n");
   printf("where X,Y,Z are replaced by any lower-case letter\n");
}
