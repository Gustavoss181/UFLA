.globl main

.text

main:
	addi $s0, $zero, 10
	addi $s1, $zero, 1
	
	add $t0, $zero, $zero #variavel i
loop1:
	slt $t2, $t0, $s0 #se i e menor q a
	beq $t2, $zero, exit1

	add $s0, $s0, $s1

	addi $t0, $t0, 1 #i++
	j loop1
exit1:
