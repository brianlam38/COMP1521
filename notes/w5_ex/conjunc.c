# if (x != 0 && y != 0 && x > y)    |       .data
#   { statements1; }                |    x: .space 4
# else                              |    y: .space 4
#   { statements2; }                |

if_start:
   lw   $t0, x
   beqz $t0, else
   lw   $t1, y
   beqz $t1, else
   ble  $t0, $t1, else
then:
   mips(statements1)
   j    end_if
else:
   mips(statements2)
end_if:
