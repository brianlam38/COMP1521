   .text
   .globl main
main:
   # prologue
   add  $sp, $sp, -4
   sw   $fp, ($sp)
   add  $sp, $sp, -4
   sw   $ra, ($sp)
   # function body
   li   $a0, 20       # v0 = malloc(20)
   jal  malloc
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

# v0 = calloc(a0,a1)
# a0 = # items, a1 = sizeof each item
# extend .data
# return address of new space
malloc:
   # prologue
   add  $sp, $sp, -4
   sw   $fp, ($sp)
   add  $sp, $sp, -4
   sw   $ra, ($sp)
   add  $sp, $sp, -4
   sw   $s0, ($sp)
   # function body
   # $a0 was passed in
   mul  $s0, $a0, $a1
   move $a0, $s0
   li   $v0, 9
   syscall
# t1 = v0 = start address
# t2 = &v0[s0]
# while (t1 < t2) { *t1 = 0; t1++; }
   move $t1, $v0
   move $t2, $v0
   add  $t2, $t2, $s0
loop:
   beq  $t1, $t2, end_loop
   sb   $0, ($t1)
   addi $t1, $t1, 1
   j    loop
end_loop:
   # sets $v0 appropriately
   # epilogue
   lw   $s0, ($sp)
   add  $sp, $sp, 4
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
