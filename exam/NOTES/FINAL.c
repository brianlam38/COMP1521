############################################################
====== 'UNIX-LINUX FILE SYSTEMS | FILE SYS OPERATIONS' =====
############################################################

	File System Objects:
	-> Files, directories/folders, devices, processes, sockets etc.

	File System Object Types:
	-> off_t: offsets in files			ssize_t: sizes of read/written blocks   
	-> struct stat: object meta-data	size_t: byte size of object

	File System Operations are functions that manipulate objects as a stream of bytes.
	-> Objects are accessed via. a 'file descriptor' -> 'stdin' = 0 | 'stdout' = 1 | 'stderr' = 2.

	Common operations:
	// Open / Close file in path
		int open(char *Path, int Flags) 						... open object, return a fd
		int close(int FileDescr)								... close fd
	// Read / Write / Positioning of fd
		ssize_t read(int FileDescr, void *Buffer, size_t Count) ... read bytes into a buffer from a fd
		ssize_t write(int FileDesc, void *Buffer, size_t Count) ... write bytes from a buffer to a fd
		off_t lseek(int FileDesc, off_t Offset, int Whence)     ... move offset / position within a file
												 'use lseek() to access i^th struct via.' i*sizeof(StructType)
	// Getting meta-data
		int lstat(char *FileName, struct stat *statBuf)         ... get meta-data about a file system object
		int fstat(int FileDescr, struct stat *statBuf)			... same as stat() except gets data via. an open fd

	'WRITE()' vs 'PRINTF()' usage:
	// Struct Student Record
		typedef struct _student {
		    int id; char name[99]; float wam;
		} Student;
		Student stu;   		// declare record
	// FD approach
		int infd, outfd; 	// declare fd
		write(outfd, &stu, sizeof(struct _student));
		read(infd, &stu, sizeof(Student));				-> while ((nbytes = read(in, buf, SIZE) != 0)) { write(1, buf, nbytes) }
	// FILE * approach
		FILE *inf, *outf; 	// declare FILE *
		fprintf(outf, "%d:%s:%f\n", stu.id, stu.name, stu.wam);			  -> write info directly to struct via. FILE *p
		fscanf(inf, "%d:[^:]:%f\n", &(stu.id), &(stu.name), &(stu.wam));  -> read info directly to struct via. FILE *p

	Other Operations:
		int getc(FILE *stream)	-> gets next char   	-> while ((ch = getc(in)) != EOF) { putchar(ch) }
		int putchar(int c) 		-> write to stdout

##############################
====== 'VIRTUAL MEMORY' ======
##############################

	Locality of reference:
	-> A process is likely to access only a small subset of its pages = "The Working Set"
	-> So it only needs to hold at any given time, the processes'' working set

	Page Faults:
	-> Occurs when requesting a non-loaded page
	-> Solved by [1] 'Finding a free page' [2] 'Page Replacement'

	Page Replacement:
	-> if p modified, save to disk, grab fno and return
	-> else grab fno and return

	"Least Recently Used (LRU)"
	-> When a page is ACCESSED, move to HEAD
	-> Replaces least-accessed page = TAIL

	"FIFO"
	-> When a page is LOADED, move to HEAD
	-> Replaces last-loaded page = TAIL

	"CLOCK SWEEP"
	-> Maintains reference bit for each frame, updated when page is used
	-> Maintains circular list of all frames
	-> Iterates over list, replacing the first frame with an unreferenced bit
	-> Skip over + reset frames with referenced bit

#################################################
====== 'OS | PROCESS MANAGEMENT | SIGNALS' ======
#################################################

	OS provides processes with:
	-> 'Control-flow independence' - process executes as if its the only process running
	-> 'Private address space' - process has its own address space, possibly larger than physical memory

	Process Pre-emption:
	-> In reality, each process uses the CPU until pre-empted / temporarily interrupted by another process.
	-> Their entire dynamic state must be:
	   [1] 'SAVED' [2] flagged as 'TEMPORARILY SUSPENDED' [3] placed on a 'PRIORITY QUEUE' for re-start

	Processes are collected into 'Process Groups'
	-> Groups have a unique 'PGID' + allow distribution of signals to a set of related processes.

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
			-> Usage: wait(&status)								return on child state change: 'exiting, sending signal etc.'
		int kill(pid_t pid, int sig) 						... 'send a signal' to a specific process or process group

		int execve(char *Path, char *Argv[], char *Envp)	... Replaces current process by executing an Object
			'Path' must be an executable, binary, script '#!/usr/'
				-> E.g.'/usr/bin:/exe.sh', tokenised by ':'
			'Argv[]' is a ptr to an array of char ptrs to strings
				-> These strings construct the argument list made available for the new process
				-> Argv[0] would typically be the name of the executed program
			'Envp[]' is a ptr to an array of char ptrs to strings
				-> Contains strings of the form key=value
			Success / Error
				-> State of the original process is lost.
				-> New process inherits open file descriptors from original process.
				-> SUCCESS = No return value
				-> ERROR = returns -1 and sets 'errno' (read msg via. strerror(errno) / perror(errno))

	Signals:
	-> A notification sent to a process or thread





