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
   assert(q != NULL);

   while (q->head != NULL) {        // while not @end
      QueueNode *temp = q->head;
      q->head = temp->next;         // move head to next
      free(temp);                   // remove temp
   }
   free(q);
}

// add a new item to tail of Queue
void  enterQueue(Queue q, int id, int size)
{
   //printf("=== ADDING NEW NODE TO Q ===\n");
   assert(q != NULL);

   QueueNode *new = makeQueueNode(id, size);

   if (q->head == NULL) {
      //printf("q->head = NULL\n");
      q->head = new;
      q->tail = new;
      q->nitems++;
   } else {
      //printf("q->head != NULL\n");
      QueueNode *old = q->tail;
      old->next = new;
      q->tail = new;
      q->nitems++;
   }
}

// remove item on head of Queue
int   leaveQueue(Queue q)
{
   assert(q != NULL);

   // head is null
   if (q->head == NULL) return 0;

   int id = 0;

   // next node is null
   if (q->head->next == NULL) {
      id = q->head->jobid;
      q->nitems--;
      QueueNode *tmp = q->head;
      q->head = NULL;
      free(tmp);
      return id;
   }

   // next node exists, move curr to next, return old head ID
   QueueNode *curr = q->head;
   QueueNode *old = q->head;
   curr = curr->next;
   q->head = curr;
   id = old->jobid;
   q->nitems--;

   free(old);
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

   //printf("=== COUNTING Q VOLUME ===\n");
   if (q->head == NULL) return 0;

   int volume = 0;
   QueueNode *curr = q->head;
   while (curr != NULL) { 
      volume += curr->size;
      curr = curr->next;          
   }
   return volume;
}

// return size/duration of first job in Queue
int   nextDurationQueue(Queue q)
{
   assert(q != NULL);

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
