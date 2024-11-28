.globl main

.text

main:
	li $t1, 19
	andi $t2, $t1, 1
	srl $t1, $t1, 1
	srl $t1, $t1, 1
	srl $t1, $t1, 1
	srl $t1, $t1, 1
