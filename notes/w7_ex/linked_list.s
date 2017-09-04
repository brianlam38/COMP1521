
 * linked list


main:
	la   $a0, msg_1
	li 	 $v0, 4
	syscall

max:
	# prologue
	addi $sp, $sp, -4
	sw   $fp, ($sp)
	la   $fp, ($sp)
	addi $sp, $sp, -4
	sw   $ra, ($sp)

	lw   $a0, list
	bne  $a0, $0, max1	// check if $a0 = 0 or NULL
	li   $v0, -1

	j     end_max

max1:
	move $s0, $a0		// use $s0 for curr
	lw   $v0, 0($s0)	// use $v0 for max    lw sets v0 = 0($s0) = 0 + 6 = 6
	// fall through to loop belo

loop:
	beq $s0, $0, end_max
	lw	$t0, 0($s0)			# t0 = curr->value
							# why do we need 0($s0)? Why can't we just use $s0?
								# this is needed to derefence
								# alternative is use 'load immediate instruction'
	# move $a0, $v0
	# li $v0, 1
	# syscall

	ble  $t0, $v0, max2		# if t0 <= v9, jump to max2
	move $v0, $t0			# max = curr->value

max2:
	lw  $s0, 4($s0)			# curr = curr->next
	j 	loop

end_max:
	move $t0, $v0			# make sure we save our value

	### UNFINISHED CODE ###
		### UNFINISHED CODE ###
			### UNFINISHED CODE ###
				### UNFINISHED CODE ###
					### UNFINISHED CODE ###

					Get it off Peter

	