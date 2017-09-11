/* WEEK 5 NOTES - MIPS CONTINUED
 *
 * Brian Lam
 */	

//=======================
// MIPS Syntax Semantics
//=======================
Treat registers as unsigned int reg[32]
Treat memory as unsigned char mem[2^32]

Syntax	Semantics
-----------------------------------------------
$Reg	as source, the content of the register, reg[Reg]
$Reg	as destination, value is stored in register, reg[Reg] = value
Label	references the associated address (in C terms, &Label)
Addr	any expression that yields an address (e.g. Label($Reg))
Addr	as source, the content of memory cell  memory[Addr]
Addr	as destination, value is stored in  memory[Addr] = value

//=====================================
// Load and Store Instruction Examples
//=====================================
la   $t1,label    # reg[t1] = &Label 				-> Loading ADDRESS only
lw   $t1,label    # reg[t1] = memory[&label]		-> Loading VALUE at address
sw   $t3,label    # memory[&label] = reg[t3]		-> Storing value at REG
                  # &label must be 4-byte aligned
lb   $t2,label    # reg[t2] = memory[&label]
sb   $t4,label    # memory[&label] = reg[t4]
move $t2,$t3      # reg[t2] = reg[t3]
lui  $t2,const    # reg[t2][31:16] = const

//======================================
// Bit Maniulation Instruction Examples
//======================================

and  $t0,$t1,$t2  # reg[t0] = reg[t1] & reg[t2]
and  $t0,$t1,Imm  # reg[t0] = reg[t1] & Imm[t2]
                  # Imm is a constant (immediate)
or   $t0,$t1,$t2  # reg[t0] = reg[t1] | reg[t2]
xor  $t0,$t1,$t2  # reg[t0] = reg[t1] ^ reg[t2]
neg  $t0,$t1      # reg[t0] = ~ reg[t1]

//=================================
// Arithmetic Instruction Examples
//=================================

add  $t0,$t1,$t2  # reg[t0] = reg[t1] + reg[t2]
                  #   add as signed (2s complement) ints
sub  $t2,$t3,$t4  # reg[t2] = reg[t3] + reg[t4]
addi $t2,$t3, 5   # reg[t2] = reg[t3] + 5
                  #   "add immediate" (no sub immediate)
addu $t1,$t6,$t7  # reg[t1] = reg[t6] + reg[t7]
                  #   add as unsigned integers
subu $t1,$t6,$t7  # reg[t1] = reg[t6] + reg[t7]
                  #   subtract as unsigned integers
mult $t3,$t4      # (Hi,Lo) = reg[t3] * reg[t4]
                  #   store 64-bit result in registers Hi,Lo
div  $t5,$t6      # Lo = reg[t5] / reg[t6] (integer quotient)
                  # Hi = reg[t5] % reg[t6] (remainder)
mfhi $t0          # reg[t0] = reg[Hi]
mflo $t1          # reg[t1] = reg[Lo]
                  # used to get result of MULT or DIV

//============================================
// Testing and Branhcing Instruction Examples
//============================================

// Critical in implementing control structures in MIPS
seq  $t7,$t1,$t2   # reg[t7] = 1 if (reg[t1]==reg[t2])		// (t1 cmp t2), return boolean result at t7
                   # reg[t7] = 0 otherwise (signed)
slt  $t7,$t1,$t2   # reg[t7] = 1 if (reg[t1] < reg[t2])		// (t1 < t2), return boolean result at t7
                   # reg[t7] = 0 otherwise (signed)
slti $t7,$t1,Imm   # reg[t7] = 1 if (reg[t1] < Imm)			// (t1 < Imm) (any value), return boolean result at t7
                   # reg[t7] = 0 otherwise (signed)

j    label         # PC = &label 		// jump to address of label
jr   $t4           # PC = reg[t4]		// jump to address of register

// Condtional branching instructions
beq  $t1,$t2,label # PC = &label if (reg[t1] == reg[t2])	// if (t1 == t2), jump to branch address
bne  $t1,$t2,label # PC = &label if (reg[t1] != reg[t2])	// if (t1 != t2), " " " "
bgt  $t1,$t2,label # PC = &label if (reg[t1] > reg[t2])		// if (t1 > t2), " " " "
bltz $t2,label     # PC = &label if (reg[t2] < 0)			// if (t2 < 0), " " " "
bnez $t3,label     # PC = &label if (reg[t3] != 0)			// if (t3 != 0), " " " "
// ^After each branch instruction, execution continues at new PC location

// Special jump instruction
jal label    	   e.g. main:
							jal func   // transfer control to label/function:
	 					func:		   // + grab address of next instruction after the jal instruction
	 						... body
	 						ja $ra     // + store value into $ra in label/function
	 						...		   // after label/function executes body, jump to next instruction after jal

//=================
// MIPS Directives
//=================
    .text        # following instructions placed in text segment
    .data        # following objects placed in data segment

    .globl       # make symbol available globally

a:  .space 18    # uchar a[18];  or  uint a[4];	 // uint a[4] = 16 bytes. Leftover 2 bytes can't be an int
    .align 2     # align next object on 22-byte addr // .align 2 (power to 2) = 4-byte boundary.
    												 // .align 1 = 2-byte boundary
    												 // Explanation: the next field after .align 2 will be aligned to a 4
i:  .word 2      # unsigned int i = 2;
v:  .word 1,3,5  # unsigned int v[3] = {1,3,5};
h:  .half 2,4,6  # unsigned short h[3] = {2,4,6};
b:  .byte 1,2,3  # unsigned char b[3] = {1,2,3};
f:  .float 3.14  # float f = 3.14;

s:  .asciiz "abc"
                 # char s[4] {'a','b','c','\0'};
t:  .ascii "abc"
                 # char s[3] {'a','b','c'};





