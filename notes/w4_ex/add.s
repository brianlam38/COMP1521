# add.s ... add two numbers
# 
# int x = 3;
# int y = 4;
# void main(void) { printf("%d\n", x+y); }

      .data
x:    .word  3          # int x = 3;
y:    .word  4          # int y = 4;
eol:  .asciiz "\n"

     .text
main:
      lw  $t0, x        # t0 = x
      lw  $t1, y        # t1 = y
      add $a0, $t0, $t1 # a0 = t0 + t1
      li  $v0,1         
      syscall           # printf("%d",a0)
      la  $a0, eol
      li  $v0,4
      syscall           # printf("\n")
      jr  $ra           # return from main
