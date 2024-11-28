.data
	prompt: .asciiz "Digite um número na base decimal: "
	result: .asciiz "O mesmo numero na base binaria: "

.text
.globl main

main:
	# Imprimir o prompt
	li $v0, 4
	la $a0, prompt
	syscall
	
	# Ler a entrada
    	li $v0, 5
    	syscall
    	move $a1, $v0
    	
    	li $v0, 4
	la $a0, result
	syscall
    	
    	jal transformar
    		
	#encerrar o programa
	li $v0, 10
	syscall
	
transformar:
	bne $a1, 1, else
	#encerrar recursao e retornar
	li $a0, 1
	li $v0, 1
	syscall
	j exit

else:
	andi $t0, $a1, 1 # n mod 2
	addi $sp, $sp, -4
	sw $t0, 0($sp) # guarda o mod na pilha
	
	srl $a1, $a1, 1 # n / 2
	addi $sp, $sp, -4
	sw $ra, 0($sp) # guarda o mod na pilha
	
	jal transformar

exit:	
	#Volta recursivamente na pilha
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $a0, 0($sp)
	addi $sp, $sp, 4
	li $v0, 1
	syscall
	jr $ra
	