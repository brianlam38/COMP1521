// CHAPTER 4: File Systems and Operations

====== 'C Pre-Processor / C Compiler' ======

How does the compiler convert C to MIPS?
-> converts #include #define
-> parses code + checks for syntax errors:
   'C Parser' understands C syntax and converts C into a parse tree
-> manage a list of symbols used in program
-> decides on data structures
-> allocates local vars to registers / stack
-> maps control structures to MIPS instructions

====== 'Symbol Table Management + Local Variables' ======

Compiler keeps track of names, resolves symbols to specific locations - data/stack/registers
Two choices for local variables:
-> On the stack = persistent for whole function 	[ use $s? if var is persistent across functions ]
-> In a register = efficient but not many registers [ use $t? if var is used locally only ]

====== 'Operating Systems + System Calls' ======

Core OS functions form the KERNEL.
-> The Kernal is one of the first programs loaded on start-up.
-> It handles the rest of start-up as well as input/output requests from software, translating them into
   data-processing instructions for the CPU.
-> It also handles memory and devices such as the mouse, keyboards, monitors, speakers etc.

An OS like Unix/Linux provides 100s of system calls
-> 'Process mgmt, file mgmt, device mgmt, information mgmt, communication' etc.

User programs invoke system calls through an API. System calls are invoked:
-> 'directly' through a library of sys calls [ e.g. man ]
-> 'indirectly' through functions in C libraries

System calls attempt to perform actions, but may fail.
-> Typically error = -1 / success = 0
-> global variable 'errno'

====== 'Unix/Linux File Systems + File System Operations' ======

File Systems provide a mechanism for managing stored data. It is an important mechanism provided by an OS.
-> Typically on a disk device
-> Handles allocating space to 'Files - a sequence of bytes'
-> Allows access to objects such as files/dirs/processes/sockets by name and enforce access rights
   Objects are referenced via. a path which can be:
   		[1] absolute - full path from root
   		[2] relative - path starts from CWD
-> Maintaining info about these files/ dirs 'meta-data'
-> Dealing with damage on the storage device 'bad blocks'

Unix defines a range of File System types:
-> off_t       ... offsets within files
-> size_t      ... no. of bytes in an object
-> ssize_t     ... sizes of read/written blocks
-> struct stat ... file system object meta-data
	> Stores info about file, but stores no content
	> Requires ino_t, dev_t, time_t, uid_t types etc.

File System object meta-data are stored in inodes:
-> Physical location on storage device of file data
-> Access to a file by name requires a 'directory = effectively a list of (name, inode) pairs'

Steps to access files by name:
1. Open directory and scan for name
2. If !found -> "no such file or directory"
3. If found as 'name, ino' -> access inode table inodes[ino]
4. Collect file metadata:
   -> check access permissions given curr user/group
         if !access -> "permission denied"
   -> collect info about files location and size
   -> update access timestamp
5. Use physical location to access device and read/write the file data

File System Operations:
-> Are functions/syscalls that manipulate objects as a stream of bytes
-> Accessed via. a 'file descriptor' (fd)
-> 'File Descriptor' 1 = stdout

Common operations:
// Open / Close file in path
	int open(char *Path, int Flags) 						... open file system object, return a fd
	int close(int FileDescr) 	   						    ... stop using a fd
// Read / Write / Positioning of fd
	ssize_t read(int FileDescr, void *Buffer, size_t Count) ... read bytes into a buffer from a fd
	ssize_t write(int FileDesc, void *Buffer, size_t Count) ... write bytes from a buffer to a fd
	off_t lseek(int FileDesc, off_t Offset, int Whence)     ... move offset / position within a file
// Getting meta-data
	int stat(char *FileName, struct stat *statBuf)          ... get meta-data about a file system object
	int fstat(int FileDescr, struct stat *statBuf)			... same as stat() except gets data via. an open fd

File stat structure:
	struct stat {
	   dev_t     st_dev;     // ID of device containing file
	   ino_t     st_ino;     // inode number
	   mode_t    st_mode;    // file type + permissions
	   nlink_t   st_nlink;   // number of hard links
	   uid_t     st_uid;     // user ID of owner
	   gid_t     st_gid;     // group ID of owner
	   dev_t     st_rdev;    // device ID (if special file)
	   off_t     st_size;    // total size, in bytes
	   blksize_t st_blksize; // blocksize for file system I/O
	   blkcnt_t  st_blocks;  // number of 512B blocks allocated
	   time_t    st_atime;   // time of last access
	   time_t    st_mtime;   // time of last modification
	   time_t    st_ctime;   // time of last status change
	};



'WRITE()' vs 'PRINTF()' usage:
// struct
	typedef struct _student {
	    int id; char name[99]; float wam;
	} Student;

// FD or PTR variables
	int infd, outfd; 	// file descriptors
	FILE *inf, *outf; 	// file pointers
	Student stu;  		// ... set values in stu.id, etc ...

// writing
	write(outfd, &stu, sizeof(struct _student));
	vs
	fprintf(outf, "%d:%s:%f\n", stu.id, stu.name, stu.wam);

// reading
	read(infd, &stu, sizeof(Student));
	vs
	fscanf(inf, "%d:[^:]:%f\n", &(stu.id), &(stu.name), &(stu.wam));














