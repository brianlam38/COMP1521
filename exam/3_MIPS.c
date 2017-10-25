// CHAPTER 3: MIPs
==========================================
===== 'STATIC vs DYNAMIC allocation' =====
==========================================

'STATIC ALLOCATION'
Uninitialised memory allocation:
	int val;		val: .space 4
	int arr[20];	arr: .space 80
	char str[20];	str: .space 20
Initialised memory allocation:
	int val = 5;				val: .word 5
	int arr[4] = {9, 8, 7, 6};	arr: .word 9, 8, 7, 6
	char *msg = "Hello\n";		msg: .asciiz "Hello\n"

'MIPS DYNAMIC ALLOCATION'
Variables local to a function.
-> Space allocated on stack during prologue / reclaimed during epilogue
-> Referenced during function relative to $fp

SPIM doesnt provide malloc() / free() functions.
-> However, provides syscall to extend .data

	li   $a0, 20    # $v0 = malloc(20)
	li   $v0, 9		# syscall
	syscall			# after syscall, $v0 holds start addr of allocated chunk
	move $s0, $v0   # $s0 = $v0	 You cant access allocated data by
								 name, you need to retain the address

-> Theres no way to align the data appropriately

'C DYNAMIC ALLOCATION'
Uninitialised block of memory allocated at run-time
	int  *ptr = malloc(sizeof(int));
	char *str = malloc(20*sizeof(char));
	int  *vec = malloc(20*sizeof(int));

Initialised block of memory allocated at run-time
	int *arr = calloc(20, sizeof(int));
	// for i in 0..19: arr[i] == 0

============================
===== 'ARRAYS IN MIPS' =====
============================
You can declare / initialise arrays as such:
	// declaration
	arr:  .space 40				# int arr[10] OR char arr[40]
	// declaration + init
	nums: .word 1, 3, 5, 7, 9	# int nums[6] = {1, 3, 5, 7, 9}
Arrays are passed to functions via. a ptr to the first elt.
________________________________________________________________
Scanning an array of N elements using an 'INDEX'
	// init counter + N
	   li   $s0, 0               # i = 0
	   li   $s1, 10				 # N = 10
	// main loop
	loop: 
	   bge  $s0, $s1, end_loop   # if (i >= 10) break
	   li   $t0, 4
	   mul  $t0, $s0, $t0        # index -> byte offset [ $t0 byte offset = size 4 * counter ]
	   lw   $a0, vec($t0)        # a0 = vec[i]			[ $a0 array value = vec($t0) ]
	   jal  print                # print a0				[ jump to print fn, then execute remaining code ]
	   addi $s0, $s0, 1          # i++					[ increase counter ]
	   j    loop 										[ next iteration ]
	end_loop:
	// do stuff
________________________________________________________________
Scanning an array of N elements using a 'CURSOR'
	   la   $s0, vec             # cur = &vec[0]
	   la   $s1, vec+40          # end = &vec[10]
	loop:
	   bge  $s0, $s1, end_loop   # if (cur >= end) break
	   lw   $a0, ($s0)           # a0 = *cur
	   jal  print                # print a0
	   addi $s0, $s0, 4          # cur++
	   j    loop
	end_loop:

________________________________________________________________
Arrays that are local to functions are allocated space on the stack

fun:                         int fun(int x) 
   # prologue                {
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   move $fp, $sp
   addi $sp, $sp, -4
   sw   $ra, ($sp)              // push a[] onto stack
   addi $sp, $sp, -40           int a[10];
   move $s0, $sp                int *s0 = a;
   # function body
   ... compute ...              // compute using s0
   # epilogue                   // to access a[]
   addi $sp, $sp, 40            // pop a[] off stack
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   jr   $ra                  }























