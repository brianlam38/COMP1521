// CONCURRENCY

====== 'INTERACTING PROCESSES' ======
Proceses can interact with each other in several ways.
'Non-deterministic' (no two is the same) problems can arise from un-controlled interactions.
Mechanisms exist to control interactions e.g. flock()

'FILE LOCKING' flock(int FileDesc, int Operation)
-> Controls access to shared files
-> Operations:
	'LOCK_SH' ... acquire shared lock
	'LOCK_EX' ... acquire exclusive lock
	'LOCK_UN' ... unlock
	'LOCK_NB' ... operation fails rather than blocking
-> flock() only ATTEMPTS to acquire a lock, only works correctly if all processes that access the file use locks
-> return 0 success | return -1 failure
