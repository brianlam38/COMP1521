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
		   -> Declare a { struct sigaction act }  object
		   -> Initialise the struct to '\0' memset(&act, '\0', sizeof(act))

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
		-> 'Information request' : 1. act.sa_sigaction = &hander    -> set sa_sigaction instead of sa_handler
		    		 			 : 2. act.sa_flags = SA_SIGINFO     -> set SA_SIGINFO flag
			You can now access signal info via. struct siginfo_t { }

#####################################
====== 'INTERACTING PROCESSES' ======
#####################################

	Processes can interact with each other in several ways.
	Uncontrolled interaction is a problem and may cause 'NON-DETERMINISTIC' behaviour.
	Mechanisms exist to control process interactions / access to files.

	File Locking flock(int fd, int Operation) controls access to shared files
	-> 'Operation':
			'LOCK_SH' ... acquire shared lock
			'LOCK_EX' ... acquire exclusive lock
			'LOCK_UN' ... unlock
			'LOCK_NB' ... operation fails rather than blocking
	-> flock() only ATTEMPTS to acquire a lock, only works correctly if all processes that access the file use locks
	-> return 0 success | return -1 failure

	FILE LOCKING SCENARIOS:
	1. Process tries to acquire a 'shared lock - LOCK_SH':
	   -> If file NOT locked or other shared locks = OK
	   -> If file locked = BLOCKED
	2. Process tries to acquire an 'exclusive lock - LOCK_EX'
	   -> If file NOT locked = OK
	   -> If file shared or exclusive lock = BLOCKED
	3. If a process is using a 'non-blocking lock'
	   -> return 0  if locked acquired
	   -> return -1 if process would be blocked

###########################
====== 'CONCURRENCY' ======
###########################

	Concurrency = multiple processes running simultaneously.
	Sequential execution = opposite of concurrency, where each process waits their turn.

	Effects of poorly controlled concurrency:
	-> 'Non-determinism'	... same code, different runs, different results each time
	-> 'Deadlock'			... a group of processes end up waiting for each other,
								as they need something from each other to proceed.
	-> 'Starvation'			... a process keeps missing access to a shared resource.
	We need concurrency control methods to address these issues.

	Concurrency Control aims to provide correct sequencing of interactions between processes.
	Co-ordination of access to shared resources.
	
	Two classes of Concurrency Control:
	[1] 'SHARED MEMORY - Semaphores'
		-> Uses a shared variable, manipulated atomically. 'Atomic = appears to the rest of the system to occur instantly'
		-> Blocks access if unavailable
	[2] 'MESSAGE PASSING - Send / Receive'
		-> Processes communicate by sending / receiving messages
		-> Receiver can block, waiting for message to arrive
		-> Sender may block, waiting for message to be received

	Semaphore Operations on LINUX/UNIX:
		#include <semaphore.h>
		int sem_init(sem_t *Sem, int Shared, uint Value) 	... Create a semaphore object, set init value
																-> 'Init value usually = 1'

		int sem_wait(sem_t *Sem) i.e wait()		... if Sem > 0, decrement Sem and continue
													else block process and keep waiting until if condition is broken.
													-> Has variants that dont block, but return error if cant decrement

		int sem_post(sem_t *Sem) i.e signal()	... Increment the value of semaphore Sem + take the first process off the Queue() and run the process
													-> Transfers a blocked process from semaphores waiting -> ready Queue()
													-> 'Fair Release policy' is needed for blocked processes, otherwise 'starvation' is possible.

		int sem_destroy(sem_t *Sem)				... Free all memory associated with sempahore Sem

	Message Passing Operations in C is provided my 'Message Queues'
		#include <mqueue.h>
		mqd_t mq_open(char *Name, int Flags)	... Create a new message queue, or open an existing one

		int mq_send(mqd_t *MQ, char *Msg,		... Adds message 'Msg' to 'MQ message queue'
					int Size, uint Prio)  			-> 'Prio' gives priority from queue MQ
													-> Blocks if MQ is empty, can run non-blocking			
																	
		int mq_close(mqd_t *MQ)					... finish accessing message queue MQ

########################
====== 'NETWORKS' ======
########################

	Internet Communications are based on a '5-layer stack'
	[1] 'Physical Layer' - bits on wires, fibre optic or radio
	[2] 'Link Layer' - ethernet, MAC addressing
	[3] 'Network Layer' - routing protocols, IP
	[4] 'Transport Layer' - data transfer, TCP/UDP
	[5] 'Application Layer' - DNS, HTTP, email, Skype, torrents, FTP etc.

	A 'Socket' is an endpoint for sending / receiving data between two processes.
	
	UNIX socket operations:
	--------------------------------
	#include <sys/socket.h>

	int socket(int Domain, int Type, int Protocol) ... creates a socket. sockets are similar to int fd
		-> 'Domain'   : AF_LOCAL, AF_INET
		-> 'Type'     : SOCK_STREAM | SOCK_DGRAM
		-> 'Protocol' : Communications Protocol [ TCP, UDP, IP etc. ]
		-> Return socket descriptor or -1 on error.
	int bind(int Sockfd, SockAddr *Addr, socklen_t AddrLen) ... associates an open socket with an IP+Port address
	int listen(int Sockfd, int Backlog)						... wait for connection on socket Sockfd
	
	SockAddr = struct sockaddr_in							... C struct containing components of the socket address

	int accept(int Sockfd, SockAddr *Addr, socklen_t *AddrLen)   ... accept a connection on a socket
																	 -> Sockf should already be 'created', 'bound', 'listening'
	int connect(int Sockfd, SockAddr *Addr, socklen_t *AddrLen)  ... connects the socket Sockfd to address *Addr

	--------------------------------

	[1] THE APPLICATION LAYER:
		'IP ADDRESSING': 32 bit identifier + Port Number e.g. 129.68.111.10:80
		'PROTOCOLS': HTTP, Skype etc.
		'DOMAIN NAME SYSTEM (DNS)': provides URL name -> IP address mapping
		-> Implementing across a hierarchy of Name Servers, which resolve names to IP addresses.
		-> Why not centralise DNS? Single point of failure, maintenance of large DB.
		-> Two methods of name resolution [1] Iterated Query ... work done by client [2] Recursive Query ... work done by NS.
		-> Top-Level-Domain TLD .com .org .edu and all country-level domains
		-> Authoritative Name Servers maintain mappings names -> IP addr within an organisation

	[2] THE TRANSPORT LAYER:
		The transport layer deals with:
		-> Data Integrity, Timing, Throughput, Security
		'PROTOCOLS': TCP and UDP
		-> TCP = reliable, connection-orientated, byte-stream
		-> UDP = un-reliable, simple, connectionless, segments

	[3] THE NETWORK LAYER:
		'PROTOCOLS': Internet Protocol IP provides host addressing and routing of packets

	[4] THE LINK LAYER:
		Takes packets from the network layer and transmits them.
		Each host [router] on the network has a network layer implementation, containing a 'Network Interface Card (NIC)'
		Implemented as a combination of hardware/software.
		Services provided: 'flow control', 'error detection', 'error correction'

		Ethernet is a cable physically connecting multiple hosts.
		-> Data is broadcast on cable, tagged with receiver MAC address. Devices recognise their own data using MAC address.
		-> Ethernet is a shared broadcasting medium so there can be:
			'Interference' - Two packets broadcast at the same time
			'Collision'    - Node receives two or more signals at the same time
		-> 'Multiple Access Protocols' handle this.
			'Channel Partitioning' - Partition channel based on time-slices/frequency-bands
			'Random Access'		   - Allow collisions, need mechanisms to recover from collisions
			'Taking Turns'		   - Nodes take turns, nodes with more to send get longer turns







