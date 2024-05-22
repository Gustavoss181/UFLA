.globl main

.text

main:
	addi $a1, $zero, 5
	
	jal fib
	
	li $v0, 1
	move $a0, $v1
	syscall
	
	#encerra o main
	li $v0, 10
	syscall

fib:	
	bne $a1, $zero, if1
	li $v1, 0
	j exitFib
	
	if1:
	li $t1, 1
	bne $a1, $t1, else
	li $v1, 1
	j exitFib
	
	else:
	
		
	exitFib:
	jr $ra
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	