# hello1.s ... print "Hello, MIPS"

      .data          # the data segment
msg:  .asciiz "Hello, MIPS\n"

      .text          # the code segment
      .globl main
main:  
      la $a0, msg    # load the argument string
      li $v0, 4      # load the system call (print_str)
      syscall        # print the string
      li $v0, 10     # load the system call (exit)
      syscall        # exit the program
