.globl main

.data
	s1: .asciiz "Digite a quantidade n de numeros que serao lidos: "
	s2: .asciiz "Digite os numeros:\n"
	s3: .asciiz "Numeros ordenados em ordem decrescente: "
	espaco: .asciiz " "
	vetor: .word 0

.text

main:
	jal soma
	
	#encerra o main
	li $v0, 10
	syscall

soma:	
	li $v0, 4
	la $a0, s1
	syscall
	
	la $s2, vetor
	#digite os proximos numeros
	
	li $v0, 5
	syscall
	move $s0, $v0 #Le do usuario e armazena em s0 (n)
	
	#reserva espaço pro vetor com tamanho n
	
	li $v0, 4
	la $a0, s2
	syscall
	
#armazena no vetor os valores de entrada
	add $t0, $zero, $zero #variavel i
loop:
	slt $t1, $t0, $s0 #se i e menor q n
	beq $t1, $zero, exit
	
	li $v0, 5
	syscall
	move $t2, $v0 #Le do usuario
	
	sll $t1, $t0, 2
	add $t1, $t1, $s2
	sw $t2, 0($t1)
	
	addi $t0, $t0, 1 #i++
	j loop
exit:
	
#ordena o vetor em ordem decrescente
	add $t0, $zero, $zero #variavel i
loop1:
	subi $t2, $s0, 1
	slt $t2, $t0, $t2 #se i e menor q n-1
	beq $t2, $zero, exit1

	addi $t1, $t0, 1 #variavel j
loop2:
	slt $t2, $t1, $s0 #se j e menor q n
	beq $t2, $zero, exit2
	
	# 4i e passa o endereco de s2 pra t2
	sll $t2, $t0, 2
	add $t2, $t2, $s2
	lw $t3, 0($t2)
	
	#4j e passa o endereco de s2 pra t4
	sll $t4, $t1, 2
	add $t4, $t4, $s2
	lw $t5, 0($t4)

	bgt $t3, $t5, exit3 #compara vet[j] > vet[i]

	# swap
	sw $t3, 0($t4)
	sw $t5, 0($t2)

exit3:

	addi $t1, $t1, 1 #j++
	j loop2
exit2:

	addi $t0, $t0, 1 #i++
	j loop1
exit1:
	
#mostra os valores em ordem decrescente

	li $v0, 4
	la $a0, s3
	syscall

	add $t0, $zero, $zero #variavel i
loop4:
	slt $t1, $t0, $s0 #se i e menor q n
	beq $t1, $zero, exit4
	
	sll $t1, $t0, 2
	add $t1, $t1, $s2
	lw $t2, 0($t1)
	
	li $v0, 1
	move $a0, $t2
	syscall
	li $v0, 4
	la $a0, espaco
	syscall
	
	addi $t0, $t0, 1 #i++
	j loop4
exit4:
	
	jr $ra
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
