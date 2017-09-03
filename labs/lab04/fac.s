# COMP1521 Lab 04 ... Simple MIPS assembler


### Global data

   .data
msg1:
   .asciiz "n: "
msg2:
   .asciiz "n! = "
eol:
   .asciiz "\n"

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

   la   $a0, msg1             # load arg msg1 into reg[$a0]
   li   $v0, 4                # load str print instruction
   syscall                    # print

                              # scanf("%d", &n);
                              # printf("n! = %d\n", fac(n));

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

   lw   $ra, fac_ret_save
   jr   $ra            # return ($v0)

