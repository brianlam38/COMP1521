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


// TODO:
// remove the #if 0 and #endif
// once you've added code to use this function

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
      printf("node removed\n");
   }
   free(q);
   assert(q == NULL); 
   printf("queue removed\n");
}

// add a new item to tail of Queue
void  enterQueue(Queue q, int id, int size)
{
   assert(q != NULL);

   printf("=== ADDING NEW NODE TO Q ===\n");
   // TODO
   QueueNode *new = makeQueueNode(id, size);
   assert(new != NULL);

   q->tail->next = new; // add node to tail
   q->tail = new;       // set new tail
   printf("new tail jobid = %d \n", new->jobid);
   printf("new node added to tail\n");
}

// remove item on head of Queue
int   leaveQueue(Queue q)
{
   assert(q != NULL);

   printf("=== REOVING NODE FROM Q HEAD ===\n");
   // TODO
   QueueNode *curr = q->head;
   QueueNode *old = q->head;
   int id = 0;
   
   // make second node the head
   if (curr->next != NULL) {
      curr = curr->next;
      q->head = curr;
      printf("linked new head\n");
   }

   // store id + remove old head memory
   id = old->jobid;
   free(old);
   assert(old == NULL);
      printf("removed old head\n");

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
   int size = 0;
   if (q->head != NULL) {
      size = q->head->size;
   }
   printf("size = %d\n", size);
   return size;
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
