        .data
row0:   .space 16
row1:   .space 16
row2:   .space 16
row3:   .space 16
matrix: .word row0, row1, row2, row3

        .text
        .globl main
main:   jr $ra
