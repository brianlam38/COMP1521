   .text
   .globl main
main:
   # prologue
   add  $sp, $sp, -4
   sw   $fp, ($sp)
   move $fp, $sp
   add  $sp, $sp, -4
   sw   $ra, ($sp)
   # function body
   li   $a0, 20       # v0 = malloc(20)
   jal  malloc
   move $s1, $v0
   move $a0, $v0      # print v0
   jal  print
   li   $a0, 4        # v0 = malloc(4)
   jal  malloc
   move $s0, $v0      # s0 = v0
   move $a0, $v0
   jal  print
   li   $t0, 42
   sw   $t0, ($s0)    # *s0 = 42
   lw   $a0, ($s0)    # print *s0
   jal  print
   # epilogue
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   jr   $ra

# v0 = malloc(a0)
# extend .data
# return address of new space
malloc:
   # prologue
   add  $sp, $sp, -4
   sw   $fp, ($sp)
   move $fp, $sp
   add  $sp, $sp, -4
   sw   $ra, ($sp)
   # function body
   # $a0 was passed in
   li   $v0, 9
   syscall
   # sets $v0 appropriately
   # epilogue
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   jr   $ra

# printf("%d\n", $a0)
print:
   # prologue
   add  $sp, $sp, -4
   sw   $fp, ($sp)
   move $fp, $sp
   add  $sp, $sp, -4
   sw   $ra, ($sp)
   # function body
   # $a0 was passed in
   li   $v0, 1        # printf("%d",a0)
   syscall
   li   $a0, '\n'     # printf("%c",'\n')
   li   $v0, 11
   syscall
   # epilogue
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   jr   $ra
