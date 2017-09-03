# i = 1; sum = 0;
# while (i < 20) {
#    sum += i;
#    i++;
# }

   li   $t1, 1
   li   $t2, 0
while:
   li   $t3, 20
   bge  $t1, $t3, end_while
   add  $t2, $t2, $t1  # sum += i
   addi $t1, $t1, 1   # i++
   j    while
end_while:
