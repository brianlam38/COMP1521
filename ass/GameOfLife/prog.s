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
#
# 1. printf("# Iterations: ");
#		store iter string in register
#		load print str instr
#		syscall
#		store newline str in register
#		load print str instr
#		syscall

	la   $a0, str_iter			# print "# Iterations: "
	li   $v0, 4
	syscall
	la   $a0, eol				# print newline
	li   $v0, 4
	syscall

# 2. scanf("%d", &maxiters);
#		load read int instr
#		syscall
#		store int in max_iter data

	li   $v0, 5					# scan iteration input + store in data
	syscall
	sw   $v0, max_iter

	#lw   $a0, max_iter			# << PRINT TEST >>
	#li   $v0, 1
	#syscall

# 3. Pre-loop prep
#		load row_ctr
#		load col_ctr
#		load max_iter counter
#		set general row counter = 0
	lw  $s0, row_ctr
	lw  $s1, col_ctr
	lw  $s2, max_iter
	li  $v0, 0

# 4. iteration loop
#	
#
#

# Keeps track of iterations
main_iter:
	beq  $s0, $s2, end_main # check to see if row_count == 0
	li   $s1, 0					 # set col_counter to 0 (start in the 0th col everytime)

end_main:
	lw   $ra, main_ret_save
	jr   $ra


# The other functions go here


main_iter:

# Keeps track of row progression
main_row:

# Keeps track of column progression
main_col:

# Checks curr board and updates state
board_update:



