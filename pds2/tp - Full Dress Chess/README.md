# tb-pds2-g4

# Full Dress Chess

Full Dress Chess trata-se de um jogo de Xadrez criado como trabalho prático para a disciplina de Programação e Desenvolvimento de Sistemas II (PDS2) pelo grupo: 

  - Guilherme de Abreu Lima Buitrago Miranda
  - Lucas Paulo Martins Mariz
  - Thales Aparecido Silva Elias
  - Victor Hugo Silva Moura

Professor Orientador: Flávio Figueiredo
UFMG - 2018/2

# Funcionalidades

Trata-se de um jogo de Xadrez PvP (Player versus Player) com o intuito de praticar:

  - A linguagem C++;
  - Os conceitos e boas práticas de POO (Programação Orientada a Objetos);
  - Desenvolvimento guiado a testes (TDD)
  - Trabalho em equipe e divisão de tarefas em projetos de Software.

### Instalação

Para instalar o jogo num sistema unix, execute os seguintes comandos no terminal:

```sh
$ git clone https://github.com/pds2/tb-pds2-g4.git
$ cd tb-pds2-g4
$ make
```

### Jogando

Para executar o jogo, utilize o comando:

```sh
$ ./bin/main
```

Digite, agora, o nome do jogador 1 e do jogador 2.
Feito isso, o jogo será iniciado e, em cada jogada, é necessário seguir 2 passos:

 - Digitar a coordenada para selecionar uma peça (ex: D2)
 - Digitar a coordenada para onde a peça selecionada deverá mover-se (ex: D4)

Com isso, caso o movimento desejado for válido, a peça é movida a vez é transferida para o outro jogador. Caso contrário, o programa gera uma saída informando que o movimento é inválido e a jogada continua sendo do jogador atual até que uma jogada válida seja efetivada.

O programa é encerrado quando o objetivo final do xadrez é alcançado por um dos dois jogadores: comer o rei inimigo.

