# prog.s ... Game of Life on a NxN grid
#
# Needs to be combined with board.s
# The value of N and the board data
# structures come from board.s
#
# Written by BRIAN LAM, August 2017

	.data
	.align 2
# board data N = 10 x 10 grid
N:
	.word 4  # gives board dimensions
#board:
#	.byte '1', '1', '1', '1'			# SMALLER SIZE BOARD
#	.byte '1', '0', '1', '1'			# EASIER FOR TESTING
#	.byte '1', '1', '0', '1'			# REMEMBER TO CHANGE LABEL 'N' TO MATCH #ROWS/#COLS
#	.byte '1', '1', '1', '1'
#newBoard:
#	.space 16

board:
	.byte '1', '1', '1', '1'			# SMALLER SIZE BOARD
	.byte '1', '0', '1', '1'			# EASIER FOR TESTING
	.byte '1', '1', '0', '1'			# REMEMBER TO CHANGE LABEL 'N' TO MATCH #ROWS/#COLS
	.byte '1', '1', '1', '1'
newBoard:
	.space 16

# program data
max_iter:
	.word 1
array_index:
	.word 0
str_iter:
	.asciiz "# Iterations: "
board_print1:
	.asciiz "=== After iteration "
board_print2:
	.asciiz " ===\n"
eol:
	.asciiz "\n"
x_nn:
	.word -1
y_nn:
	.word -1
nn:
	.word 0
	.align 2
main_ret_save:
	.space 4
board_ret_save:
	.space 4
neighbours_ret_save:
	.space 4

################
# MAIN FUNCTION
################

	.text
	.globl main
main:
	sw   $ra, main_ret_save
	# Print "# Iterations: "
	la   $a0, str_iter			# print "# Iterations: "
	li   $v0, 4
	syscall
	# Scan and store max_iter input
	li   $v0, 5
	syscall
	sw   $v0, max_iter
	# Set up counter and end values
	li   $s0, 0					# row counter
	li   $s1, 0					# col counter
	li   $s2, 0					# iter counter
	li   $s5, 0					# array index
	lw   $s3, max_iter			# store max_iter
	lw   $s4, N 				# store board size N

# Keep track of iterations
iter_loop:
	beq  $s2, $s3, end_main 	# while (iter_ctr != max_iter)

# Keep track of row progression
row_loop:
	beq  $s0, $s4, end_row_loop # while row < N
	li   $s1, 0					# 		reset col ctr

# Keep track of col progression
col_loop:
	beq  $s1, $s4, end_col_loop # while col < N

	# neighbours
	jal  neighbours

	# do stuff
	lb   $a0, board($s5)		# 		load cell to $reg
	sb   $a0, newBoard($s5)		#		store cell in newBoard

	addi $s5, $s5, 1 			# array_index++
	addi $s1, $s1, 1    		# col ctr++, goto next col
	j 	 col_loop

# End of rows
end_row_loop:
	addi $s2, $s2, 1 	# iter ctr++
	jal  board_update	# -> board_outer and link
	j    iter_loop		# -> next iteration

# End of columns
end_col_loop:
	addi $s0, $s0, 1	# row ctr++
	j 	 row_loop 		# -> next row

# End of main
end_main:
	lw   $ra, main_ret_save
	jr   $ra

####################
# copyBackAndShow()
####################

board_update:							# update board and print current state
    sw   $ra, board_ret_save
    # reset counter values
	li   $s0, 0
	li   $s1, 0
	li   $s5, 0
	# print no. iterations
	la   $a0, board_print1
	li   $v0, 4
	syscall
	move $a0, $s2
	li   $v0, 1
	syscall
	la   $a0, board_print2
	li   $v0, 4
	syscall

board_outer:							# board row loop, while row < N
	beq  $s0, $s4, end_board_outer
	li   $s1, 0

board_inner:							# board col loop, while col < N
	beq  $s1, $s4, end_board_inner
	# print newBoard cell
	lb   $a0, newBoard($s5)
	li   $v0, 11
	syscall
	# increment array + col counter
	addi $s5, $s5, 1
	addi $s1, $s1, 1
	j 	 board_inner

end_board_inner:						# end of cols
	# print newline
	la   $a0, eol
	li   $v0, 4
	syscall
	# jump to next row
	addi $s0, $s0, 1
	j 	 board_outer

end_board_outer:						# end of rows
	# reset counters
	li   $s0, 0
	li   $s1, 0
	li   $s5, 0
	# return to next iteration
	lw   $ra, board_ret_save
	jr   $ra

###############
# neighbours()
###############

neighbours:							# update board and print current state
    sw   $ra, neighbours_ret_save
    # set up init values
    lw   $s6, x_nn # x rows
    lw   $s7, y_nn # y cols
    #addi $s6, $s0, -1 # x+i
    #addi $s7, $s1, -1 # y+j

    lw   $a1, N
    addi $a1, $a1, -1 # a1 = N-1
    li   $a2, 2 	  # const val 1

    # reset nn
    li   $t0, 0
    sw   $t0, nn

n_outer:							# while (x < 2) ~= (x <= 1)
	beq  $s6, $a2, end_n_outer
	li   $s7, 0

n_inner:							# while (x < 2) ~= (x <= 1)
	beq  $s7, $a2, end_n_inner

	# LHS/RHS: if out of bounds -> skip
	add  $t0, $s6, $s0 				# t0 = i+x
	bltz $t0, end_n_inner 			# i+x < 0
	bgt  $t0, $a1, end_n_inner 		# i+x > N-1

	# UP/DOWN: if out of bounds -> skip
	add  $t0, $s7, $s1 				# t0 = j+y
	bltz $t0, end_n_inner 			# j+y < 0
	bgt  $t0, $a1, end_n_inner 		# j+y > N-1

	# SAME SPOT -> skip
	li   $t0, 0 
	bne  $s6, $t0, check_alive	 # row != 0, check cell
	bne  $s7, $t0, check_alive   # col != 0, check cell

	# increment col
	addi $s7, $s7, 1
	j 	 n_inner

end_n_inner:						# end of cols
	# jump to next row
	addi $s6, $s6, 1
	j 	 n_outer

end_n_outer:						# end of rows
	# return nn and link back
	lw   $ra, neighbours_ret_save
	jr   $ra

check_alive:
	# if board[i][j] != alive, skip
	li   $t0, '1'
	lb   $a0, board($s5)
	bne  $a0, $t0, end_n_inner

    lw   $a3, nn
    addi $a3, $a3, 1
    sw   $a3, nn
    lw   $a0, nn
    li   $v0, 1
    syscall
    la   $a0, eol
    li   $v0, 4
    syscall

	j    end_n_inner



#NEXT STEPS:
#1. Add code in main() to assign newBoard values
#2. Add code in copyBackAndShow() to parse newBoard cells -> char bytes for printing
#2. Do print tests to make sure newBoard assignment + printing works
#3. Create num neighbours check

