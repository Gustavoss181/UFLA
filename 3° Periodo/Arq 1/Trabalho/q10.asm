.data
	string1: .asciiz "Digite os tres lados do triangulo:\n"
    	retangulo: .asciiz "E um triangulo retangulo"
    	n_retangulo: .asciiz "Nao e um triangulo retangulo"

.text
    	.globl main
    	.globl Verificar

main:
	la $a0, string1
    	li $v0, 4
    	syscall
    	#ler n1
    	li $v0, 5
    	syscall
    	move $a0, $v0
    	#ler n2
    	li $v0, 5
    	syscall
    	move $a1, $v0
    	#ler n3
    	li $v0, 5
    	syscall
    	move $a2, $v0

    	#chama a função Verificar
    	jal Verificar
    	
    	li $v0, 10
    	syscall

Verificar:
    	#(n1 * n1) == (n2 * n2) + (n3 * n3)
    	mul $s0, $a0, $a0 #n1^2
    	mul $s1, $a1, $a1 #n2^2
    	mul $s2, $a2, $a2 #n3^2
    	add $t0, $s1, $s2
    	beq $t0, $s0, final_certo
    	add $t0, $s0, $s1
    	beq $t0, $s2, final_certo
    	add $t0, $s0, $s2
    	beq $t0, $s1, final_certo
    
    	#else final, deu errado
    	la $a0, n_retangulo
    	li $v0, 4
    	syscall
    	
    	jr $ra

final_certo:
	la $a0, retangulo
    	li $v0, 4
    	syscall
    	
    	jr $ra
