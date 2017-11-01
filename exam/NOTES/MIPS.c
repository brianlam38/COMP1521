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

' === MATHS ==='
add  $t0,$t1,$t2  # t0 = t1 + t2  --> add as signed ints
addu $t0,$t1,$t2  # t0 = t1 + t2  --> add as unsigned integers
addi $t0,$t1, 5   # t0 = t1 + 5	  --> add IMMEDIATE

sub  $t3,$t2,$t1  # t3 = t2 - t1  --> subtract as signed ints
subu $t3,$t2,$t1  # t3 = t2 - t1  --> subtract as unsigned ints

mul  $t1,$t2,$t3  # t1 = t2 * t3
div	 $t1,$t2,$t3  # t1 = t2 / t3

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

int_array:  .word 1,3,5  # int v[3] = [1,3,5];

 str_null:  .asciiz "abc" # char s[4] {'a','b','c','\0'}; -> null-terminated
	  str:  .ascii "abc"  # char s[3] {'a','b','c'};	  -> un-terminated

' === ARRAYS ==='
// array indexing = offset(register)
    .data
vec: .space   16      # int vec[4], 16 bytes of storage
    .text
__start:   
    la  $t0, vec      # reg[t0] = &vec
    li  $t1, 5        # reg[t1] = 5
    sw  $t1, ($t0)    # vec[0] = reg[t1]
    li  $t1, 13       # reg[t1] = 13
    sw  $t1, 4($t0)   # vec[1] = reg[t1]
    li  $t1, -7       # reg[t1] = -7
    sw  $t1, 8($t0)   # vec[2] = reg[t1]
    li  $t2, 12       # reg[t2] = 12
    li  $t1, 42       # reg[t1] = 42
    sw  $t1, vec($t2) # vec[3] = reg[t1]









