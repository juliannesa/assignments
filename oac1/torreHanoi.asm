.data
parte1: .asciiz "\n Peca "
parte2: .asciiz " que esta na haste "
parte3: .asciiz " vai para a haste "
.text
.globl main
main:
	li $v0,  5				# recebe o número de peças
	syscall		


	add $a0, $v0, $zero		# move para $a0
	li $a1, '1'				# armazena o nome das hastes
	li $a2, '2'				# armazena o nome das hastes
	li $a3, '3'				# armazena o nome das hastes

	jal torredehanoi		# chama a parte do código TorredeHanoi e volta para essa parte depois que executar

	li $v0, 10				# fecha
	syscall

torredehanoi:

	
	addi $sp, $sp, -20		# decresce a pilha para que seja possível armazenar valores
	sw   $ra, 0($sp)		# armazena na pilha os valores que estão nos registradores
	sw   $s0, 4($sp)		# offset de 4 para armazenar em um arranjo
	sw   $s1, 8($sp)
	sw   $s2, 12($sp)
	sw   $s3, 16($sp)

	add $s0, $a0, $zero		# move para $s0
	add $s1, $a1, $zero		# move para $s1
	add $s2, $a2, $zero		# move para $s2
	add $s3, $a3, $zero		# move para $s3

	addi $t1, $zero, 1
	beq $s0, $t1, print		# funciona como o if 

	recursiva1:

		addi $a0, $s0, -1 
		add $a1, $s1, $zero	# move para $a1
		add $a2, $s3, $zero	# move para $a2
		add $a3, $s2, $zero	# move para $a3
		jal torredehanoi	# recursão

		j print				# chama a parte que imprime

	recursiva2:

		addi $a0, $s0, -1
		add $a1, $s2, $zero	# move para $a1
		add $a2, $s1, $zero	# move para $a2
		add $a3, $s3, $zero	# move para $a3
		jal torredehanoi	# recursão

	fim:
	
		lw   $ra, 0($sp)	# restaura os registradores
		lw   $s0, 4($sp)	# novamente há offset de 4
		lw   $s1, 8($sp)
		lw   $s2, 12($sp)
		lw   $s3, 16($sp)

		addi $sp, $sp, 20	# ajusta para excluir os itens

		jr $ra				# retorna para main

	print:

		li $v0,  4			# imprime a primeira parte da string 
		la $a0,  parte1
		syscall
		li $v0,  1			# imprime a peça usada que é um int
		add $a0, $s0, $zero
		syscall
		li $v0,  4			# imprime a segunda parte da string 
		la $a0,  parte2
		syscall
		li $v0,  11			# print a haste que a peça esta que é um caracter
		add $a0, $s1, $zero
		syscall
		li $v0,  4			# imprime a terceira parte da string 
		la $a0,  parte3
		syscall
		li $v0,  11			# imprime a haste que peça vai que é um caracter
		add $a0, $s3, $zero
		syscall

		beq $s0, $t1, fim	# funciona como o if, se $s0 e $t1 tiverem valor igual, vai para fim
		j recursiva2		# chama a 2 parte recursiva