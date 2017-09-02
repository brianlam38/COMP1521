/* WEEK 4 NOTES - INSTRUCTION SET ARCHITECTURES
 *
 * Brian Lam
 */

//==================
// CPU ARCHITECTURE
//==================
A modern CPU has:
- A set of registers / control registers / arithmetic-logic unit [ALU] / access to random access memory [RAM]
- A set of simple instructions:
[1] Transfer data between memory and registers
[2] push values through ALU to compute results
[3] make tests and transfer control of execution

//==================
// INSTRUCTION SETS
//==================
Machine-level instructions:
- have 1-2 32bit words per instruction
- partition bits in each word into operator & operands
- #bits for each depends on #instructions #registers etc.
Example:
     8b         8b         8b		   8b
| operator | operand1 | operand2 |    dest    |	  ' operators and destination are typically registers '
| operator |   dest   |		value or address  |

//=====================
// FETCH-EXECUTE CYCLE
//=====================
All CPU have program execution logic similar to:
while (1) {
	instruction = memory[PC]	// fetch instruction
	PC++						// move to next instruction
	if (instruction == HALT) {
		break;					// PC = Program Counter, a CPU register which keeps track of execution
	} else {					//      Some programs may modify PC further (i.e. jump)
		execute(instruction)
	}
}

Executing an instruction involves:
- Determine what the 'OPERATOR' is
- Determine which 'REGISTERS', if any, are involved
- Determine which 'MEMORY LOCATION', if any, is involved
- Carry out the operation with the relevant operands
- Store result, if any, in the appropriate register

//===================
// ASSEMBLY LANGUAGE
//===================
Instructions are simply bit-paterns within a 32-bit string.
Machine programs can be described as a sequence of hex digits:
'ADDRESS'	'CONTENT'
0x100000	0x3c041001	Assembly Language / Assembler provides a
0x100004	0x34020004	symbolic way of giving code to machines
0x100008	0x0000000C

//===================
// MIPS ARCHITECTURE
//===================
MIPS CPU has:
- 32 x 32-bit general purpose registers
- 16 x 64-bit double precision registers
- PC ... 32-bit register (always aligned on 4-byte boundary)
- HI, LO ... for storing results of multiplication and division

Registers can be referred to as $0 ... $31 or by symbolic names

Special Registers:
- Register $0 always has value 0, cannot be written
- Registers $1, $26, $27 reserved for use by the system

General purpose registers and their usage:
Reg	 		Name	 	Notes
-------------------------------------------------------------------------------------------
$0	 		zero	 	the value 0, not changeable
$1	 		$at	 		assembler temporary; reserved for assembler use
$2	 		$v0	 		value from expression evaluation or function return
$3	 		$v1	 		value from expression evaluation or function return
$4	 		$a0	 		first argument to a function/subroutine, if needed
$5	 		$a1	 		second argument to a function/subroutine, if needed
$6	 		$a2	 		third argument to a function/subroutine, if needed
$7	 		$a3	 		fourth argument to a function/subroutine, if needed
$8..$15	 	$t0..$t7	temporary; must be saved by caller to subroutine; subroutine can overwrite

$16..$23	$s0..$s7	safe function variable; must not be overwritten by called subroutine
$24..$25	$t8..$t9	temp registers; must be saved by caller to subroutine; subroutine can overwrite
$26..$27	$k0..$k1	for kernel use; may change unexpectedly
$28	 		$gp	 	global pointer
$29	 		$sp	 	stack pointer
$30	 		$fp	 	frame pointer
$31	 		$ra	 	return address of most recent caller

Floating-point registers and their usage:
NOTE: Registers come in pairs of 2 x 32-bits. Only even registers are addressed for double-precision.
Reg	 			Notes
----------------------------------------------------------------------
$f0..$f2	 	hold floating-point function results
$f4..$f10	 	temporary registers; not preserved across function calls
$f12..$f14	 	used for first two double-precision function arguments
$f16..$f18	 	temporary registers; used for expression evaluation
$f20..$f30	 	saved registers; value is preserved across function calls

Each line in a MIPS assembly program contains:
- Comments    						  '#'	
- Labels				appended with ':'	-> Labels = symbolic names given to memory addresses
- Directives	symbol beginning with '.'	-> Special instructions / kind of like C pre-processor #include etc.
- Assembly language Instructions 			   Directives tell the assembler to do something.
Programmers need to:
- Specify where data objects exist in memory + give them a name so you can reference them.
- Specify functions / 'instruction sequences' that live in the code/text region.
- Specify each instruction or directive on its own line.

//====================================
// GENERIC STRUCTURE OF MIPS PROGRAMS
//====================================
# Prog.s ... comment giving description of function
# Author ...

		.data 		# everything below will be put into "data segment" of memory
msg:	.asciiz	"Hello, MIPS\n"	# direct inserts the str at the 1st location in the data segment
								# Assembler will look at "msg" label and associate the msg label
								# as the start of the segment

		.text 		# everything below will be put into "code/text segment" of memory
		.globl main # "main is a label/name that is going to be known globally"

main:				# indicates start of code i.e. first user instruction to execute.
		la $a0, msg	# load the argument string into register $a0
		li $v0, 4	# load the system call: 4 = 'print' system call
		syscall		# print the string / invoke the system call
		jr $ra 		# jump function, return to caller: '__start' which is the start of the 'code/text segment'
					#									invoke the main program. Return to the next instruction.

# End of program; leave a blank line to make SPIM happy

//====================================
// MIPS MEMORY LAYOUT
//====================================
MIPS programs assume the following memory layout:

Region	 	Address	 		Notes
text	 	0x00400000	 	contains only instructions; read-only; cannot expand
data	 	0x10000000	 	data objects; readable/writeable; can be expanded
stack	 	0x7fffefff	 	grows down from that address; readable/writeable
k_text	 	0x80000000	 	kernel code; read-only; only accessible kernel mode
k_data	 	0x90000000	 	kernel data; read/write; only accessible kernel mode















