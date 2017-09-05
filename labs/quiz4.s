	.data
result:
	.word 1

	.text

main:
   li   $t1, 0
   li   $t2, 1
   li   $t3, 10
loop:
   bgt  $t2, $t3, end_loop
   mul  $t1, $t1, $t2
   addi $t2, $t2, 1
   j    loop
end_loop:
   sw   $t1, result


t1 = 0
t2 = 1
t3 = 10

while t2 > t3 {
   t1 = t1 * t2
   t2 = t2 + 1
}

result = t1