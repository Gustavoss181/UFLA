.globl main

.data
	string1: .asciiz "Digite um numero inteiro: "
	string2: .asciiz "Soma: "

.text
	#dicionario: s1 - i / s2 - somatorio / s0 - numero fornecido / s3 - resto / s4 - divisão por 2

main:
	#pegando valor n
	li $v0, 5
	syscall
	move $s0, $v0
	
	li $s1, 1
	li $s2, 0
	li $s4, 2
	
Loop:
	bgt  $s1, $s0, Exit
	div $s1, $s4
	mfhi $s3
	beqz $s3, Soma
	addi $s1, $s1, 1
	j Loop


Soma:
	add $s2, $s2, $s1
	addi $s1, $s1, 1
	j Loop


Exit:
	li $v0, 1
	move $a0, $s2
	syscall
	li $v0, 10
	
	
	
	
	
