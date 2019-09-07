.data
input: .word -43 # Armazena na memória

.text
lw a0, input # Carrega da memória para o registrador

andi x10, a0, 1 # And com 1 faz o mesmo que pegar o último bit do número 
#(em binário), que diz se é par ou ímpar.
addi a1, x10, 0 # Coloca o resultado no registrador de saída

addi a0, x0, 1 # Fazendo o ecall escrever a resposta no console
ecall		 # Escreve a resposta