   .data
stu1:
   .space 56
stu2:
   .space 56

   .text
   .globl main
main:
   # prologue
   add  $sp, $sp, -4
   sw   $fp, ($sp)
   move $fp, $sp
   add  $sp, $sp, -4
   sw   $ra, ($sp)
   # function body
   li  $t0  5012345      
   sw  $t0, stu1+0       # stu1.id = 5012345;
   li  $t0, 3778
   sw  $t0, stu1+44      # stu1.program = 3778;
   la  $s1, stu2         # stu = & stu2;
   li  $t0, 3707
   sw  $t0, 44($s1)      # stu->program = 3707;
   li  $t0, 5034567
   sw  $t0, 0($s1)       # stu->id = 5034567;
   # epilogue
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   jr   $ra
