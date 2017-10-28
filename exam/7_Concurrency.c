// CONCURRENCY

====== 'INTERACTING PROCESSES / CONTROLLING ACCESS via. FLOCK()' ======
Proceses can interact with each other in several ways.
'Non-deterministic' (no two is the same) problems can arise from un-controlled interactions.
Mechanisms exist to control interactions / access to files e.g. flock()

FILE LOCKING: flock(int FileDesc, int Operation)
-> Controls access to shared files
-> Operations:
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
   -> If file NOT lcoked = OK
   -> If file shared or exclusive lock = BLOCKED
3. Process using a 'non-exclusive lock'
   -> return 0  if locked acquired
   -> return -1 if procecess would be bocked

====== 'CONCURRENCY' ======
Concurrency = have multiple processes running simultaenously.
Sequential execution = the alternative to concurrency

Concurrency increase throughput e.g.
-> if one process is delayed, others can run
-> If we have multiple CPUs, use all at once

Effects of poorly controlled concurrency:
-> 'Non-determinism' ... same code, different runs, different reults each time
-> 'Deadlock'		 ... a group of processes end up waiting for each other
-> 'Starvation' 	 ... one process keeps missing access to resource
We need 'CONCURRENCY CONTROL METHODS' to address these issues.

NON-PROBLEMATIC CONCURRENCY: 'PARALLEL PROCESSING'
-> Multiple identical processes, performing same computation on one element of a data structure
-> Results copied back to main memory data structure + synchronise completion of computation

PROBLEMATIC CONCURRENCY: 'e.g. BANK WITHDRAWAL'
-> Two processes withdrawing $300 from balance $500
-> return balance = -$100
-> vs. return balance = $200 + one process fails

====== 'CONCURRENCY CONTROL' ======
Concurrency Control aims to provide correct sequencing of interactions between processes.
Co-ordinate access to shared resources.

Two classes of concurrency control methods:
1. 'SHARED MEMORY BASED - e.g. SEMAPHORES'
    -> uses shared variable, manipulated atomically - 'Atomic variable = appears to the rest of the system to occur instantaneously'
   	   e.g. atomic data transfer will either success or fail, no corruption if transfer stops midway.
    -> blocks access if unavailable
2. 'MESSAGE PASSING - e.g. SEND/RECEIVE'
	-> Processes communicate by sending/receiving messages
	-> Receiver can block, waiting for message to arrive
	-> Sender may block, waiting for message to be received

SEMAPHORE OPERATIONS:
	init(Sem, InitValue)	... set the initial value of semaphore Sem -> 'InitValue usually set = 1'
	-> Semphore is like a KEY that gets passed arounds
	-> First person with Sem gets access
	-> Everyone else is blocked until Sem is released

	wait(Sem) / P()			... if current value of Sem > 0, decrement Sem and continue
								otherwise, block and wait until Sem value > 0
	-> The process with the Sem goes into a queue()
	-> When someone does a SIGNAL and increments the Sem value, it will send a signal to take the first off the queue() and run the process

	signal(Sem)				... increment value of Sem by 1 and continue
								transfers a blocked process from the semaphores waiting queue() to the ready queue()


There needs to be fair release of blocked processes, otherwise starvation is possible
-> One solution is to use a Queue() [ FIFO STRUCTURE ]

SEMPAHORES ON LINUX/UNIX:
#include <semaphore.h>
int sem_init(sem_t *Sem, int Shared, uint Value) 	... create a semaphore object, set init value
int sem_wait(sem_t *Sem) i.e wait()					... try to decrement, block if Sem == 0
													    has variants that dont block, but return error if cant decrement
int sem_post(sem_t *Sem) i.e signal()				... increment the value of semaphore Sem
int sem_destroy(sem_t *Sem)							... free all memory associated with sempahore Sem

====== 'MESSAGE PASSING' ======
Message passing mechanisms are often embedded into programming languages.

E.g. Google GO language
-> 'goroutines' ... concurrently executing functions
-> 'channels'   ... communication pipes between goroutines [ one process pipe to another process ]
-> 'select'     ... manage multiple channels

Message passing in C is provided by message queues.
#include <mqueue.h>
mqd_t mq_open(char *Name, int Flags)					... create a new message queue, or open an existing one

int mq_send(mqd_t *MQ, char *Msg, int Size, uint Prio)  ... adds message Msg to message queue MQ
															Prio gives priority from queue MQ
															blocks if MQ is empty, can run non-blocking

int mq_close(mqd_t *MQ)		... finish accessing message queue MQ











