// MEMORY MANAGEMENT

Operating systems provide a view of memory for individual processes.

Scenarios for memory addressing mapping:

'SCENARIO 1: SINGLE PROCESS (OLD DAYS)'
-> The process could use up entire memory.
-> Addresses within the process code are absolute.
-> Easy to implement by initialising $sp to psize-4

'SCENARIO 2: TWO PROCESSES LOADED INTO MEMORY AT ONCE'
-> Addresses in P1 are absolute
-> ALL Addresses in P2 need to be interpreted relative to P1_SIZE
-> How do I sort out P2 addresses?
	Replace all addresses by ADDR + P1_SIZE when loading process code+data
	Each mem reference is mapped by extra hardware on the fly.

'SCENARIO 3: MULTIPLE PROCESSES LOADED INTO MEMORY AT ONCE'
-> If we do on-the-fly address mapping, we need to:
	Remember base address for each process (process table)
	When process restarts, load base address into mapping hardware
	Interpret every address ADDR in program as BASE+ADDR
-> Each process sees its own address space as [0 ... PSIZE-1]
	So the process can be loaded anywhere in memory without change.

'SCENARIO 3 + EXTRA: ADD A NEW PROCESS'
-> The new process doesnt fit into unused slots: 'move some processes to make a single large slot'
-> Alternative: 'split new process memory over two regions'
-> Implications for splitting process memory across physical mem:
	Each chunk of process addr space has its own 'base'
	Each chunk of process addr space has its own 'size'
	Each chunk of process addr space has its own 'memory location'
-> Need a table of process/address info to manage this.
	
	Example:
	PROCESS ADDRESS MAPPING TABLE

	P[0] [ - - - - ]
					  'base'   'size'     'mem'
	P[1] [ P1_SIZE ] [  0  ][ P1_SIZE ][    0    ]
	  .
	  .				  'base'   'size'     'mem'
	P[4] [ P4_SIZE ] [  0  ][ P4_SIZE ][  20000  ] 
	  .
	  .				  'base'   'size'     'mem'		  'base'     'size'		   'mem'
	P[7] [ P7_SIZE ] [  0  ][  a - 1  ][   5000  ] [    a    ][ P7_SIZE-a ][   25000   ]
												   <------------------------------------>
											 A process addr space w/ its own base, size, mem location

Under this scheme, address mapping calculation is complicated.

		Address processToPhysical(pid, addr)
		{
		   Chunk chunks[] = getChunkInfo(pid);
		   for (int i = 0; i < nChunks(pid); i++) {
		      Chunk *c = &chunks[i];
		      if (addr >= c->base && addr < c->base+c->size)
		         break;
		   }
		   uint offset = addr - c->base;
		   return c->mem + offset;
		}

Address mapping would be simpler if all chunks were the same size
-> A call to each chunk of address space of a 'page'
-> All pages are the same size 'PageSize'
-> A specific process memory is spread across 'ProcSize / PageSize' pages
-> 'Page i' contains addresses to range 'i * PageSize ... (i+1) * PageSize - 1'
Also leads to simpler address mapping table:

	EXAMPLE:
	SIMPLIFIED ADDRESS MAPPING TABLE

	P[0] [ - - - - ]
					    'mem'
	P[1] [ P1_SIZE ] [    0    ]
	  .
	  .				    'mem'
	P[4] [ P4_SIZE ] [  20000  ] 
	  .
	  .				    'mem'		'mem'
	P[7] [ P7_SIZE ] [   5000  ] [  25000  ]

Mapping from process address -> physical address is very simple:

		Address processToPhysical(pid, addr)
		{
		   PageInfo pages[] = getPageInfo(pid);
		   uint pageno = addr / PageSize;  // integer div
		   uint offset = addr % PageSize;
		   return pages[pageno].mem + offset;
		}
		// Computaton of pageno and offset is a single MIPS instruction (more efficient)
		// We are also allowing more complex PageInfo entries

// VIRTUAL MEMORY
A side-effect of this type of process -> physical address mapping:
-> Dont need to load all process pages upfront
-> Start with a 'small memory footprint' (e.g. main + stack top)
-> Load new process address pages into memory as needed
-> Grow up to the size of the available physical memory

'Virtual Memory' is the strategy of:
-> Dividing process memory space into fixed-size pages
-> On-demand loading of process pages into physical memory
In this context, we call Process Addresses as 'virtual addresses'

'Page Frames'
-> Are page-sized regions of memory
-> Are typically 512 bytes ... 8 kb in size
-> In a 4 gb memory, would =~ 4million x 1kb page frames
-> Each page frame contains a small region of a processes address space

						 Leads to a memory layout like:

[    0   ][    1   ][    2   ]											   [ nP - 1 ]
[ P1 pg5 ][ P7 pg1 ][ P1 pg0 ][ P4 pg6 ][  free  ][ P7 pg1 ] --- [ P7 pg1 ][ P7 pg1 ]

<----------------------------------------------------------------------------------->
					   ' nP total pages of physical memory '



Memory usage could be managed via. a table which records:
-> Which process the page is allocated to - NULL if not in use
-> Whether the page is currently in use and modified
-> Which chunk it represents within the processes address space

         'PAGE TABLE'						'MEMORY'
   0 [ P1 ][ u+m ][ 35 ]
   1 [ P4 ][  u  ][ 20 ]		0 [ in use by process 1 ,   modified   ]
   2 [ -- ][  -- ][ -- ]		1 [ in use by process 4 , not modified ]
			......								......
nP-2 [ P1 ][  u  ][ 35 ]						......
nP-1 [ P4 ][ u+m ][ 20 ]	 nP-1 [ in use by process 4 ,   modified   ]

'u' = used
'm' = modified


Problems with the table above:
-> To access pages, we provide a page number
-> Need to search the page table to find entry for the page
-> This is 'inefficient'

// ----------- INEFFICIENT SEARCH FOR PAGE IN PAGE TABLE

typedef struct { int pid, char status, int pageno } PageData;
PageData PageTable[nP];  // one entry for each physical page

Address processToPhysical(pid, addr)
{
   int pageno = addr / PageSize;
   int offset = addr % PageSize;
   for (int i = 0; i < nP; i++) {	// O(n) worst case to go through each page in the table
      PageData *p = PageTable[i];
      if (p->pid == pid && p->pageno == pageno)
         break;
   }
   return i*PageSize + offset;  // assumes page is loaded
}
// --------------------------------------------------------


Search could be improved by using hashing:

  'HASH TABLE'		      'PAGE TABLE'							'MEMORY'
  key     val		0 [ P1 ][ u+m ][ 35 ]
(p4,20) [  1  ]		1 [ P4 ][  u  ][ 20 ]		 0 [ in use by process 1 ,   modified   ]
(p7, 0)	[ nP-2]  	2 [ -- ][  -- ][ -- ]		 1 [ in use by process 4 , not modified ]
(p1,35) [  0  ]				......								......
(p4,19) [ nP-1]		nP-2 [ P1 ][  u  ][ 35 ]						......
					nP-1 [ P4 ][ u+m ][ 20 ]  nP-1 [ in use by process 4 ,   modified   ]

					'u' = used
					'm' = modified

typedef struct { int pid, char status, int pageno } PageData;
PageData PageTable[nP];  // one entry for each physical page
int HashTable[>nP];  // at least as many entries as PageTable

Address processToPhysical(pid, addr)
{
   int pageno = addr / PageSize;
   int offset = addr % PageSize;
   int key = hash(pid,pageno);  // index into HashTable
   int i = HashTable[key];      // index into PageTable
   PageData *p = PageTable[i];
   if (p->pid == pid && p->pageno == pageno)
      return i*PageSize + offset;
   else
      // hmmm ... this is not the page we want
}

// --------------------------------------------------------

We can also consider a per-process page table:
-> Each entry contains page status and physical address [if loaded]
-> Potentially, we need upperLim[ ProcSize / PageSize ] entries in this table


typedef struct { char status, int memPage } PageData;
PageData *PageTables[maxProc];  // one entry for each process

Address processToPhysical(pid, addr)
{
   PageData *ProcPageTable = PageTables[pid];
   int pageno = addr / PageSize;
   int offset = addr % PageSize;
   PageData *p = ProcPageTable[pageno];
   if (loaded(p->status))
      return memPage*PageSize + offset;
   else
      // hmmm ... page not currently in memory
}








