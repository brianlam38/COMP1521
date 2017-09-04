# C PROGRAM
#
# for (i = 0; i < row_count; i++) {
#		for (i = 0; j < col_count; j++) {
#			printf("%c", flag[i][j]);
#		}
#		printf("\n");
#}
#

  1 2 3 4 5
1 . . . . .
2 . . . . .
3 . X . . .
4 . . . . .
5 . . . . .
6 . . . . .

how to find the value of X in 2d array[i][j]
- Keep track of num_rows and num_cols
- Multiply value of num_rows * num_cols (2 rows * 5 columns = 10)
- Address the offset
- See code below in 'loop_inner'

variables $s2: row_count
		  $s3: col_count
		  $s0: row_counter
		  $s1: col_counter

main:
	la	$a0, msg_1
	li 	$v0, 4
	syscall

	lw $s2, num_rows		# load row_count
	lw $s3, num_colsl		# load col_count
	li $s0, 0				# set row_counter to 0

loop_outer:
	beq $s0, $s2, end_loop_outer # check to see if row_count == 0
	li  $s1, 0					 # set col_counter to 0 (start in the 0th col everytime)

loop_inner:
	beq $s1, $s3, end_loop_inner ### THIS PART HELPS LOCATE VALUE INSIDE ARRAY ###
	mul $t0, $s0, $s3			# multiply our col count with our counter
	add $t0, $t0, $s1			# addin the offset

	lb $a0, flag($t0)			# load byte, flag($t0) = printing character in array (reg should be inside the bracket, label outside)
	li $v0, 11						# 8(0) = 0 + 8 (take outside and add inside)
	syscall							# flag(t0) = take address of flag + add t0
								# li $v0, 11 = print newline

	addi $s1, $s1, 1			# increment
	j loop_inner

end_loop_inner:
	li $a0, 10				# newline print
	li $v0, 11				# 11 = syscall value for printing a byte
	syscall

	addi $s0, $s0, 1	# increment outer loop here
	j loop_outer 		# jump back to outer

end_loop_outer:
	jr $ra




	
