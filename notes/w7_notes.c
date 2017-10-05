// WEEK 7 NOTES

// 1. C PRE-PROCESsSOR
// 2. MIPS: MAPPING CONTROL STRUCTURES
// 3. FILE SYSTEM FUNCTIONS

/*
 * C Pre-Processor
 */
How does the compiler convert C -> MIPS?
-> Converts #include #define
-> Parse code to make sure syntax is correct
-> Manage a list of symbols used in the program
-> Decide how to rep data structures
-> Alloc local vars to registers / stack
-> Map control structurs to MIPS instructions

Example substitutions:
'#include file.h' = replaces #include by contents of file.h
'#define Name Const' = replaces all occurrences of symbol Name by Constant value
'#define Name(Params) Expression' = replace Name(Params) by Expression

Pre-Processor commands get evaluated before actual compilation.
Code inside pre-processor block doesnt appear when compiled:
	#include Inserts a header from another file
	#define  Substitutes a macro
	#if 	 Tests if a condition is true
	#else	 The alternative for #if
	#elif	 #else and #if
	#endif	 Ends pre-processor conditional
	#error	 Prints error message on stderr
	#ifdef	 Ret true if this macro is defined
	#ifndef	 Ret true if this macro is NOT defined
Usage: Debugging
	// if DEBUG macro is defined (by passing -DDEBUG flag to gcc compiler), then run debugging tests
	#ifdef DEBUG
   		/* Your debugging statements here */
	#endif

// Compiler: Symbol Table Management
Compiler keeps track of names, resolves symbols to specific locations - data/stack/registers

// Local Variables
Two choices for storing local vars:
1. In stack = persist for whole function, but lw/sw needed in MIPS
2. In register = efficient, not many registers but is useful if var is used in small scope

// Expression evaluation
Uses temporary registers:
-> Even complex expressions dont generally need > 3-4 registers

    x = ((y+3) * (z-2) * x) / 4;

   	(y+3)			lw   $t0, y
   					addi $t0, $t0, 3    # t0 = y + 3
   	(z-2)			lw   $t1, z
   					addi $t1, $t1, -2   # t1 = z - 2
   	(y+3) * (z-2)	mul  $t0, $t0, $t1  # t0 = t0 * t1
   					lw   $t1, x
   	^expr * x		mul  $t0, $t0, $t1  # t0 = t0 * x
   					li   $t1, 4
   	^expr / 4		div  $t0, $t0, $t1  # t0 = t0 / 4

// Mapping Control Structures / Control Structure templates

// WHILE TEMPLATE
while (Cond) { Stat1; Stat2; ... }              while (i < N) { p = p*i; i++; }

loop:                                           lw    $s0, 8($sp)    # place N on stack
   MIPS code to check Cond; result in $t0    loop5:
   beqz $t0, end_loop5                          lw    $t1, 4($sp)    # place i on stack
   MIPS code for Stat1                          slt   $t0, $t1, $s0  # (i < N)
   MIPS code for Stat2                          beqz  $t0, end_loop
   MIPS code for ...                            lw    $t0, 0($sp)    # p is on stack
   j    loop                                    mul   $t0, $t0, $t1  # p = p*i
end_loop:                                       sw    $t0, 0($sp)    # store ^p result
                                                add   $t1, t1, 1     # i = i + 1
                                                sw    $t1, 4($sp)    # store ^i result
                                                j     loop
                                             end_loop5:
                                                // other code

// IF, ELSE IF, ELSE TEMPALTE
if (Cond1) Stat1 else if (Cond2) Stat2 else Stat3

if:
   MIPS code to check Cond1; result in $t0
   beqz $t0, else1
   MIPS code for Stat1
   j    end_if
else1:
   MIPS code to check Cond2; result in $t0
   beqz $t0, else2
   MIPS code for Stat2
   j    end_if
else2:
   MIPS code for Stat3
end_if:

// UNIX-LINUX File System
Unix/Linux file system is tree-structured

Unix defines a range of file-system-related types:
   off_t   ... offsets within files
      -> typically long and signed to allow backward references
   size_t  ... number of bytes in some object
      -> unsigned, since objects cant have neg size
   ssize_t ... sizes of read/written blocks
      -> like size_t, but signed to allow for error values
   struct stat ... file system object metadata;
      -> stores info about file, but stores no content
      -> requires ino_t, dev_t, time_t, uid_t

Metadata for file sys objects are stored in inodes;
-> Info on physical location of file data, file type, file size, file ownership,
   access permisssions, timestamps etc.
-> Each file sys volume has a table of inodes in a known location
-> Access to a file by name requires a directory
   (where a directory is a list of 'name, inode' pairs.)

// Steps to access files by name:
1. Open directory and scan for name
2. If !found -> "no such file or directory"
3. If found as 'name, ino' -> access inode table inodes[ino]
4. collect file metadata:
   -> check access permissions given curr user/group
         if !acess -> "permission denied"
   -> collect info about files location and size
   -> update access timestamp
5. Use physical location to access device and read/write the file data

// File system operations
Unix functions/syscalls manipulate objects as a stream of bytes
They are acessed via. a file descriptor [index into a system table]

Common operations:

int open(char *Path, int Flags) -> 'open an object at Path, according to Flags'
   flags:
      O_RDONLY , O_WRONLY , O_APPEND , O_RDWR , O_CREAT - create obj if !exist
   flags can be combined e.g.:
      O_WRONLY | O_CREAT
   if successful, return file descriptor
   if unsucecssful, return -1 and set errno

int close(int FileDesc)
   attempt to release an open file descriptor
   if successful, return 0
   if unsucessful, return -1 and set errno
NOTE: if you remove and obj via. 'rm' it removes the objs entry from a directory,
      but inode and data will persist until all processes accessing the obj close() their handle
      OR all references to the inode from other dirs are removed

ssize_t read(int FileDesc, void *Buffer, size_t Count)
   attempt to read Count bytes from FileDesc into Buffer
   if successful, return no. bytes read = NRead
   if unsuccessful, return -1 and set errno
NOTES: Does not check whether Buffer contains enough space
      Advances the file offset by NRead
      Does not treat "\n" as special
      Once a file is open(), the curr position is maintained as part of the f.d entry
      The curr pos can be modified by read(), write(), lseek()

ssize_t write(int FileDesc, void *Buffer, size_t Count)
   attempt to write Count bytes from Buffer into FileDesc
   if successful, return no. bytes written into FileDesc
   "  " " "
   Does not check whether Buffer has Count bytes of data to write into f.d
   Advances the file offset by NWritten bytes

Example:
1. offset = 0 | current = 1023  | file size = 1024
2. write(fd, buf, 512) 'write 512 bytes from buffer into fd'
3. result:
   offset = 0 | current = 1535  | file size = 1536

-----------------------

// Writing and Printing file records
Files of records can be produced by either:
1. write()ing chunks of bytes from struct objs
2. printing formatted text representation of struct data

Example of write()ing records vs printf()ing records:

         // Struct to be written / read
         typedef struct _student {
             int id; char name[99]; float wam;
         } Student;
         int infd, outfd; // file descriptors
         FILE *inf, *outf; // file pointers

         Student stu;  ... set values in stu.id, etc ...

         // write vs. print
         write(outfd, &stu, sizeof(struct _student));
           vs
         fprintf(outf, "%d:%s:%f\n",
                      stu.id, stu.name, stu.wam);
         // read() vs. print
         read(infd, &stu, sizeof(Student));
           vs
         fscanf(inf, "%d:[^:]:%f\n", // maybe?
                     &(stu.id), &(stu.name), &(stu.wam));

-----------------------

Continuation of common file system operations:

off_t lseek(int FileDesc, off_t Offset, int Whence)
   Set the curr position of the FileDesc
   Offset is in units of bytes and can be neg
   Whence can be:
      SEEK_SET - 'set file pos to Offset from start of file'
      SEEK_CUR - 'set file pos to Offset from curr position'
      SEEK_END - 'set file pos to Offset from end of life'
   Seeking beyond eof leaves a gap which reads as 0 s
   Seeking back beyond start of file sets pos = start of file

int stat(char *FileName, struct stat *statBuf)
   Stores metadata associated with FileName into StatBuf
   Info includes:
      inode number , file type + access mode , owner , group
      size in bytes , storage block size , allocated blocks
      time of fast/access
   return -1 if metadata is !useful

int fstat(int FileDescr, struct stat *StatBuf)
   Same as stat() but gets data via. an open file descriptor

int stat(char * FileName, struct stat *Statbuf)
   Same as stat() but doesnt follow symbolic links

-----------------------

The File System links allow multiple paths to access the same data.
1. HARD LINKS
   -> multiple directory entries referencing the same inode
   -> the two entries must be on the same filesystem
2. SYMBOLIC LINKS (SYMLINK)
   -> A file containing the path name of another file
   -> Opening the symlink opens the file being referenced.

-----------------------

Continuation of common file system operations:

int mkdir(char *PathName, mode_t Mode)
   create a new dir called PathName with mode mode
   if PathName is a/b/c/d
   must not be readable by the writer

   usage: mkdir("newDir", 0755)

int fsync(int FileDesc)
   Ensure that data associated with FileDesc is written to storage
   Linux usually makes heavy use of buffering:
      -> Data written to a file is eventually stored in memory buffers
      -> Eventually, it makes its way onto permanent storage device
   fsync() forces this to happen NOW
   Writing to permanent storage is an expensive operation.

int mount(char *Source, char *Target, char *FileSysType, unsigned long Flags, void *data)
   File systems normally exist on permanent storage devices
   Mount attaches a file system to a specific location in the file hierarchy.
   *Source = storage device e.g. '/dev/disk'
      -> Contains a file system: inode table, data chunks
   *Target 'aka mount point' = path in the file hierarchy
   *FileSysType = specifies a particular layout / drivers
   *Flags = specify various properties of the filesys e.g. 'read only'

USAGE: mount("/dev/disk5", "/usr", "ext3", MS_RDONLY, ...)

// FILE SYSTEMS SUMMARY

Operating systems provide a file system:
   -> As an 'abstraction over physical storage' devices e.g. DISKS
   -> Provide 'named access' to chunks of related data i.e. FileSysType
   -> Providing 'sequential / random' access to contents of files
   -> Allowing files to be 'arranged in a hierarchy of directories'
   -> Provides control over 'access / permissions' to files and directories
   -> Managing other metadata associated with files 'size, location etc...'

Operating systems also manage:
   -> Memory, processes, processor time, i/o devices, networking etc.






