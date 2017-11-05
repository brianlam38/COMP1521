// Final MIPS notes
' === REGISTERS === '
$a0...$a3 	ALWAYS use for passing arguments to functions
$v0...$v1	ALWAYS use for system calls and storing function return values
$t0...$t7	used for local / temp storage
$s0...$s7	used for preserved storage across funct

$ra		stores the return addr, usually beginning of a function

' === LOAD & STORE INSTRUCTIONS ==='
la   $t1,label    # t1 = address of label
lw   $t1,label    # t1 = value at label
sw   $t3,label    # label = value at $t3 [ label must be 4-byte aligned ]

lb   $t2,label    # t2 = byte at label
sb   $t4,label    # label = byte at t4
move $t2,$t3      # t2 = t3
li   $t1,888	  # t1 = 888
li   $a0, 'A'

' === MATHS ==='
add  $t0,$t1,$t2  # t0 = t1 + t2  --> add as signed ints
addu $t0,$t1,$t2  # t0 = t1 + t2  --> add as unsigned integers
addi $t0,$t1, 5   # t0 = t1 + 5	  --> add IMMEDIATE

sub  $t3,$t2,$t1  # t3 = t2 - t1  --> subtract as signed ints
subu $t3,$t2,$t1  # t3 = t2 - t1  --> subtract as unsigned ints

mul  $t1,$t2,$t3  # t1 = t2 * t3
div	 $t1,$t2,$t3  # t1 = t2 / t3
// Special registers
mfhi $t0          # t0 = Hi		-> Hi = reg1 % reg2 [ remainder ]
mflo $t1          # t1 = Lo 	-> Lo = reg1 / reg2 [ normal division ]
								-> FOR MULT, STORE 64-BIT RESULT LO(32) + HI(32)

' === CONTROL / BRANCHING ==='
// BRANCHING
beq  $t1,$t2,label 		# if (t1 == t2), jump to branch address &label
bne  $t1,$t2,label 		# if (t1 != t2), jump to branch address &label
bgt  $t1,$t2,label 		# if (t1 > t2), jump to branch address &label
bltz $t2,label     		# if (t1 < 0),  jump to branch address &label
bnez $t3,label     		# if (t1 != 0), jump to branch address &label

// TRUE-FALSE
seq  $t1,$t2,$t3 	# if (t2 == t3) { t1 = 1 } else { t1 = 0}
slt  $t1,$t2,$t3 	# if (t2 < t3)  { t1 = 1 } else { t1 = 0}
slti $t1,$t2,5 	    # if (t2 < 5)   { t1 = 1 } else { t1 = 0}

' === Jump instructions ==='
j    label  # jump to address of label
jr   $ra    # jump to return address in register
				func:
					sw $ra func_ret_save	-> store start of func
					--- execute code ---
					lw $ra func_ret_save	-> load $ra = addr of func
					jr $ra 					-> 

jal label	# jump to label, link back after execution
				main:
					jal func   	 -> jump to label func + store address of next instr in $ra
			 	func:
			 		--- code ---
			 		ja $ra       -> jump back to $ra address

' === DIRECTIVES / VARS ==='
// UN-INITIALISED
a:  .space 18    # char a[18]; OR int a[4];	 // Leftover 2 bytes can't be an int
    .align 2     # align to the next multiple of 4 addr

// INITIALISED
  int_var:  .word 2      # int var = 2;
short_var:  .half 4		 # short var = 4;
 byte_var:  .byte 1		 # char var = 1;
float_var:	.float 3.14	 # float f = 3.14;

int_array:  .word 1,3,5  # int a[3] = [1,3,5];

  matrix1:	.space 64	 # int a[4][4]
 OR
	 row1:	.space 16	 # int b[4][4]
	 row2:	.space 16
	 row3:	.space 16
	 row4:	.space 16
  matrix2:	.word row1, row2, row3, row4

 str_null:  .asciiz "abc" # char s[4] {'a','b','c','\0'}; -> null-terminated
	  str:  .ascii "abc"  # char s[3] {'a','b','c'};	  -> un-terminated

' === ARRAYS - 1D and 2D ==='
// array cursor = offset(&array)
// array indexing = array_label(offset)
    .data
arr:
	.space   12      # int arr[3] un-initialised

    .text
main:
    la  $t0, vec      # t0 = &arr[0]
	// INIT METHOD 1 -> CURSOR
    li  $t1, 5
    sw  $t1, ($t0)    # arr[0] = 5
    li  $t1, 13
    sw  $t1, 4($t0)   # arr[1] = -13
    // INIT METHOD 2 -> INDEX
    li  $t2, 12
    li  $t1, 42
    sw  $t1, arr($t2) # arr[3] = 42

// 2D arrays
    mul $t0 row col     -> calculate offset
    lw  $a0 array($t0)	-> a0 = array value via. offset #

' === STRUCT - UNINITIALISED ==='
// Assuming student struct:
struct _student {
	int id; char family[20]; char given[20]; int program; double wam;
};
// Access struct by offset;
	.data
stu:
	.space 56		# Student stu;  -> size = 4 + 20 + 20 + 4 =56
init_struct:
	la  $s1, stu          # stu = &stu2;
	li  $t0, 2041
	sw  $t0, 44($s1)      # stu->program = 1521;
	li  $t0, 5034567
	sw  $t0, 0($s1)       # stu->id = 5030587;

' === STRUCT - INITIALISED ==='
// Follow the above struct
	.data
stu:
	.word 5035087	# int id = 5035087;
	.asciiz "LAM"	# char family = "LAM\0"; -> PADDING: 20 - 4 bytes
	.space 16
	.asciiz "BRIAN" # char given = "BRIAN\0"; -> PADDING: 20 - 6 bytes
	.space 14
	.word 1521		# int program = 1521
	.double 68		# double wam = 68

' === DYNAMIC ALLOCATION (MALLOC) ==='
	li   $a0, 20	 # $v0 = malloc(20 bytes)
	li   $v0, 9
	syscall
	move $s0, $v0	 # $s0 = $v0

' === LINKED LISTS ==='
typedef struct _node Node;
struct _node {
   int  value;  // value stored in Node
   Node *next;  // pointer to following Node
};

   ...                 # $s0 represents Node *first
   li   $a0, 8         # sizeof(Node) == 8
   jal  malloc
   move $s0, $v0       # s0 = malloc(sizeof(Node))
   li   $t0, 1
   sw   $t0, 0($s0)    # s0->value = 1
   li   $a0, 8         # required: $a0 not persistent
   jal  malloc
   move $t1, $v0       # s1 = malloc(sizeof(Node))
   sw   $t1, 4($s0)    # s0->next = s1
   li   $t0, 2
   sw   $t0, 0($t1)    # s1->value = 2
   sw   $0, 4($t1)     # s1->next = NULL
   ...


















