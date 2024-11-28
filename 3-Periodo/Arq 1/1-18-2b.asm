.globl main

.data
var1: .word 2

.text

main:
	addi $s0, $zero, 10
	addi $s1, $zero, 1
	la $s2, var1
	
	add $t0, $zero, $zero #variavel i
loop1:
	slt $t2, $t0, $s0 #se i e menor q a
	beq $t2, $zero, exit1

	add $t1, $zero, $zero #variavel j
loop2:
	slt $t2, $t1, $s1 #se j e menor q b
	beq $t2, $zero, exit2
	
	sll $t2, $t1, 2 #j*4
	sll $t2, $t2, 2 #J*4 pro tamanho da palavra
	add $t2, $t2, $s2 #joga pro endereco
	add $t3, $t0, $t1 #i+j
	sw $t3, 0($t2) #D[j*4] = i+j

	addi $t1, $t1, 1 #j++
	j loop2
exit2:

	addi $t0, $t0, 1 #i++
	j loop1
exit1:
