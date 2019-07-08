#include "../include/game.h"

Game::Game(std::string namePlayer1, std::string namePlayer2) : 
	player1(Player(namePlayer1, "White", field)), player2(Player(namePlayer2, "Black", field)) {}

void Game::initGame() {
	std::cout << "O game foi iniciado!" << '\n';

	this->field.initField();
	std::system("clear || cls");
}

void Game::playGame() {
	char pieceX, finalX;
	char pieceY, finalY;

	//provisório
	while(true){
		do{
			this->field.printField();

			try{
				std::cout << this->player1.getName() + ", digite as coordenadas da peça x (letra) e y (numero)\n";
				std::cin >> pieceY >> pieceX;
				std::cin.clear();
				std::cin.ignore(__INT_MAX__, '\n');
				std::cout << this->player1.getName() + ", digite as coordenadas de destino x (letra) y (numero)\n";
				std::cin >> finalY >> finalX;
				std::cin.clear();
				std::cin.ignore(__INT_MAX__, '\n');

				std::system("clear || cls");

				if(!isdigit(pieceX) || !isdigit(finalX))
					throw std::invalid_argument("Entrada Invalida");

				if(!isalpha(pieceY) || !isalpha(finalY))
					throw std::invalid_argument("Entrada Invalida");


			}catch(std::invalid_argument e){
				std::cout << e.what() <<std::endl;
			}

		} while(!this->player1.makeMove((int((pieceX)-CHARTOINT)), (int((tolower(pieceY))-CHARTOLETTER)), (int((finalX)-CHARTOINT)), (int((tolower(finalY)))-CHARTOLETTER)));
		
		if(this->field.kingInCheck(this->player2.getColor())){
			std::cout << "Rei " + this->player2.getColor() + " em xeque\n";
		}
		
		do{
			this->field.printField();
			
			try{
				std::cout << this->player2.getName() + ", digite as coordenadas da peça x (letra) e y (numero)\n";
				std::cin >> pieceY >> pieceX;
				std::cin.clear();
				std::cin.ignore(__INT_MAX__, '\n');
				std::cout << this->player2.getName() + ", digite as coordenadas de destino x (letra) y (numero)\n";
				std::cin >> finalY >> finalX;
				std::cin.clear();
				std::cin.ignore(__INT_MAX__, '\n');

				std::system("clear || cls");

				if(!isdigit(pieceX) || !isdigit(finalX))
					throw std::invalid_argument("Entrada Invalida");

				if(!isalpha(pieceY) || !isalpha(finalY))
					throw std::invalid_argument("Entrada Invalida");


			}catch(std::invalid_argument e){
				std::cout << e.what() <<std::endl;
			}


		} while(!this->player2.makeMove((int((pieceX)-CHARTOINT)), (int((tolower(pieceY))-CHARTOLETTER)), (int((finalX)-CHARTOINT)), (int((tolower(finalY)))-CHARTOLETTER)));
		
		if(this->field.kingInCheck(this->player1.getColor())){
			std::cout << "Rei " + this->player1.getColor() + " em xeque\n";
		}
	}
}
