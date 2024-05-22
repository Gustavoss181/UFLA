.globl main

.data
	string1: .asciiz "Digite um numero inteiro: "
	string2: .asciiz "Soma: "

.text

main:
	li $v0, 4
	la $a0, string1
	syscall
	li $v0, 5
	syscall
	move $a1, $v0
	
	jal soma
	
	li $v0, 4
	la $a0, string2
	syscall
	li $v0, 1
	move $a0, $v1
	syscall
	
	#encerra o main
	li $v0, 10
	syscall

soma:	
	li $v1, 0
loop:
	beqz $a1, exitLoop
	add $v1, $v1, $a1
	subi $a1, $a1, 1
	j loop
exitLoop:
	jr $ra
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
