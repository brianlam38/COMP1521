# COMP1521 Practice Prac Exam #1
# int rmOdd(int *src, int n, int*dest)

   .text
   .globl rmOdd

# params: src=$a0, n=$a1, dest=$a2
rmOdd:
# prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s0, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)
   # if you need to save more $s? registers
   # add the code to save them here

# function body
# locals: ...

   # add code for your rmOdd function here
   move $s0, $a0	# s0 = 0(src)
   move $s1, $a1	# s1 = n
   move $s2, $a2	# s2 = 0(dest)
   li   $t3, 0		# i = 0
   li   $t4, 0		# j = 0
for:
   beq $s1, $t3, end

   mul $t0, $t3, 4	# offset = index * 4
   add $t0, $t0, $s0	# addr = offset + base
   lw  $a0, ($t0)	# get src[index]

   li  $t1, 1		# remainder = 1
   div $t2, $a0, 2	# elt / 2
   mfhi $t5

   beq $t1, $t5, else		# if (elt%2) != 0 -> else
store:
   mul $t6, $t4, 4
   add $t6, $t6, $s2
   sw  $a0, ($t6)

   addi $t4, $t4, 1     # j++

else:
   addi $t3, $t3, 1	# i++
   j for

end:
   move $v0, $t4

# epilogue
   # if you saved more than two $s? registers
   # add the code to restore them here
   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

