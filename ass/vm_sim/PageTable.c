// PageTable.c ... implementation of Page Table operations
// COMP1521 17s2 Assignment 2
// Written by John Shepherd, September 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Memory.h"
#include "Stats.h"
#include "PageTable.h"

// Symbolic constants

#define NOT_USED 0
#define IN_MEMORY 1
#define ON_DISK 2

typedef struct _node* Node;
typedef struct _list* List;

/* Linked list
 * Node = Page Table Entry
 * Node Value = Page Number
 */
typedef struct _node {
    int pno;      // page number
    Node next;
} node;

typedef struct _list {
    Node head;
} list;

// PTE = Page Table Entry
// PTE tells you info about a status of a page, with respect to its location in memory,
//   wether its loaded in mem or not.

typedef struct {
   char status;      // NOT_USED, IN_MEMORY, ON_DISK     in_mem = loaded | not_used / on_disk (if page contains initialised data) = not loaded
   char modified;    // boolean: has it changed / been modified since page was loaded
   int  frame;       // memory frame holding this page (where in memory is this process page located - IMPORTANT)
   int  accessTime;  // clock tick for last access (most recently used)
   int  loadTime;    // clock tick for last time loaded
   int  nPeeks;      // total number times this page read (how many times did we look at the page)
   int  nPokes;      // total number times this page modified (how many times did we write data into the page in memory)
   // TODO: add more fields here, if needed ...
} PTE;

// The virtual address space of the process is managed
//  by an array of Page Table Entries (PTEs)
// The Page Table is not directly accessible outside
//  this file (hence the static declaration)

static PTE *PageTable;      // array of page table entries (ptr to first entry)
static int  nPages;         // # entries in page table
static int  replacePolicy;  // how to do page replacement
static int  fifoList;       // index of first PTE in FIFO list (first elt in list)
static int  fifoLast;       // index of last PTE in FIFO list (last elt in list)

// Forward refs for private functions

static int findVictim(int);

/* 
 * LRU and FIFO functions
 */
List newList(void) {
   List l = malloc(sizeof(list));
   assert(l != NULL);
   l->head = NULL;
   return l;
}

void freeList(List l) {
   Node curr = l->head;
   Node prev = NULL;
   while (curr != NULL) {
      prev = curr;
      curr = curr->next;
      free(prev);
   }
   free(l);
}

// initPageTable: create/initialise Page Table data structures

void initPageTable(int policy, int np)
{
   /*
    * Init LRU and FIFO data structures
    */

   // initialising page table
   PageTable = malloc(np * sizeof(PTE));
   if (PageTable == NULL) {
      fprintf(stderr, "Can't initialise Memory\n");
      exit(EXIT_FAILURE);
   }
   // setting policy, ctr of pages, init fifo list
   replacePolicy = policy;
   nPages = np;
   fifoList = 0;
   fifoLast = nPages-1;
   // setting up initial status of all pages in the page table
   for (int i = 0; i < nPages; i++) {
      PTE *p = &PageTable[i];
      p->status = NOT_USED;
      p->modified = 0;
      p->frame = NONE;
      p->accessTime = NONE;
      p->loadTime = NONE;
      p->nPeeks = p->nPokes = 0;
   }
}

// requestPage: request access to page pno in mode
// returns memory frame holding this page
// page may have to be loaded
// PTE(status,modified,frame,accessTime,nextPage,nPeeks,nWrites)

int requestPage(int pno, char mode, int time)
{
   // Page number fits in a range of valid pages
   if (pno < 0 || pno >= nPages-1) {
      fprintf(stderr,"Invalid page reference\n");
      exit(EXIT_FAILURE);
   }
   PTE *p = &PageTable[pno];         // get page table entry
   int fno; // frame number
   switch (p->status) {
   case NOT_USED:                   // if page has never been use before or currently saved to disk
   case ON_DISK:
      // TODO: add stats collection
      fno = findFreeFrame();        // if free frame is in memory, use that
      if (fno == NONE) {            // else findVictim() -> what we have to write
         int vno = findVictim(time);   //          -> returns PAGE no, NOT FRAME no
#ifdef DBUG
         printf("Evict page %d\n",vno);
#endif
         // TODO:
         // if victim page modified, save its frame      // update victim page
         // collect frame# (fno) for victim page
         // update PTE for victim page
         // - new status
         // - no longer modified
         // - no frame mapping
         // - not accessed, not loaded
      }
      printf("Page %d given frame %d\n",pno,fno);
      // TODO:
      // load page pno into frame fno  // update the replacement page
      // update PTE for page
      // - new status
      // - not yet modified
      // - associated with frame fno
      // - just loaded
      break;
   case IN_MEMORY:                  // if the page IS in memory, indicate that we got a page table hit
      // TODO: add stats collection // we are done
      break;
   default:
      fprintf(stderr,"Invalid page status\n");  // if any other case, invalid page status and we should fix it
      exit(EXIT_FAILURE);
   }
   if (mode == 'r')           // update peek
      p->nPeeks++;
   else if (mode == 'w') {    // update pokes + modified
      p->nPokes++;
      p->modified = 1;
   }
   p->accessTime = time;      // update access time
   return p->frame;           // return FRAME (which is located in physical memory)
}

// findVictim: find a page to be replaced
// uses the configured replacement policy

// Work out a page victim to be replaced
// Least Recently Used / First in first out
static int findVictim(int time)              // you can add new data structures
{
   int victim = 0;
   switch (replacePolicy) {
   case REPL_LRU:
      // TODO: implement LRU strategy
      // SETTING BITS (most recent -> least recent)
      // 4. USED, MODIFIED
      // 3. USED, NOT MODIFIED
      // 2. NOT USED, MODIFIED
      // 1. NOT USED, NOT MODIFIED
      // When a page is referenced, mark referenced = 1
      // When a page is modified, mark modified = 1
      // When replacement is needed, grab lowest / least referenced class (not used, not modified)
      //    Pick a page at random within that class

      break;
   case REPL_FIFO:
      // TODO: implement FIFO strategy
      // Implement using a LIST (head and tail)
      // Keep track of all pages in a queue
      //    Most recent page = tail of list
      //    Oldest arrival in memory = head of list
      // When replacement is needed, grab head of the queue
      break;
   case REPL_CLOCK:
      return 0;
   }
   return victim;
}

// showPageTableStatus: dump page table
// PTE(status,modified,frame,accessTime,nextPage,nPeeks,nWrites)

void showPageTableStatus(void)
{
   char *s;
   printf("%4s %6s %4s %6s %7s %7s %7s %7s\n",
          "Page","Status","Mod?","Frame","Acc(t)","Load(t)","#Peeks","#Pokes");
   for (int i = 0; i < nPages; i++) {
      PTE *p = &PageTable[i];
      printf("[%02d]", i);
      switch (p->status) {
      case NOT_USED:  s = "-"; break;
      case IN_MEMORY: s = "mem"; break;
      case ON_DISK:   s = "disk"; break;
      }
      printf(" %6s", s);
      printf(" %4s", p->modified ? "yes" : "no");
      if (p->frame == NONE)
         printf(" %6s", "-");
      else
         printf(" %6d", p->frame);
      if (p->accessTime == NONE)
         printf(" %7s", "-");
      else
         printf(" %7d", p->accessTime);
      if (p->loadTime == NONE)
         printf(" %7s", "-");
      else
         printf(" %7d", p->loadTime);
      printf(" %7d", p->nPeeks);
      printf(" %7d", p->nPokes);
      printf("\n");
   }
}
