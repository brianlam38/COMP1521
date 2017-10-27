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









