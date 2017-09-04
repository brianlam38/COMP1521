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
   #.space 4    # method 1 (.space): allocate space for 4-byte int
   .word 1    # method 2 (.word): store 1 32-bit (4-byte) quantity memory address


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
   la   $a0, msg1             # load address msg1 into reg[$a0]
   li   $v0, 4                # load str print instruction
   syscall                    # print

   # scanf("%d", &n);
   li   $v0, 5                # load "read int" instruction
   syscall

   sw   $v0, n       # store input into var n
   lw   $a0, n       # load value of n into a0
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
   li   $t1, 1  # t1 = 1 fac value
   li   $t2, 1  # t2 = 1 counter
   lw   $t3, n  # t0 = n value
while:
   bge  $t2, $t3, end_while      # 1 <= n    // WHY ISN'T THIS BLE? Isn't BGE $t2 >= $t3
   addi $t2, $t2, 1              # t2++
   mul  $t1, $t1, $t2            # val = val * counter
   j    while
end_while:
   sw   $t1, n       # n = t1
   move $a0, $t1     # a0 = t1
   li   $v0, 1       # print integer
   syscall

   lw   $ra, fac_ret_save
   jr   $ra            # return ($v0)



