.globl main

.data
	lerBase: .asciiz "Base: "
	lerExpoente: .asciiz "Expoente: "
	saida: .asciiz "Resultado: "

.text
	#a0- base
	#a1 - potencia
	#s0 - contador
	#s1 - resultado da potenciacao

main:
	li $v0, 4
	la $a0, lerBase
	syscall
	li $v0, 5
	syscall
	move $a1, $v0
	
	li $v0, 4
	la $a0, lerExpoente
	syscall
	li $v0, 5
	syscall
	move $a2, $v0
	
	jal Potencia
	
	li $v0, 4
	la $a0, saida
	syscall
	move $a0, $v1
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall
	 

Potencia:
	addi $v1, $v1, 1
	
func_Loop:
	beq $s0, $a2, Exit
	mul $v1, $v1, $a1
	addi $s0, $s0, 1
	j func_Loop
	
Exit:
	jr $ra
	
