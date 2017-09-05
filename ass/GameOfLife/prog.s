# prog.s ... Game of Life on a NxN grid
#
# Needs to be combined with board.s
# The value of N and the board data
# structures come from board.s
#
# Written by BRIAN LAM, August 2017

   .data
# board data N = 10 x 10 grid
N:
	.word 10  # gives board dimensions
board:
	.byte 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.byte 1, 1, 0, 0, 0, 0, 0, 0, 0, 0
	.byte 0, 0, 0, 1, 0, 0, 0, 0, 0, 0
	.byte 0, 0, 1, 0, 1, 0, 0, 0, 0, 0
	.byte 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
	.byte 0, 0, 0, 0, 1, 1, 1, 0, 0, 0
	.byte 0, 0, 0, 1, 0, 0, 1, 0, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
newBoard:
	.space 100

# program data
max_iter:
	.word 1
rows:
	.word 1
cols:
	.word 1
row_ctr:
	.word 1
col_ctr:
	.word 1
str_iter:
	.asciiz "# Iterations: "
eol:
	.asciiz "\n"
	.align 2
main_ret_save:
	.space 4

	.text
	.globl main
main:
	sw   $ra, main_ret_save

# Your main program code goes here

# 1. prepare starting board
#		
#
# 2. printf("# Iterations: ");
#		store iter string in register
#		load print str instr
#		syscall
#		store newline str in register
#		load print str instr
#		syscall
# 3. scanf("%d", &maxiters);
#		load read int instr
#		syscall
#		store int in max_iter data
#

end_main:
	lw   $ra, main_ret_save
	jr   $ra


# The other functions go here
