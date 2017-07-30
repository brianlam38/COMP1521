// Interface to ADT for a FIFO queue
// COMP1521 17s2 Week01 Lab Exercise
// Written by John Shepherd, July 2017

#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueRep *Queue;

// make a new empty Queue
Queue makeQueue();
// release space used by Queue
void  freeQueue(Queue);
// add a new item to tail of Queue
void  enterQueue(Queue, int, int);
// remove item on head of Queue
int   leaveQueue(Queue);
// count # items in Queue
int   lengthQueue(Queue);
// return total duration in all Queue items
int   volumeQueue(Queue);
// return duration of first job in Queue
int   nextDurationQueue(Queue);
// display jobid's in Queue
void showQueue(Queue);

#endif
