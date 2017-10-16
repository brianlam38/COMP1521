/*
 * PROCESSES: Introduction
 */

A process is an instance of an executing program.
-> 'Static info': program code and data
-> 'Dynamic state': heap, stack, registers, program counter
-> 'OS-supplied state': environment variables, stdin, stdout

PROCESS MANAGEMENT FORMS A CRITICAL COMPONENT OF O.S FUNCTIONALITY.

OS provides processes with:
-> 'Control-flow independence' - the process executes as if it is the only process running on the machine
-> 'Private address space' - the process has its own address space, possibly larger than physical memory

/*
 * PROCESSES: Control-Flow Independence
 */

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

/*
 * PROCESSES: Pre-emption
 */

'PRE-EMPTION = similar to "saving" the frame to disk if it
				is currently IN_MEMORY, so another page can replace it'

What can cause a program to pre-empt?
-> If it runs 'long enough' and the OS replaces it by a waiting process
-> It attempts to perform a long-duration task, like 'I/O'

More on pre-emption
-> The process''s entire dynamic state must be 'SAVED'
-> The process is flagged as 'TEMPORARILY SUSPENDED'
-> The process is placed on a 'PROCESS (PRIORITY) QUEUE' for re-start

On resuming, the state is restored and the process starts at saved

Overall impression: I ran until I finished all my computation

/*
 * O.S PROCESS MANAGEMENT: Unix / Linux Processes
 */

OS''s maintain information about processes in Process Control Blocks

'argc' / 'argv' / 'envp' / 'uid' / 'gid' and more...
'stdin'  fd:0
'stdout' fd:1
'stderr' fd:2
return status 0 = OK / !0 = ERROR

Unix provides a range of tools for manipulating processes:
-> COMMANDS
	- 'sh' ... for creating processes via. object-file name
	- 'ps' 'w' 'top' ... all shows process information
	- 'kill' ... send a signal to a process or terminate process
-> SYSTEM CALLS
	- 'fork()' ... create a new child process (copy of curr process)
	- 'execve()' ... convert one process into another by executing object
	- 'wait()' ... wait a for state change in child process
	- 'kill()' ... send a signal to a process
	- '_exit()' ... terminate an executing process (after cleanup)
-> INFO ASSOCIATED WITH PROCESSES
	- 'pid' ... process ID, unique among current processes
	- 'ruid' 'euid' ... real and effective user ID
	- 'rgid' 'egid' ... real and effective group ID
	- current working dir
	- accumulated execution time (user/kernal)
	- user file descriptor table
	- information on how to react to signals
	- ptr to process page table
	- process state ... 'running', 'suspended', 'asleep' etc.
The data is split across a kernal process table entry and a user area

/*
 * O.S PROCESS MANAGEMENT: Process-related System Calls
 */
pid_t fork(void)
	- Creates new process by duplicating the calling process
	- New process = 'child' | Calling process = 'parent'
	- Child has a diff process ID (pid) to the parent
	- in child: fork() returns 0
	- in parent: fork() returns the pid of the child
	- if system call fails, fork() returns -1
	- child inherits copies of parent''s address space and open fd''s
	- child does not inherit copies of pending signals, memory locks
Typically, the child pid is a small increment over the parent pid









