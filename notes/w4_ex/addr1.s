      .data
x:    .word 0x00010101
y:    .word 0x10010000
z:    .word 0x0000002A
eol:  .asciiz "\n"

      .text
main:
      move $s7, $ra

s1:   la   $a0, x
      jal  print

s2:   lw   $a0, x
      jal  print

s3:   lb   $a0, x
      jal  print

s4:   la   $s0, z
      lw   $a0, ($s0)
      jal  print

s5:   li   $s0, 8
      lw   $a0, y($s0)
      jal  print

s6:   lw   $s0, y
      lw   $a0, ($s0)
      jal  print

s7:   li   $s0, 4
      lw   $a0, x+4($s0)
      jal  print

end_main:
      move $ra, $s7
      jr   $ra

# print function

print:
      move $s1, $a0
      li   $v0, 1
      syscall
      la   $a0, eol
      li   $v0, 4
      syscall
      move $a0, $s1
      jr   $ra


