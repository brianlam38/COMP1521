====== 'UNIX-LINUX FILE SYSTEMS | FILE SYS OPERATIONS' ======

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


====== 'OS | PROCESS MANAGEMENT | SIGNALS' ======

OS provides processes with:
-> 'Control-flow independence' - process executes as if its the only process running
-> 'Private address space' - process has its own address space, possibly larger than physical memory

Process Pre-emption:
-> In reality, each process uses the CPU until pre-empted / temporarily interrupted by another process.
-> Their entire dynamic state must be:
   [1] 'SAVED' [2] flagged as 'TEMPORARILY SUSPENDED' [3] placed on a 'PRIORITY QUEUE' for re-start

Signals:
-> A notification sent to a process or thread











