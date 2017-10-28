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
