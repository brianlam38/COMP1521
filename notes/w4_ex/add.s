# add.s ... add two numbers
# 
# int x = 3;
# int y = 4;
# void main(void) { printf("%d\n", x+y); }

      .data             # EVERYTHING BELOW WILL BE IN DATA SEGMENT
x:    .word  3          # int x = 3;
y:    .word  4          # int y = 4;
eol:  .asciiz "\n"

     .text              # EVERYTHING BELOW WILL BE IN CODE/TEXT SEGMENT
main:
      lw  $t0, x        # t0 = x                load word x into temp reg
      lw  $t1, y        # t1 = y                load word w into temp reg
      add $a0, $t0, $t1 # a0 = t0 + t1          add x w and store into first reg    reg[a0] = reg[t0] + reg[t1]
      li  $v0,1         #                       load instruction syscall 1 (print number)
      syscall           # printf("%d",a0)       execute print number (the sum)
      la  $a0, eol      #                       load argument end of line \n
      li  $v0,4         #                       load instruction syscall 4 (print str)
    # -- method 2: load \n directly --
    # li $a0, 0x0a
    # li $v0, 11        # 11 = sys call for print char
      syscall           # printf("\n")          execute print str (the newline)
      jr  $ra           # return from main      jump back to start
