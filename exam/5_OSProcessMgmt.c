// CHAPTER 5: OS Process Management

====== 'Processes' ======

A process is an instance of an executing program.
Process Management forms a critical component of OS functionality.

OS provides processes with:
-> 'Control-flow independence' - the process executes as if it is the only process running on the machine
-> 'Private address space' - the process has its own address space, possibly larger than physical memory

Process Pre-emption:
-> In reality, each process uses the CPU until pre-empted / temporarily interrupted by another process.
-> The process''s entire dynamic state must be 'SAVED', flagged as 'TEMPORARILY SUSPENDED',
   then placed on a 'PROCESS (PRIORITY) QUEUE' for re-start

====== 'OS Process Management' ======

LINUX / UNIX Processes
-> File Descriptors: 'stdin' fd:0 | 'stdout' fd:1 | 'stderr' fd:2
-> Environment Vars: 'argc' | 'argv' | 'envp' | 'uid' | 'gid' and more...
-> Return status: 0 = ok | !0 = error

Process-related System Calls:
-> Process 0 = schedular | Process 1 = init
-> Lower numbered processes are typically system related
-> Processes are collected into 'Process Groups'
   Groups have a unique 'PGID' + Groups allow distribution of signals to a set of related processes.

Examples of process-related sys calls:

	pid_t fork(void)	... Duplicate parent process, creating a child process. Child_PID typically a small increment over parent_PID.
							Call by parent: fork() = pid_t child_pid
							Call by child: fork() = 0
							Call fails: fork() = -1
	pid_t getpid(void)	... Return 'current process PID'
	pid_t getppid(void) ... Return 'parent_PID of current process'
	pid_t getpgid(void)	... Return 'process group ID'

	int setpgid(pid_t pid, pid_t pgid) ... Set the process group ID of a specified process

	pid_t waitpid(pid_t pid, int *status, int options)	... Pause current process until PID changes state
															'&status' stores info about child process state
															'pid = -1' wait on child
															'pid = 0' wait for any child in process group
															'pid > 0' wait on a specific processes
	pid_t wait(int *status) = waitpid(-1, &status, 0)   ... wait on a child process
															returns on child state change: 'exiting, sending signal etc.'
	int kill(pid_t pid, int sig) 						... 'send a signal' to a specific process or process group

	int execve(char *Path, char *Argv[], char *Envp)	... Replaces current process by executing an Object
		'Path' must be an executable, binary, script '#!/usr/'
		Passes arrays of strings to a new process.
			-> Both arrays terminated by a NULL ptr.
			-> envp[] contains strings fo the form key=value
		State of the original process is lost.
		New process inherits open file descriptors from original process.
		On error, returns -1 and sets 'errno' (read msg via. strerror(errno)) | If successful, does NOT return

====== 'SIGNALS + INTERRUPTS + MULTI-TASKING + SCHEDULING' ======
A signal is a notification sent to a process or to a specific thread within the same process to tell it that an event occurred.

Signals can be generated from multiple sources.
-> From kill(), operating sys timer(), i/o device.

Processes can define how they want to handle signals using:

	signal(int SigID, sighandler_t Handler)		... Handler can be 'SIG_IGN', 'SIG_DFL' or a function
													'SigID' is one of the OS-defined signals.

'Interrupts' are signals which cause normal process execution to be suspended.
-> A 'handler' carries out tasks related to the interrupt.
-> Control is then returned to the original process.

Single process example:
1. Process starts a disk I/O operation - i.e. read a block of data
2. Process then carries out in-memory computations.
3. When data is fetched from disk, process is interrupted.
4. Data is placed in a buffer for later access by the process.
5. In-memory computation resumes.

'In-memory computations' are fast = nano-seconds
'I/O computations' are slow = milli-seconds

OLD WAY: Process invokes I/O --> wait 100ms --> continue process = 'SINGLE-PROCESS'
NEW WAY: Process invokes I/O --> run another process -> continue process = 'MULTI-TASKING'

'MULTI-TASKING'
-> Have a mixture of processes: some are ready to execute, some are blocked awaiting I/O completion
-> Switch between processes for a defined 'time slice'.
-> After timer counts down, current process is 'pre-empted'
-> A new process is selected to run by the 'system scheduler'

'SCHEDULING' - Selecting which process should run next.
-> Processes are organised in a Priority Queue. Highest = head of queue.
-> Factors to determine this:
	System processes > normal processes
	Newer processes > older processes
	Less-memory intense > more memory intense
	Some processes suggest their own priority: (highest) 0 --> 100+ (lowest)

'OS Scheduler' abstract view:
	onTimerInterrupt() {
		save state of currently executing process
		newPID = dequeue(runnableProcessesQueue)
		setup state of newPID e.g. load pages
		transfer control to newPID
	}

Process information is stored in a 'process control block'
-> process identification data: 'pid, ppid, pgid, uid, gid ...'
-> process state data: 			'registers, stack, heap, page table ...'
-> process control data: 		'scheduling state/priority, open files ...'


















