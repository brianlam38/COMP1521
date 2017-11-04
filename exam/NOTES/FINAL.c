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

#######################################
====== 'OS | PROCESS MANAGEMENT' ======
#######################################

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

##########################
====== 'IO DEVICES' ======
##########################
	
	IO devices allow programs to communicate with the outside world.
	-> 'Device Data' = very slow access [ms], random or sequential, access data in blocks.
	-> 'Memory-based Data' = much faster [ns], random access via. virtual addresses.
		Transfer via. 'units of bytes, words etc.'

	Device Drivers:
	-> Code to control I/O of a device. Often written in assembler + core to an OS.
	-> Each device has its own unique access protocol. Special registers / buffer locations for READ/WRITE
	-> Typical protocol: send request for operation [R/W/Get Status], receive interrupt when request complete.

	Memory-Mapped IO: IO devices are treated as memory locations
	-> Virtual Memory addresses are associated with 'data buffers' / 'control registers' of IO device.
	-> User programs perform IO by getting / putting data into memory.
	-> 'Advantages': Use of existing memory address = Less Hardware + access to full range of CPU instructions.
	-> 'Disadvantages': Using up valuable memory address space for processes.

	Devices on UNIX/LINUX:
	-> Unix treats devices all the same as 'byte-streams' (similar to files)
	-> Devices can be accessed via. '/dev':
	'/dev/diskN' = part of the HD, '/dev/ttyN' = a terminal '/dev/mem' = physical memory, '/dev/random' = rando num generator

	Device Files: a special file that allows software to interact with a device driver using IO system calls.
	-> Two types of Device Files:
	   [1] 'Character Files' provide un-buffered access to hardware devices.
	   [2] 'Block Files' provide byffered access to hardware devices.
	-> 'UN-BUFFERED' R/W one byte at a time | 1 real IO operation per element | VERY SLOW
	-> 'BUFFERED' R/W chunks at a time | data accumulated in buffer | 1 real IO op per chunk of data | FASTER

	I/O Device Operations: ioctl() - Input Output Control
	// Manipulates parameters of special files (on an OPEN fd)
	int ioctl(int FileDesc, int Request, void *Arg)
	-> 'Request' = device-specific request code.
	-> 'Arg' = an int value going to driver OR ptr to data block going to driver or coming from driver
	-> 'Returns' 0 if OK | -1 if ERROR
	// Other standard ones:
	open() | read() | write()

	Buffered IO: using read() from a device byte-by-byte is inefficient.
	-> Data is fed to user program from Buffer without having to access the device each time = 'more efficient'
	-> <stdio.h> library provides buffering of input via. 'BUFSIZ' macro.
	-> Buffering is hidden from the user, who only sees getchar() fgets() etc.

	Example implementation of int getc(fp):
	// read BUFSIZ bytes from open fd into buffer
	if (pos == BUFSIZ) {
		read(fileno(fp), buffer, BUFSIZ);		--> 'fileno(FILE *stream)' returns the fd associated with the
		pos = 0;														   stream pointed to by *stream.
	}
	// return buffer, increment pos
	return buffer[pos++]


#######################
====== 'SIGNALS' ======
#######################

	'Signals' are a notification sent to a process or thread.
	'Signal Handlers' are functions invoked in response to a signal.

	Signal Handler operations:
	---------------------------
		struct sigaction {
			void 		(*sa_handler)(int)   					  ... * to signal handling fn.
			void 		(*sa_sigaction)(int, siginfo_t *, void *) ... * to alt handling fn.
			sigset_t	sa_mask		 							  ... sets signals to be blocked in handler
			int 		sa_flags	 							  ... modifiers (e.g. dont block invoking signal)
		}

		where:
			void (*sa_handler)(int)						   -> takes in a single argument, the invoking signal
			void (*sa_sigaction)(int, siginfo_t *, void *) -> first arg is invoking signal, others are context info e.g. uid, gid

		usage of struct:
			int sigaction(int sig, SigActStruct act, NULL)	-> sigaction(SIGTERM, &act, NULL)
			-> Assigns an action act for a signal int sig.

	Steps for producing signal handler program:
	---------------------------------------------
		1. Create your own function for signal handler behaviour:
		   -> void handler(int signal)
		   -> Used to catches the exception/signal

		2. In main()
		   -> Declare { struct sigaction act } object + initialise it to '\0'
		   -> memset(&act, '\0', sizeof(act))

		3. Passing address of handler() function to sigaction signal handler "when a signal occurs, the handler() function will be executed"
		   -> '1 handler arg'   	: act.sa_handler = &handler    - set your own behaviour -
		   -> '>1 handler args' 	: act.sa_sigaction = &handler  - set your own behaviour -
		   -> 'take default action' : act.sa_sigaction = SIG_DFL   - stake default behaviour -
		   -> 'ignore signal'		: act.sa_sigaction = SIG_IGN   - ignore the signal entirely / program keeps running -

		4. Set up signal handler
		   -> sigaction(SIGUP, &act, NULL)
		   -> sigaction(SIGTERM, &act, NULL)

		5. If signal handler fails:
		    if (sigaction(SIGHUP, &act, NULL) < 0) {
		       perror ("sigaction");
		       return EXIT_FAILURE;
		    }

		Optional things for signal handler program:
		// Blocking certain signal
		-> 'Blocking signals'  	 : act.sa_mask = SIGTERM    - block the SIGTERM signal -

		// Information about the current process
		-> 'Information request' : act.sa_sigaction = &hander    1. set sa_sigaction instead of sa_handler
		    		 			 : act.sa_flags = SA_SIGINFO     2. set SA_SIGINFO flag
			You can now access signal info via. struct siginfo_t { }






