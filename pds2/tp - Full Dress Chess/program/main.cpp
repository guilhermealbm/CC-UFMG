#include "../include/game.h"

int main() {
	std::string jog1, jog2;
	std::cout << "Bem vindo ao nosso xadrez! \n ----------------------------- \nTrata-se de um jogo entre 2 jogadores (PvP)! \n \nPara jogar, selecione uma peça baseada em sua posição\nLetra e número conforme tabuleiro \nEntre com o nome do jogador 1 (peças brancas) \n";
	std::cin >> jog1;
	std::cout << "Entre com o nome do jogador 2 (peças pretas)\n";
	std::cin >> jog2;
    Game game(jog1, jog2);
    game.initGame();
    game.playGame();
    return 0;
}

// Command to run: $ make main && cd bin && ./main && cd .. && make clean && rm -r bin && rm -r build