# char a[100];
# ...
# call mylength(a,99)

   .data
a: .space 100
   .text
...
   la   $a0, a
   li   $a1, 99
   jal  mylength
   # result in $v0
...
mylength:
   # save registers, etc.
   # compute length
   # $v0 = length
   # restore saved registers
   jr   $ra
