// PageTable.c ... implementation of Page Table operations
// COMP1521 17s2 Assignment 2
// Written by John Shepherd, September 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "Memory.h"
#include "Stats.h"
#include "PageTable.h"

// Symbolic constants

#define NOT_USED 0
#define IN_MEMORY 1
#define ON_DISK 2

typedef struct _node* Node;
typedef struct _list* List;

/* --- DATA STRUCTURE / FUNCTIONS FOR PAGE REPLACEMENT -- */

typedef struct _node {
    int pno;      // page number
    Node next;
} node;

typedef struct _list {
    Node head;
    Node tail;
} list;
// create new list
List newList(void) {
   List l = malloc(sizeof(list));
   assert(l != NULL);
   l->head = NULL;
   l->tail = NULL;
   return l;
}
// free list
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
// append node to list
void append(List l, int pno) {
   Node new = malloc(sizeof(node));
   new->pno = pno;
   new->next = NULL;
   Node curr = l->head;
   if (curr == NULL) {
      l->head = new;
      l->tail = new;
   } else {
      while (curr->next != NULL) {
         curr = curr->next;
      }
      curr->next = new;
      l->tail = new;
   }
}

/* --- LRU AND FIFO FUNCTIONS --- */

// global start time
static int start_time;
static List FIFO;
//static List LRU;

// initialise list for page replacement + timing var
void initStratData(int np) {
   // init clock tick start
   start_time = clock();
   printf("START TIME = %d\n", start_time);
   // init FIFO list + page nodes
   FIFO = newList();
   for (int i = 0; i < np; i++) {
      append(FIFO, i);
   }
}
// show pages in current list
void showPageList(List l) {
   printf("--- SHOWING PAGES IN LIST ---\n");
   Node curr = l->head;
   while (curr != NULL) {
      printf("PAGE NO = %d\n", curr->pno);
      curr = curr->next;
   }
}

// PTE = Page Table Entry
// PTE tells you info about a status of a page, with respect to its location in memory,
//   whether its loaded in mem or not.

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


// initPageTable: create/initialise Page Table data structures

void initPageTable(int policy, int np)
{
   // init page replacement data structures
   initStratData(np);
   showPageList(FIFO);

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
   // check if pno is within valid range
   if (pno < 0 || pno >= nPages) {
      fprintf(stderr,"Invalid page reference\n");
      exit(EXIT_FAILURE);
   }
   // grab page entry
   PTE *p = &PageTable[pno];
   // declare frame no
   int fno;
   switch (p->status) {
      /* --- NOT IN MEMORY --- */
      case NOT_USED:
      case ON_DISK:
         countPageFault();             // pageFault++
         fno = findFreeFrame();        // free frame exists
         if (fno == NONE) {            // page replacement needed
            int vno = findVictim(time);
   #ifdef DBUG
            printf("Evict page %d\n",vno);
   #endif
            /* --- UPDATING VICTIM PAGE --- */
            // init entry to victim page
            PTE *v = &PageTable[vno];
            fno = v->frame;
            // if modified, save frame, flip ON_DISK status
            // NOTE: save is counted in saveFrame()
            if (v->modified == 1) {
               saveFrame(fno);
               v->status = ON_DISK;
            }
            // update v.p status
            if (v->status != ON_DISK) {
               v->status = NOT_USED;
            }
            // reset modified, fno, access/load times    // DOES ACCESS/LOAD TIME RESET TO NONE AFTER FREEING?
            v->modified = 0;
            v->frame = NONE;
            v->accessTime = NONE;
            v->loadTime = NONE;
         }
         printf("Page %d given frame %d\n",pno,fno);
         // clock load time, load page pno into frame fno (ctr exists loadFrame())
         int when = clock();
         loadFrame(fno, pno, when);
         // update PTE for page
         p->status = IN_MEMORY;     // new status
         p->modified = 0;           // just loaded, not yet modified
         p->frame = fno;            // associate page with frame no
         p->loadTime = when;        // update loadTime
         break;
      /* --- IN MEMORY --- */
      case IN_MEMORY:
         // PageHit++, request complete      ---> POSSIBLY MORE STATS?
         countPageHit();
         break;
   default:
      fprintf(stderr,"Invalid page status\n");  // if any other case, invalid page status and we should fix it
      exit(EXIT_FAILURE);
   }
   // READ - update peek, peekCtr++
   if (mode == 'r') {
      countPeekRequest();
      p->nPeeks++;
   // WRITE - update pokes + mod, pokeCtr++
   } else if (mode == 'w') {
      countPokeRequest();
      p->nPokes++;
      p->modified = 1;
   }
   // update access time
   p->accessTime = time;
   return p->frame;
}

// findVictim: find a page to be replaced
// uses the configured replacement policy
// Work out a page victim to be replaced
// Least Recently Used / First in first out
static int findVictim(int time)
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
