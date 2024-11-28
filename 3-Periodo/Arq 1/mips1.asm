.globl main

.data
var1: .word 2,4,3,10,1

.text

main:
	la $s6, var1
	add $s0, $zero, $zero #variavel i
loop1:
	slti $t0, $s0, 4 #se i e menor q 4
	beq $t0, $zero, exit1

	addi $s1, $s0, 1 #variavel j
loop2:
	slti $t0, $s1, 5 #se i e menor q 5
	beq $t0, $zero, exit2
	
	# 4i e passa o endereco de s6 pra t1
	sll $t0, $s0, 2
	add $t0, $t0, $s6
	lw $t1, 0($t0)
	
	#4j e passa o endereco de s6 pra t3
	sll $t2, $s1, 2
	add $t2, $t2, $s6
	lw $t3, 0($t2)

	blt $t1, $t3, exit3 #compara t1 e t3 ou vet[j] < vet[i]

	# swap
	sw $t1, 0($t2)
	sw $t3, 0($t0)

exit3:

	addi $s1, $s1, 1 #j++
	j loop2
exit2:

	addi $s0, $s0, 1 #i++
	j loop1
exit1:
