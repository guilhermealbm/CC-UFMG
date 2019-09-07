.data #Tamanho dos arrays
array1_size: .word 4
array2_size: .word 4

#Preenchendo os arrays com elementos
array1:
    .word 1, 2, 3, 4
array2:
    .word 4, 2, 1, 3

.text
    la x17, array1_size
    lw x13, 0(x17) # Carregando primeiro tamanho
    la x17, array2_size
    lw x14, 0(x17) # Carregando segundo tamanho
    bne x13, x14, different_sizes
    
    add x12, x0, x0 #Variável auxiliar (contador 0 .. array1_size)
    addi s4, x0, 1 #S4 sempre = 1
    
    la t0 array1
    
    add x15, x14, x0 #Mantendo o tamanho dos arrays em x15
    addi x14, x0, -4 #x14 = tamanho da palavra
    mul x13, x13, x14 #Tamanho do vetor em bytes
    add sp, sp, x13 #Decrementando sp
    
    search_element_array1:    
        la t2 array2 #Começo do array2
        add x11, x0, x0 #Variável auxiliar (contador 0 .. array2_size)
        lw t1, 0(t0) # Lê novo valor no array1
        addi x12, x12, 1 #Incrementando contador
        blt x15, x12, exit_success #Se verdadeiro, é permutação
        sub t0, t0, x14 # Avança uma posição no vetor
        jal search_element_array2
        
	search_element_array2:
        lw t3, 0(t2) # Lê novo valor
        sub t2, t2, x14 # Avança uma posição no vetor
        addi x11, x11, 1 #Incrementando contador
        beq t1, t3, equal_element
        bge x15, x11, search_element_array2
        addi x10, x0, 0 # Coloca em X10 falso
        jal exit #Se chegou até aqui, o elemento não existe no vetor e,
        #portanto, não é uma permutação
        
	equal_element:
    	#Checa se a posição é 1 no vetor auxiliar. 
    	#Se for = 1, o elemento encontrado já foi usado 
    	#para chegar à permutação (em caso de elementos repetidos).
        mul x31, x11, x14
        add x31, x31, sp
        lw x30, 0(x31)
        beq x30, s4, search_element_array2 #Se for 1, 
        #volta para o search_element_array2
        sw s4, 0(x31)
        jal search_element_array1 #Se chegou até aqui, 
        #o elemento existe e pode voltar a pesquisa no array1
    
    different_sizes:
        addi x10, x0, 0 # Coloca em X10 falso
        jal x0, exit
    
	exit:
        addi a1, x10, 0 #Coloca o resultado no registrador de saída
        addi a0, x0, 1 
        ecall # Escreve o Retorno

        addi a0, x0, 10
        ecall # exit
        
	exit_success:
        addi x10, x0, 1 # Coloca em X10 verdadeiro 
        #(se chegou até aqui, é permutação)
        jal x0, exit