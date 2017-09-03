# COMP1521 Lab 04 ... Simple MIPS assembler


### Global data

   .data
msg1:
   .asciiz "n: "
msg2:
   .asciiz "n! = "
eol:
   .asciiz "\n"
n:
   .space 4

### main() function

   .data
   .align 2
main_ret_save:
   .word 4

   .text
   .globl main

main:
   sw   $ra, main_ret_save    # store address of main_ret_save into the return register

#  ... your code for main() goes here

   # printf("n: ");
   la   $a0, msg1             # load arg msg1 into reg[$a0]
   li   $v0, 4                # load str print instruction
   syscall                    # print

   # scanf("%d", &n);
   li   $v0, 5                # load "read int" instruction
   syscall

   move $a0, $v0              # move integer input to reg[$a0]
   li   $v0, 1                # load "print int" instruction
   syscall

   # printf("n! = %d\n", fac(n));
   jal  fac                   # jump to fac function

# ... end of code

   lw   $ra, main_ret_save    # load the value of main_ret_save into return register
   jr   $ra                   # jump to saved return address (start again)

### fac() function

   .data
   .align 2
fac_ret_save:
   .space 4

   .text

fac:
   sw   $ra, fac_ret_save

#  ... your code for fac() goes here
   #move $s0, $a0       # copy value of n into reg[$s0]
   #li   $v0, 1
   #syscall
   #li   $v0, 1          # load "print int" instruction
   #la   $a0, n          # load arg n into reg[$a0]
   #lw   $a0, ($a0)      # load into $a0 the contents of reg[$a0]
   #syscall

   lw   $ra, fac_ret_save
   jr   $ra            # return ($v0)

