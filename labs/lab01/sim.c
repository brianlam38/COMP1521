// Simulate jobs being added to a pool of printers
// COMP1521 17s2 Week 01 Lab
// Written by John Shepherd, July 2017

#include <stdlib.h>
#include <stdio.h>
#include "Printers.h"

#define MAX_TIME 100
#define JOB_FREQ 3

void processArgs(int, char **, int *, int *,int *);

int main(int argc, char *argv[])
{
   int seed;       // random # seed
   int nprinters;  // #printers
   int maxlen;     // max length of jobs
   
   // process command-line args
   processArgs(argc, argv, &nprinters, &maxlen, &seed);

   Printers pool;  // printer pool
   pool = makePrinters(nprinters);

   // run the simulation
   int currentTime = 0;
   int nextJobSize = random()%maxlen + 1;
   int nextJobTime = 0;
   srandom(seed);
   while (currentTime < MAX_TIME) {
      clearPrinterJobs(pool, currentTime);
      // is a new job ready to go
      if (currentTime >= nextJobTime) {
         // time taken for new job
         nextJobSize = random()%maxlen + 1;
         addPrintersJob(pool, nextJobSize, currentTime);
         nextJobTime += random()%JOB_FREQ + 1;
      }
      printf("Printer Queues @ t=%d\n",currentTime);
      showPrinters(pool);
      currentTime++;
   }

   return EXIT_SUCCESS;
}

void processArgs(int argc, char **argv, int *np, int *maxlen,  int *seed)
{

   if (argc < 2) {
      fprintf(stderr, "Usage: %s #Printers maxJobLen [seed]\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   switch (argc) {
   case 2:
      *np = atoi(argv[1]);
      *maxlen = 10;
      *seed = 123;
      break;
   case 3:
      *np = atoi(argv[1]);
      *maxlen = atoi(argv[2]);
      *seed = 123;
      break;
   case 4:
   default:
      *np = atoi(argv[1]);
      *maxlen = atoi(argv[2]);
      *seed = atoi(argv[3]);
      break;
   }
   if (*np < 1) {
      fprintf(stderr, "%s: must have >= 1 printer \n", argv[0]);
      exit(EXIT_FAILURE);
   }
   if (*maxlen < 2) {
      fprintf(stderr, "%s: must have maxJobLen >= 2 \n", argv[0]);
      exit(EXIT_FAILURE);
   }
}
