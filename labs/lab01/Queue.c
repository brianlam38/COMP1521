// ADT for a FIFO queue
// COMP1521 17s2 Week01 Lab Exercise
// Written by John Shepherd, July 2017
// Modified by ...

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Queue.h"

typedef struct QueueNode {
   int jobid;  // unique job ID
   int size;   // size/duration of job
   struct QueueNode *next;
} QueueNode;

struct QueueRep {
   int nitems;      // # of nodes
   QueueNode *head; // first node
   QueueNode *tail; // last node
};

// create a new node for a Queue
static
QueueNode *makeQueueNode(int id, int size)
{
   QueueNode *new;
   new = malloc(sizeof(struct QueueNode));
   assert(new != NULL);
   new->jobid = id;
   new->size = size;
   new->next = NULL;
   return new;
}

// make a new empty Queue
Queue makeQueue()
{
   Queue new;
   new = malloc(sizeof(struct QueueRep));
   assert(new != NULL);
   new->nitems = 0; new->head = new->tail = NULL;
   return new;
}

// release space used by Queue
void  freeQueue(Queue q)
{
   printf("=== FREEING QUEUE ===\n");
   assert(q != NULL);

   QueueNode *curr = q->head;    // curr ptr
   while (curr != NULL) {        // while not @end
      QueueNode *prev = curr;
      curr = curr->next;         // curr = next
      free(prev);                // remove prev  
      assert(prev == NULL);           
   }
   free(q);
   assert(q == NULL); 
}

// add a new item to tail of Queue
void  enterQueue(Queue q, int id, int size)
{
   printf("=== ADDING NEW NODE TO Q ===\n");
   assert(q != NULL);

   // TODO
   QueueNode *new = makeQueueNode(id, size);
   QueueNode *curr = q->head;

   printf("begin loop\n");
   while(curr != NULL) {
      curr = curr->next;
   }
   curr = new;

   printf("linking tail to new\n");
   q->tail = new;
   q->nitems++;
}

// remove item on head of Queue
int   leaveQueue(Queue q)
{
   assert(q != NULL);

   printf("=== REMOVING NODE FROM Q HEAD ===\n");
   // TODO
   int id = 0;

   QueueNode *curr = q->head;
   QueueNode *old = NULL;

   printf("part 1\n");
   if (q->head != NULL) {
      printf("part 2\n");
      curr = curr->next;
      q->head = curr;
      old = q->head;
      id = old->jobid;
      free(old);
   } else {
      printf("part 3\n");
      id = curr->jobid;
      printf("part 4\n");
      free(curr);
   }

   q->nitems--;

   return id;
}

// count # items in Queue
int   lengthQueue(Queue q)
{
   assert(q != NULL);
   return q->nitems;
}

// return total size in all Queue items
int   volumeQueue(Queue q)
{
   assert(q != NULL);
   printf("=== COUNTING Q VOLUME ===\n");
   // TODO
   QueueNode *curr = q->head;    // curr ptr
   int volume = 0;
   while (curr != NULL) {        // while not @end
      printf("summing node size\n");
      volume += curr->size;
      curr = curr->next;          
   }
   printf("TOTAL VOLUME = %d \n", volume);
   return volume; // replace this statement
}

// return size/duration of first job in Queue
int   nextDurationQueue(Queue q)
{
   assert(q != NULL);
   printf("=== COUNTING SIZE OF Q HEAD ===\n");
   // TODO
   if (q->head != NULL) {
      return q->head->size;
   }
   return 0;
}


// display jobid's in Queue
void showQueue(Queue q)
{
   QueueNode *curr;
   curr = q->head;
   while (curr != NULL) {
      printf(" (%d,%d)", curr->jobid, curr->size);
      curr = curr->next;
   }
}
