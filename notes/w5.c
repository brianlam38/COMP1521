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
seq  $t7,$t1,$t2   # reg[t7] = 1 if (reg[t1]==reg[t2])
                   # reg[t7] = 0 otherwise (signed)
slt  $t7,$t1,$t2   # reg[t7] = 1 if (reg[t1] < reg[t2])
                   # reg[t7] = 0 otherwise (signed)
slti $t7,$t1,Imm   # reg[t7] = 1 if (reg[t1] < Imm)
                   # reg[t7] = 0 otherwise (signed)

j    label         # PC = &label
jr   $t4           # PC = reg[t4]
beq  $t1,$t2,label # PC = &label if (reg[t1] == reg[t2])
bne  $t1,$t2,label # PC = &label if (reg[t1] != reg[t2])
bgt  $t1,$t2,label # PC = &label if (reg[t1] > reg[t2])
bltz $t2,label     # PC = &label if (reg[t2] < 0)
bnez $t3,label     # PC = &label if (reg[t3] != 0)
After each branch instruction, execution continues at new PC location

