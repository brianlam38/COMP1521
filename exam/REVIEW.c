=== 'FILE SYSTEM OPERATIONS' ===

GENERAL APPROACH: Assuming you are given a struct of records etc. and you need to read each record
1. Declare struct stat;
2. Declare entry point into the given struct
   -> FILE* or DIR* objects.
   -> file descriptor fd.
3. Open the entry point to allow read/write by user
   -> open() opendir()
4. Fill information about the file being pointed to into the stat struct
   -> lstat(fd, stat)
5. Read/Write data from
   -> read() write()
   -> fprintf() fscsanf()

FUNCTIONS TO USE:
// Getting meta-data
	int stat(char *FileName, struct stat *statBuf)  ... get meta-data about a file system object
	int lstat(int FileDescr, struct stat *statBuf)	... same as stat() but gets data via. an open fd
// A struct record of sorts
	typedef struct _student {
	    int id; char name[99]; float wam;
	} Student;
	Student stu;
// fd or file ptr variables
	int in_fd, out_fd;
	FILE *in_fp, *out_fp;
// Usage - file descriptor operations (fd)
	write(int FileDesc, void *Buffer, size_t Count)    ... write bytes from a buffer to a fd
	read(int FileDesc, void *Buffer, size_t Count)	   ... read bytes into a buffer from a fd
// Usage - file pointer operations (fd)
	fprintf(FILE *stream, "%s %d %lld", val_str, val_int, val_long)   ... print bytes from stu struct to the FILE * output stream.
	fscanf(FILE *stream, "%s %d %lld", &val_str, &val_int, &val_long) ... read from FILE * input stream into the stu struct

