// ADT for a pool of printers, each with a job queue
// COMP1521 17s2 Week01 Lab Exercise
// Written by John Shepherd, July 2017
// Modified by ...

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "Printers.h"
#include "Queue.h"

// concrete data structure for printer pool
struct PrintersRep {
   int    nprinters;
   int    nextjobid;
   Queue  *queue;
   int    *schedule;
};
   
// create a pool containing N printers
Printers makePrinters(int N)
{
   Printers new;
   int i;
   new = malloc(sizeof(struct PrintersRep));
   assert(new != NULL);
   new->nprinters = N;
   new->nextjobid = 1;
   new->queue = malloc(N*sizeof(Queue));
   assert(new->queue != NULL);
   new->schedule = malloc(N*sizeof(int));
   assert(new->schedule != NULL);
   for (i = 0; i < N; i++) {
      new->queue[i] = makeQueue();
      new->schedule[i] = 0;
   }
   return new;
}

// release memory allocated to Printers
void freePrinters(Printers pool)
{
   assert(pool != NULL);
   int i;
   for (i = 0; i < pool->nprinters; i++) {
      freeQueue(pool->queue[i]);
   }
   free(pool->queue);
   free(pool->schedule);
   free(pool);
}

// remove all completed jobs from pool
void clearPrinterJobs(Printers pool, int nowTime)
{
   assert(pool != NULL);
   int i;
   for (i = 0; i < pool->nprinters; i++) {
      if (pool->schedule[i] <= nowTime
          && lengthQueue(pool->queue[i]) > 0) {
         leaveQueue(pool->queue[i]);
         int next = nextDurationQueue(pool->queue[i]);
         pool->schedule[i] = nowTime + next;
      }
   }
}

// add a new job to the Printer pool
void addPrintersJob(Printers pool, int duration, int nowTime)
{
   assert(pool != NULL);
   int i, minvol, minq;
   minvol = INT_MAX;
   for (i = 0; i < pool->nprinters; i++) {
      int vol = volumeQueue(pool->queue[i]);
      if (vol < minvol) {
         minvol = vol;
         minq = i;
      }
   }
   enterQueue(pool->queue[minq], pool->nextjobid, duration);
   if (lengthQueue(pool->queue[minq]) > 0) {
      // only do this if item actually got added
      int next = nextDurationQueue(pool->queue[minq]);
      pool->schedule[minq] = nowTime + next;
   }
   pool->nextjobid++;
}

// display printer pool queues
void showPrinters(Printers pool)
{
   assert(pool != NULL);
   int i;
   for (i = 0; i < pool->nprinters; i++) {
      printf("[%02d] %3d", i, pool->schedule[i]);
      showQueue(pool->queue[i]);
      printf("\n");
   }
}

