.globl main

.data
	string1: .asciiz "Digite um numero inteiro: "
	string2: .asciiz "Produto: "

.text
	#dicionario: s1 - i / s2 - somatorio / a0 - numero fornecido / s3 - resto / s4 - divisão por 2
	
main:
	#pegando valor n
	li $v0, 4
	la $a0, string1
	syscall
	li $v0, 5
	syscall
	move $a0, $v0
	
	li $s1, 1
	li $v1, 1
	li $s4, 2
	
	jal NumerosPares
	
	li $v0, 4
	la $a0, string2
	syscall
	move $a0, $v1
	li $v0, 1
	syscall


	#termino da main
	li $v0, 10
	syscall
	
	
NumerosPares:
	bgt  $s1, $a0, Exit
	j Loop
	
Loop:
	div $s1, $s4
	mfhi $s3
	beqz $s3, Mult
	addi $s1, $s1, 1
	j NumerosPares
	
Mult:
	mul $v1, $v1, $s1
	addi $s1, $s1, 1
	j NumerosPares


Exit:
	jr $ra
	
	
	
	
	
