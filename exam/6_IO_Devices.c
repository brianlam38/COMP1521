// CHAPTER 6: IO Devices

====== 'Input / Output Devices' ======
IO devices allow programs to communicate with the outside world.
-> 'Device Data' = very slow access [ms], random or sequential. Transfer data in 'blocks'.
-> 'Memory-based Data' = much faster [ns], random access via. virtual address. Transfer data in 'units of bytes, halfwords, words'

Example: HARD DISK
-> Access = 'move to track' + 'wait for sector' + 'read block'
-> Typical cost = 10ms seek + 5ms latency + 0.1ms transfer

Example: NETWORK TRANSFER
-> Transfer cost = N( dT + dP + dC + dQ ) , where N = #hops
-> Typical cost = 0.5 ms [local ethernet] | 200 ms [internet]

====== 'Device Drivers' ======
Device Driveres are chunks of code to control an I/O device.
-> Often written in assembler + are core components of the operating system.

Each device has its own unique access protocol.
-> Special control/data registers
-> Locations/buffers for data to be read/written

Typical protocol to manipulate devices:
-> Send request for operation (e.g. read / write / get status)
-> Receive interrupt when request is completed

====== 'Memory-mapped input / output' ======
I/O DEVICES ARE TREATED AS MEMORY LOCATIONS.
-> Virtual Memory addresses are associated with: 'data buffers' / 'control registers' of I/O device.
-> User programs perform I/O by getting/putting data into memory.

Advantages
-> Use of existing memory addresses = 'Less hardware'
-> Access to a full-range of CPU instructions = 'More efficient programming'
Disadvantage
-> Using up valuable memory address space for processes.

====== 'Devices on UNIX/LINUX' ======
Unix treats devices all the same as 'byte-streams' (similar to files)

Devices can be accessed via. file system under '/dev':
	'/dev/diskN' ... part of a hard-drive
	'/dev/ttyN'  ... a terminal device
	'/dev/ptyN'  ... a pseudo-terminal device
Other interesting devices in '/dev':
	'/dev/mem'   ... the physical memory
	'/dev/null'  ... data sink
	'/dev/random'... stream of pseudo-random numbers

'DEVICE FILES': An interface for a device driver that appears in the file system, as it were an ordinary file.
			  Allows software to interact with a device driver using I/O system calls.

Two standard types of device files:

1. CHARACTER DEVICES [special character files] - UN-BUFFERED
2. BLOCK DEVICES [block special files] - BUFFERED

'UN-BUFFERED' = read/write one byte at a time.
				-> 1 real I/O operation per element = VERY SLOW
'BUFFERED'	  = read/write chunks at a time.
				-> Data accumulated in a buffer, then write entire buffer to device.
				-> 1 real I/O operation per chunk of data = FASTER

I/O Device Operations:
	// Manipulates params of special files (on an OPEN fd)
	int ioctl(int FileDesc, int Request, void *Arg)
		-> Request = device-specific request code.
		-> Arg = either int modifier OR ptr to data block
		-> Returns 0 if OK | -1 if ERROR
	// Attempts to open file/device PathName in mode Flags
	int open(char *PathName, int Flags)
		-> Returns file descriptor if OK | -1 if ERROR
	// Attempts to read Nbytes of data from fd into Buf.
	ssize_t read(int FileDesc, void *Buf, size_t Nbytes)
		-> Returns #bytes read, 0 at EOF, -1 if ERROR
	// Attempts to write Nbytes of data from Buf into fd.
	ssize_t write(int FileDesc, void *Buf, size_t Nbytes)
		-> Returns #bytes written, -1 if ERROR


====== 'BUFFERED I/O' ======
Using read() from a device byte-by-byte is inefficient.
-> OS uses a collection of buffers to hold data from a device.
-> Data is fed to user program from Buffer without having to access the device each time = 'more efficient'

The standard I/O <stdio.h> library provides buffering of input:
-> Read in 'BUFSIZ' chunks - A macro for the size of the input buffer. Different for each system.
-> Buffering is hidden from the user, who sees getchar() fgets() etc.

Example implementation of int getc(fp):
	// read BUFSIZ bytes from open fd into buffer
	if (pos == BUFSIZ) {
		read(fileno(fp), buffer, BUFSIZ);		--> 'fileno(FILE *stream)' returns the int fd associated with the stream pointed to by *stream
		pos = 0;
	}
	// return buffer, increment pos
	return buffer[pos++]

====== 'EXCEPTIONS' ======
EXCEPTIONS are unexpected conditions occuring during program execution.

Two types of exceptions:
[1] 'exceptions' from faults within an executing program -> often fatal
[2] 'interrupts' from events external to the program -> often requires some action and then execution continues

Many exceptions occur via. signals and signals can be handled in a variety of ways:
-> 'Term' ... terminate the process
-> 'Ign'  ... ignore the signal
-> 'Core' ... terminate the process, dump core
	['core dump' = a file that consists of the recorded state of the working memory of a process when the program has crashed/terminated]
-> 'Stop' ... stop the process
-> 'Cont' ... continue the process if currently stopped

Signals from 'internal process activity' ... 'SIGILL | SIGABRT | SIGFPE  | SIGSEGV' 	   -> handled by "create core image" core dump + terminate
Signals from 'external process events'   ... 'SIGINT | SIGPIPE | SIGCHLD | SIGTSTP/ctrl-z' -> REFER TO "DEFAULT ACTION" to see how all signals are handled

====== 'SIGNAL HANDLERS' ======
SIGNAL HANDLER = a function invoked in response to a signal.












