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
row_num:
	.word 1
col_num:
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

####################
# Main Program Code
####################

# 1. printf("# Iterations: ");
	la   $a0, str_iter			# print "# Iterations: "
	li   $v0, 4
	syscall
	la   $a0, eol				# print newline
	li   $v0, 4
	syscall

# 2. scanf("%d", &maxiters);
	li   $v0, 5					# scan iteration input + store in data
	syscall
	sw   $v0, max_iter

	#lw   $a0, max_iter			# << PRINT TEST >>
	#li   $v0, 1
	#syscall

# 3. Pre-loop prep
#	set counters, load max_iter and N values
	li   $s0, 0					# row counter
	li   $s1, 0					# col counter
	li   $s2, 0					# iter counter

	sw   $s0, row_num			# keep track of row
	sw   $s1, col_num			# keep track of col

	lw   $s3, max_iter			# store max_iter
	lw   $s4, N 				# store board size N

# 4. loops

# Keep track of iterations
iter_loop:
	beq  $s2, $s3, end_main 	# while (iter_ctr != max_iter)
								#		continue

# Keep track of row progression
row_loop:
	beq  $s0, $s4, end_iter_loop # while (row_ctr != N)
	li   $s1, 0					 #		set col ctr = 0

col_loop:
	beq  $s1, $s4, end_row_loop # while (col_ctr != N)


end_main:
	lw   $ra, main_ret_save
	jr   $ra


##################
# Other Functions
##################

# End of row loops, increment iter ctr, jump to next iter
end_row_loop:
	addi $s2, $s2, 1
	j    iter_loop

# End of column loops, increment row ctr, jump to next row
end_col_loop:
	addi $s0, $s0, 1
	j 	 row_loop

# Checks curr board and updates state
board_update:



