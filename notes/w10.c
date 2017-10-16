// PROCESSES
A process is an instance of an executing program.
-> 'Static info': program code and data
-> 'Dynamic state': heap, stack, registers, program counter
-> 'OS-supplied state': environment variables, stdin, stdout

PROCESS MANAGEMENT FORMS A CRITICAL COMPONENT OF O.S FUNCTIONALITY.

OS provides processes with:
-> 'Control-flow independence' - the process executes as if it is the only process running on the machine
-> 'Private address space' - the process has its own address space, possibly larger than physical memory

Control-flow Independence ' "I am the only process and I run until I finish" '
-> In reality, there are multiple processes running on the machine
	- Each process uses the CPU until pre-empted [ temporarily interrupting the process ] or exits
	- Another process uses the CPU until it too is pre-empted
	- Eventually, the 1st process will get another run on the CPU
	
					'Control-Flow Independence'
	TIME ------------------------------------------------>

	P1   ======							 ============			The overall impression is that
	P2		   ========			 ========	     	 ======		3 programs are running simultaneously
	P3				   ==========

'PRE-EMPTION = similar to "saving" the frame to disk if it
				is currently IN_MEMORY, so another page can replace it'

What can cause a program to pre-empt?
-> If it runs 'long enough' and the OS replaces it by a waiting process
-> It attempts to perform a long-duration task, like 'I/O'

More on pre-emption
-> The process''s entire dynamic state must be 'SAVED'













