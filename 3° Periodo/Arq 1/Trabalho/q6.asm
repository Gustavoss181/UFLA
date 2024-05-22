.globl main

.data
	string1: .asciiz "Digite os valores de n, i e j:\n"
	string2: .asciiz "Os n primeiros valores multiplos de i ou j: "
	espaco: .asciiz " "

.text

main:	
	li $v0, 4
	la $a0, string1
	syscall
	
	li $v0, 5
	syscall
	move $a1, $v0 # n
	
	li $v0, 5
	syscall
	move $a2, $v0 # i
	
	li $v0, 5
	syscall
	move $a3, $v0 # j

	jal valoresMultiplos
	
	#encerra o main
	li $v0, 10
	syscall

valoresMultiplos:

	li $v0, 4
	la $a0, string2
	syscall
	
	li $t0, 0 #cont
	li $t1, 0 #k
loop:
	beq $t0, $a1, exit
	
	div $t1, $a2
	mfhi $t2 # k%i
	div $t1, $a3
	mfhi $t3 # k%j
	
	beq $t2, $zero, then
	beq $t3, $zero, then
	j else
then:
	li $v0, 1
	move $a0, $t1
	syscall
	
	li $v0, 4
	la $a0, espaco
	syscall
	
	addi $t0, $t0, 1
else:
	addi $t1, $t1, 1
	j loop
exit:

	jr $ra
