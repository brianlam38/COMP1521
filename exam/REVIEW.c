=== 'READ / WRITE / EXE PERMISSIONS' ===
PERMISSIONS:
-> '-rwxrwxrwx'
0 = '---'	4 = '-r-'		[ 'r' = read ]
1 = '--x'	5 = 'r-x'		[ 'w' = write ]
2 = '-w-'	6 = 'rw-'		[ 'x' = execute ]
3 = '-wx'	7 = 'rwx'

USAGE WITH FILE SYS OPERATIONS:
// Mask mode code with 0x1FF (0b111111111) to remove 3 excess octal permission digits
// Mode meta-data usually: 100664 -> cut out 100
	unsigned mask = 0x1FF;
	unsigned bits = mode & mask;
// assigning portions of bits to owner|group|other
    unsigned owner = bits & 0x07;           // 0b111       ... retains [0][1][2] for owner
    unsigned group = (bits & 0x38) >> 3;    // 0b111111    ... retains [3][4][5] for group
    unsigned other = (bits & 0x1C0) >> 6;   // 0b111111111 ... retains [6][7][8] for others

=== 'FILE SYSTEM OPERATIONS' ===

GENERAL APPROACH: Assuming you are given a struct of records etc. and you need to read each record
1. Declare struct stat;
2. Declare entry point into the given struct
   -> FILE* or DIR* objects.
   -> file descriptor fd.
3. Open the entry point to allow read/write by user
   -> open() opendir()
4. Fill the stat struct with info / meta-data about the file that is being pointed to
   -> lstat(fd, stat)
5. Read/Write data from
   -> read() write()
   -> fprintf() fscsanf()

FUNCTIONS TO USE:
// Getting meta-data
	int lstat(char *FileName, struct stat *statBuf)  ... get meta-data about a file system object
	int fstat(int FileDescr, struct stat *statBuf)	 ... same as stat() but gets data via. an open fd
// A struct record of sorts
	typedef struct _student {
	    int id; char name[99]; float wam;
	} Student;
	Student stu;
// fd or file ptr variables
	int in_fd, out_fd;
	FILE *in_fp, *out_fp;
// Usage - file descriptor operations (fd)
	ssize_t	write(int FileDesc, void *Buffer, size_t Count)    ... write bytes from a buffer to a fd
	ssize_t	read(int FileDesc, void *Buffer, size_t Count)	   ... read bytes into a buffer from a fd
	off_t lseek(int FileDesc, off_t Offset, int Whence)    ... move offset / position within a file
// Usage - file pointer operations (fd)
	fprintf(FILE *stream, "%s %d %lld", val_str, val_int, val_long)   ... print bytes from stu struct to the FILE * output stream.
	fscanf(FILE *stream, "%s %d %lld", &val_str, &val_int, &val_long) ... read from FILE * input stream into the stu struct







=== 'OS Process Management' ===








