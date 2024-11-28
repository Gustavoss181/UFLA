.globl main

.data 
	string1: .asciiz "Digite um numero inteiro: "
	perfeito: .asciiz "O numero e perfeito" 
	nperfeito: .asciiz "O numero n eh perfeito"
	
.text

main:
	#Dicionario
	#s0 - numero passdo pelo usuario
	#s1 - contador
	#s2 - resto da divisão
	#s3 somador
	
	li $v0, 4
	la $a0, string1
	syscall
	li $v0, 5
	syscall
	move $s0, $v0
	
	li $s1, 1
	li $s3, 0
	jal NumPerfeito
	
	li $v0, 10
	syscall
	
	
NumPerfeito:
	beq $s0, $s1, Perfeito
	j Loop

Loop:
	div $s0, $s1
	mfhi $s2
	beqz $s2, Divisor
	addi $s1, $s1, 1
	j NumPerfeito
	
Divisor:
	add $s3, $s3, $s1
	addi $s1, $s1, 1
	j NumPerfeito
	
	
Perfeito:
	bne $s3, $s0, Exit
	li $v0, 4
	la $a0, perfeito
	syscall
	
	jr $ra
	
Exit:
	li $v0, 4
	la $a0, nperfeito
	syscall
	
	jr $ra
	
	
	
	
	
	 
