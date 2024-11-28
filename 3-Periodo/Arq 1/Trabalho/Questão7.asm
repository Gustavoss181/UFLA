.text
	#a0- base
	#a1 - potencia
	#s0 - contador
	#s1 - resultado da potenciacao
	
	li $s0, 0
	
	li $v0, 5
	syscall
	move $a0, $v0
	
	li $v0, 5
	syscall
	move $a1, $v0
	move $v0, $zero
	
	jal Potencia
	
	move $a0, $v0
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall
	 
	
	

Potencia:
	addi $v0, $v0, 1
	
	
	
func_Loop:
	beq $s0, $a1, Exit
	mul $v0, $v0, $a0
	addi $s0, $s0, 1
	j func_Loop
	
	
Exit:
	jr $ra
	