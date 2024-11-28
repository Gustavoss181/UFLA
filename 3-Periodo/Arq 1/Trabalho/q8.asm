.data
	prompt: .asciiz "Digite um número: "
	result1: .asciiz "E um numero triangular"
	result2: .asciiz "Nao e um numero triangular"

.text

main:
    	# Imprimir o prompt
    	li $v0, 4
    	la $a0, prompt
    	syscall

    	# Ler a entrada
    	li $v0, 5
    	syscall
    	move $a1, $v0

	jal funcao
	
	li $v0, 10
    	syscall

funcao:
    	# Inicializa o contador
    	li $s1, 1

loop:
	# Verifica se o (número atual * o próximo número * o próximo + 1 número) = entrada
	addi $t1, $s1, 1
	mul $t0, $s1, $t1
	addi $t1, $t1, 1
	mul $t0, $t0, $t1

	beq $t0, $a1, print_result1
        
	addi $s1, $s1, 1
	blt $t0, $a1, loop
	j print_result2

print_result1:
    	li $v0, 4
    	la $a0, result1
    	syscall
    	
    	jr $ra
    
print_result2:
    	li $v0, 4
    	la $a0, result2
    	syscall
    	
    	jr $ra
    	




