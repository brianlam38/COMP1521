# int f(...)
# {
#    // variables happen to be stored 
#    // in registers $s0, $s1, ..., $s5 
#    int a,b,c,d,e,f;
#    ... // variables initialised
#    a = g(a,b,c,d,e,f);
#    printf("%d\n",a);
# }
# int g(int u,v,w,x,y,z)
# {
#    return u+v+w*w*x*y*z;
# }

   .text
   .globl main
main:
# prologue
   addi $sp, $sp, -4
   sw   $ra, ($sp)
# initialise "variables"
   li   $s0, 2        # a = 2
   li   $s1, 3        # b = 3
   li   $s2, 2        # c = 2
   li   $s3, 4        # d = 4
   li   $s4, 6        # e = 6
   li   $s5, 3        # f = 3
# set up args
   move $a0, $s0
   move $a1, $s1
   move $a2, $s2
   move $a3, $s3
   addi $sp, $sp, -4
   sw   $s4, ($sp)
   addi $sp, $sp, -4
   sw   $s5, ($sp)
# call function
   jal  g
   nop
   addi $sp, $sp, 8
# display result
   move $a0, $v0
   li   $v0, 1
   syscall
   li   $a0, '\n'
   li   $v0, 11
   syscall
# epilogue
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   jr   $ra

g:
# prologue
   addi $sp, $sp, -4
   sw   $ra, ($sp)
# u+v+w*w*x*y*z;
   move $t0, $a0
   add  $t0, $t0, $a1
   move $t1, $a2
   mul  $t1, $t1, $a2
   mul  $t1, $t1, $a3
   lw   $t2, 8($sp)
   mul  $t1, $t1, $t2
   lw   $t2, 4($sp)
   mul  $t1, $t1, $t2
   add  $v0, $t0, $t1
# epilogue
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   jr   $ra
