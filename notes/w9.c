// VIRTUAL MEMORY

Basic idea of virtual memory is that:
-> Process views its virtual address space as [ 0 ... maxAddr ]
-> Memory manager partitions it over fixed-size pages
-> 'Process pages' are loaded into memory when referenced
-> 'Process page table' provides the mapping from virtual->physical pages


(1) Process Address Space - 'A single process with multiple pages / chunks of address space'

		[0]       [1]       [2]       [3]			 [N-2]		[N-1]
		[ page 1 ][ page 2 ][ page 3 ][ page 4 ] ... [ pageN-2 ][ pageN-1 ]

(2) Process Page Table - 'Mapping process & page number to a physical memory address'

(3) Physical Memory - 'Multiple processes running at once, with their respective pages / address spaces'


// ----------- PER-PROCESS PAGE TABLE + Mapping to physical memory

typedef struct { char status, int memPage } PageData;
PageData *PageTables[maxProc];    // one entry for each process

Address processToPhysical(pid, addr)
{
   PageData *ProcPageTable = PageTables[pid];
   int pageno = addr / PageSize;
   int offset = addr % PageSize;
   int frameno;  // which page in memory
   if (loaded(ProcPageTable[pageno].status))
      frameno = ProcPageTable[pageno].memPage;
   else
      // load page into a free frame → frameno ... 
   return frameno * PageSize + offset;
}
// -----------------------------------------------------------

// WORKING SETS

QN: Do we ever need to load all process pages at once?

'The Working Set Model' - From observations of running programs:
-> In any given window of time, a process is likely to access only a small subset of its pages
-> Implications:
	If each process has a relatively small working set, it can hold pages for many active processes in memory at same time
	If only need to hold some of processes pages in memory, process addr space can be larger than physical memory


// Loading pages in physical memory
Where do pages that are loaded into physical memory actually come from?
-> Code is 'loaded from the exe' file stored on disk
-> 'Global data' is also initially loaded from here
-> 'Dynamic (heap, stack) data' is created in memory

Consider a process whose 'addr space > physical memory'
-> The pages of dynamic data not currently in use may need to to 'removed temporarily from memory',
   thus would also be 'saved on disk' and 'restored from disk'.

We can imagine that a processes addr space:
-> Exists on disk for the duration of the processes execution
   and only some parts of it are in memory at any given time.

Transferring pages between disk <-> memory is VERY EXPENSIVE.
We need to ensure 'minimal reading from / writing to disk'.


		Per-Process Page Table, allowing for some pages to be not loaded

         'PAGE TABLE'					'MEMORY'
   0 [      memory     ]		0 [	    PT[0] PAGE   ]
   1 [       disk      ]		1 [	   PT[N-1] PAGE  ]
   2 [		 disk      ]		2 [	    other pages  ]
   			. . .
 N-2 [     - - - -     ] 				  'DISK'
 N-1 [ memory modified ]	    0 [     PT[1] PAGE	 ]	
 							 'PAGE N-2 NOT YET CREATED ON DISK'

What do we do if the page is NOT loaded?
-> Requesting a non-loaded page is a 'page fault'
-> One approach to handling a page fault is to 'find a free (unused) page frame in memory and use that'
   
   // PER-PROCESS PAGE TABLE + HANDLING PAGE FAULTS
   // load page into a free frame ...
   else {
      frameno = getPageFrame();
      p->memPage = frameno;
      p->status  = LOADED;
   }

This assumes that we have a way of quickly identifying free page frames.
This is commonly handled via. a 'free list'
(pages allocated to a process become 'free' when the process exits)

What happens if there are currently NO FREE PAGE FRAMES? You can:
-> 'Suspend' the requesting process until a page is freed.
-> 'Replace' one of the currently loaded/used pages

With 'PAGE SUSPENSION', it requires the process manager to:
-> 'Maintain a priority queue' of processes waiting for pages
-> 'Dequeue and schedule' the first process on queue when a page is freed.

With 'PAGE REPLACEMENT':
-> If its been modified since loading, save to disk
	[ we now need a flag to indicate modified or not]
	#define LOADED 	  0x00000001
	#define MODIFIED  0x00000002
-> Grab its frame number and give it to the requester
How to decide which frame should be replaced?
-> Maintain a 'usefulness' measure for each frame / grab frame with lowest usefulness

Factors to consider in deciding which page to replace:
-> Best page to replace = 'wont be used again' by its process
-> Prefer pages that are 'Read Only'	( no need to write to disk )
-> Prefer pages that are 'Un-modified'  ( no need to write to disk )
-> Prefer pages that are used by only one process

Operating Sys cant predict whether a page will be required again by its process.
But we do know whether it has been used recently [ if we record this ]

Useful heuristic: 'LRU replacement' - A page not used recently may not be needed again soon
This working set model helps VMs avoid 'thrashing'

Other strategies:
'First in first out'
-> Page frames are entered into a queue when loaded
-> Page replacement uses the frame at the front of the queue
'Clock Sweep'
-> Maintains a referenced bit for each frame, updated when page is used
-> Maintains a circular list of allocated frames
-> Uses a 'clock hand' which iterates over the page frame list
-> Page replacement uses first-round unreferenced frame, skipping over
   and resetting referenced bit in all referenced pages.

// PAGE TABLES REVISITED
A virtual address space with N pages needs N Page Table entries.
Since N may be large, we do not want to store whole Page Table, especially since working set tells us n << N needed at once
One possiblity: PT with n < N entries and hashing

Alternative strategy: Multi-level page TABLES

Virtual Memory allows sharing of read-only pages e.g. library code
-> Several processes include the same frame in their virtual address space.

// ASSIGNMENT 2
Simulation of Virtual Memory management system.
-> Representation for physical and virtual memory spaces.
-> Read process traces [ sequences of page references ]
-> Implement effect of each reference on pages/frames
-> Collect and display statistics
-> Do this for different page replacement strategies.
'Process Trace': sequence of (mode, page#), where mode = "r" or "w"
-> Each (mode, page#) represents an action over one clock tick.
-> r0 w3 r1 r0 r2 w3 r0 w3 r2 w2 r0 w3 r0 w2 r0 r1

Data structures representing address spaces:

  			 0    1    2           nP - 1  	
PageTable  [ - ][ - ][ - ] - - - [    -   ]	'Represents Virtual/Process Address Space'
		  		  PTE

Memory       0    1    2           nF-1
		   [ - ][ - ][ - ] - - - [  -  ]	'Represents Physical Memory'
		   		 MFI 							+ SUMMARY STATISTICS

Data structures representing page tables and frames:

		'PTE = Page Table Entry'	'MFI = Memory Frame Info'

			|    status     |       	|      page#         |
			|	modified?	|			|     whenLoaded     |
			|	  frame#	|			|       stats        |
			|	whenLoaded	|
			|  whenAccessed |
			|	listLinks	|
			|	   stats 	|

### 'Main Program:' ###

		collect (from argv) Policy, #Pages, #Frames
		initialise Stats, PageTable, Memory
		time = 0
		while (getNextReference(&mode,&page#))
		{
		   // mode is either r or w
		   // page# is value in 0..#Pages-1
		   requestPage(page#, mode, time)
		   time++
		}
		show summary stats
		show frame stats
		show page table stats


### Page request handler ###

		int requestPage(page#, mode, time)
		{
		   	P = PageTable[page#]
		   	switch (status of P)
		   		case IN_MEMORY:
		    		pageHit
		   		case NOT_USED:
		   		case ON_DISK:
		    		pageFault
		    		F = find a frame for P to use
		    		set P''s frame to F

		   	if (mode is write) set P to modified
		   	update P''s access time
		   	return P''s frame#
		}


### Finding a frame F for a page P to use ###

		if (there are free frames) {
		   F = one of the free frames
		}
		else {
		   V = find a page to replace using Policy
		   if (V is modified) save to disk
		   F = V''s frame
		   load P''s data into F (from disk)
		   reset P''s data (modified, etc.)
		}

### Finding a page to replace using LRU ###
-> This will be much better if we have a list of pages ordered by load time
-> When we re(load) P, move P to the back of the list (restart load time)

oldest = now
victim = NONE
for (i = 0; i < #Pages; i++) {
   P = PageTable[i]
   if (P''s accessTime < oldest) {
      oldest = P''s accessTime	// access time
      victim = P''s page
   }
}

### Finding a page to replace using FIFO ###
-> Better if we have a list of pages ordered by access time
-> On access to Page, move Page to the back of the list

oldest = now
victim = NONE
for (i = 0; i < #Pages; i++) {
   P = PageTable[i]
   if (P''s loadTime < oldest) {
      oldest = P''s loadTime	// load time
      victim = P''s page
   }
}

// ASSIGNMENT 2

Add statistics collection at appropriate points.
Convert linear scans to appropriate lists.
Do this for LRU and FIFO. Challenge: do Clock as well.

// PROCESSES

A process is an instance of an executing program.
-> 'Static info': program code and data
-> 'Dynamic state': heap, stack, registers, program counter
-> 'OS-supplied state': environment variables, stdin, stdout
Process management forms a critical component of OS functionality.

OS provides processes with:
-> 'Control-flow independence' - the process executes as if it is the only process running on the machine
-> 'Private address space' - the process has its own address space, possibly larger than physical memory














