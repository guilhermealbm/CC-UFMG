.data
n: .word 5

.text
lw x5, n
jal x1, fat
    
addi a1, x10, 0 #Coloca o resultado no registrador de saída
addi a0, x0, 1 
ecall # Escreve o Retorno
    
addi a0, x0, 10
ecall # exit

fat:
    addi sp,sp,-8 #Anda 2 words na memória
    sw   x1,4(sp) #Armazena x1 em memória
    sw   x5,0(sp) #Armazena x5 em memória
    addi x5,x5,-1 #Decrementa x5
    bge  x5,x0,L1 
    addi x10,x0,1 #Incrementa x10
    addi sp,sp,8 #Anda com o stack pointer 2 words
    jalr x0,0(x1) # Retorno
    
L1:
    addi x10,x10,-1 #Decrementa x10
    jal  x1,fat 
    addi x6,x10,0 
    lw   x10,0(sp) #Carrega da memória para x10
    lw   x1,4(sp) #Carrega da memória para x1
    addi sp,sp,8 #Incrementa o stack pointer
    mul  x10,x10,x6 #Faz a operação básica do fatorial (n * n-1)
    jalr x0,0(x1) #Retorno