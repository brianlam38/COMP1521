      .data
x:    .word 0x00010101
y:    .word 0x10010000
z:    .word 0x0000002A
eol:  .asciiz "\n"

# different to the exercise,
# we're loading into $a0
      .text
main:
s1:   la $a0, x

      li $v0, 1    # print the value
      syscall      # that was loaded
      la $a0, eol
      li $v0, 4
      syscall

s2:   lw $a0, x

      li $v0, 1    # print the value
      syscall      # that was loaded
      la $a0, eol
      li $v0, 4
      syscall

s3:   lb $a0, x

      li $v0, 1    # print the value
      syscall      # that was loaded
      la $a0, eol
      li $v0, 4
      syscall

s4:   la $s0, z
      lw $a0, ($s0)

      li $v0, 1    # print the value
      syscall      # that was loaded
      la $a0, eol
      li $v0, 4
      syscall

s5:   li $s0, 8
      lw $a0, y($s0)

      li $v0, 1    # print the value
      syscall      # that was loaded
      la $a0, eol
      li $v0, 4
      syscall

s6:   lw $s0, y
      lw $a0, ($s0)

      li $v0, 1    # print the value
      syscall      # that was loaded
      la $a0, eol
      li $v0, 4
      syscall

s7:   li $s0, 4
      lw $a0, x+4($s0)

      li $v0, 1    # print the value
      syscall      # that was loaded
      la $a0, eol
      li $v0, 4
      syscall

end:  jr $ra


