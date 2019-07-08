#include "../include/field.h"
#include <iostream>
#include "../include/termcolor/termcolor.hpp"

Field::Field() { }

void Field::initField() {
    std::cout << "O field foi iniciado!" << '\n';

    std::string colors[2] = {"Black", "White"};

    //x-axis -> rows
    //y-axis -> colums
    Pieces* pieces[8][8] = {
        {new Rook(1, 1, colors[1]), new Knight(1, 2, colors[1]), new Bishop(1, 3, colors[1]), new Queen(1, 4, colors[1]),
        new King(1, 5, colors[1]), new Bishop(1, 6, colors[1]), new Knight(1, 7, colors[1]), new Rook(1, 8, colors[1])},
        {new Pawn(2, 1, colors[1], 1), new Pawn(2, 2, colors[1], 1), new Pawn(2, 3, colors[1], 1), new Pawn(2, 4, colors[1], 1),
        new Pawn(2, 5, colors[1], 1), new Pawn(2, 6, colors[1], 1), new Pawn(2, 7, colors[1], 1), new Pawn(2, 8, colors[1], 1)},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {new Pawn(7, 1, colors[0], 0), new Pawn(7, 2, colors[0], 0), new Pawn(7, 3, colors[0], 0), new Pawn(7, 4, colors[0], 0),
        new Pawn(7, 5, colors[0], 0), new Pawn(7, 6, colors[0], 0), new Pawn(7, 7, colors[0], 0), new Pawn(7, 8, colors[0], 0)},
        {new Rook(8, 1, colors[0]), new Knight(8, 2, colors[0]), new Bishop(8, 3, colors[0]), new Queen(8, 4, colors[0]),
        new King(8, 5, colors[0]), new Bishop(8, 6, colors[0]), new Knight(8, 7, colors[0]), new Rook(8, 8, colors[0])}
    };

    for(int i = POS_MIN - 1; i < POS_MAX; i++){
        for(int j = POS_MIN - 1; j < POS_MAX; j++){
            allPieces[i][j] = pieces[i][j];
        }
    }
}

Pieces* Field::getPiece(int x, int y) {
    if(x >= POS_MIN && x <= POS_MAX && y >=POS_MIN && y <=POS_MAX){
        return allPieces[x-1][y-1];
    }
    return nullptr;
}

//check if a position in field is occupied by another piece
bool Field::isOccupied(int x, int y) {
    if(this->getPiece(x, y) != nullptr) {
        return true;
    }
    else {
        return false;
    }
}

bool Field::isOccupiedByEnemy(int x, int y, std::string color){
    if(this->getPiece(x, y)->getColor() == color)
        return false;
    else
        return true;
}

bool Field::hasOtherPieceOnTheWay(Pieces *piece, int x, int y){
    std::string pieceName = piece->getName();
    int xAtual = piece->getX();
    int yAtual = piece->getY();

    if(pieceName == "queen" || pieceName == "bishop" || pieceName == "rook" || pieceName == "pawn"){
        while(xAtual != x || yAtual != y) {
            if(xAtual < x)
                xAtual++;
            else if(xAtual > x)
                xAtual--;

            if(yAtual < y)
                yAtual++;
            else if(yAtual > y)
                yAtual--;

            if(allPieces[xAtual-1][yAtual-1] != nullptr && xAtual != x && yAtual != y)
                return true;
        }
    }
    return false;
}

bool Field::move(Pieces *piece, int x, int y) {
    if(x >= POS_MIN && x <= POS_MAX && y >= POS_MIN && y <= POS_MAX) {
        if(piece->movimentValidator(x, y)) {
            if(!this->hasOtherPieceOnTheWay(piece, x, y)) {
                if(this->isOccupied(x, y)) {
                    if(this->isOccupiedByEnemy(x, y, piece->getColor())) {
                        int xAnt = piece->getX(),
                            yAnt = piece->getY();

                        if(allPieces[x-1][y-1]->getName() == "king"){
                            std::cout << "Fim de jogo. O último jogador venceu!!!" << std::endl;
                            std::exit(EXIT_SUCCESS);
                        }

                        delete (allPieces[x-1][y-1]);

                        piece->setX(x);
                        piece->setY(y);
                        this->allPieces[x-1][y-1] = piece;
                        this->allPieces[xAnt-1][yAnt-1] = nullptr;
                    }
                    else{
                        std::cout << "Posição ocupada\n";
                        return false;
                    }
                }
                else {
                    int xAnt = piece->getX(),
                        yAnt = piece->getY();

                    piece->setX(x);
                    piece->setY(y);
                    this->allPieces[x-1][y-1] = piece;
                    this->allPieces[xAnt-1][yAnt-1] = nullptr;
                }
            }
            else {
                std::cout << "Peça no caminho\n";
                return false;
            }
        //Checking pawn capture of enemy piece
        } else if(piece->getName()=="pawn" && this->isOccupied(x, y)){
            if(this->isOccupiedByEnemy(x, y, piece->getColor())){
                if((piece->movementDirection && x - piece->getX() == 1 && abs(y - piece->getY()) == 1) ||
                    (!piece->movementDirection && piece->getX() - x == 1 && abs(y - piece->getY()) == 1)) {

                    int xAnt = piece->getX(),
                        yAnt = piece->getY();

                    if(allPieces[x-1][y-1]->getName() == "king"){
                        std::cout << "Fim de jogo. O último jogador venceu!!!" << std::endl;
                        std::exit(EXIT_SUCCESS);
                    }

                    delete (allPieces[x-1][y-1]);

                    piece->setX(x);
                    piece->setY(y);
                    this->allPieces[x-1][y-1] = piece;
                    this->allPieces[xAnt-1][yAnt-1] = nullptr;
                }
                else {
                    std::cout << "Movimento inválido\n";
                    return false;
                }
            }
            else {
                std::cout << "Posição ocupada\n";
                return false;
            }
        }
        else {
            std::cout << "Movimento inválido\n";
            return false;
        }
    }
    else {
        std::cout << "Coordenadas inválidas\n";
        return false;
    }
    return true;
}

bool Field::kingInCheck(std::string color){
    int xKing, yKing;
    //getting king position
    for(int i=POS_MIN-1; i<POS_MAX; i++){
        for(int j=POS_MIN-1; j<POS_MAX; j++){
            if(isOccupied(i+1, j+1)){
      	        if(allPieces[i][j]->getName()=="king" && allPieces[i][j]->getColor()==color){
                    xKing = allPieces[i][j]->getX();
                    yKing = allPieces[i][j]->getY();
                }
            }
          
        }
    }
    

    //Checking Pawn
    if(allPieces[xKing-1][yKing-1]->getColor() == "White"){
        if(isOccupied(xKing+1, yKing+1)){
            if(isOccupiedByEnemy(xKing+1, yKing+1, color) && (allPieces[xKing+1-1][yKing+1-1]->getName() == "pawn"))
                return true;
        }else{
            if(isOccupied(xKing+1, yKing-1)){
                if(isOccupiedByEnemy(xKing+1, yKing-1, color) && (allPieces[xKing+1-1][yKing-1-1]->getName() == "pawn"))
                    return true;
            }
        }
	}else{
        if(isOccupied(xKing-1, yKing-1)){
            if(isOccupiedByEnemy(xKing-1, yKing-1, color) && (allPieces[xKing-1-1][yKing-1-1]->getName() == "pawn"))
                return true;
        }else{
            if(isOccupied(xKing-1, yKing+1)){
                if(isOccupiedByEnemy(xKing-1, yKing+1, color) && (allPieces[xKing-1-1][yKing+1-1]->getName() == "pawn"))
                    return true;
            }
        }
	}
	
    //Checking diagonals
    for(int i = 1; xKing-1+i<POS_MAX && yKing-1+i<POS_MAX; i++)
        if(isOccupied(xKing+i, yKing+i)){
            if(isOccupiedByEnemy(xKing+i, yKing+i, color) && (allPieces[xKing+i-1][yKing+i-1]->getName() == "queen" || allPieces[xKing+i-1][yKing+i-1]->getName() == "bishop"))
                return true;
            else break;
        }

    for(int i = 1; xKing-1-i>=POS_MIN-1 && yKing-1-i>=POS_MIN-1; i++){
        if(isOccupied(xKing-i, yKing-i)){
            if(isOccupiedByEnemy(xKing-i, yKing-i, color) && (allPieces[xKing-i-1][yKing-i-1]->getName() == "queen" || allPieces[xKing-i-1][yKing-i-1]->getName() == "bishop"))           
                return true;
            else break;
        }
    }

    for(int i = 1; xKing-1-i>POS_MIN-1 && yKing-1+i<POS_MAX; i++)
        if(isOccupied(xKing-i, yKing+i)){
            if(isOccupiedByEnemy(xKing-i, yKing+i, color) && (allPieces[xKing-i-1][yKing+i-1]->getName() == "queen" || allPieces[xKing-i-1][yKing+i-1]->getName() == "bishop"))
                return true;
            else break;
        }

    for(int i = 1; xKing-1+i<POS_MAX-1 && yKing-1-i>=POS_MIN-1; i++){
        if(isOccupied(xKing+i, yKing-i)){
            if(isOccupiedByEnemy(xKing+i, yKing-i, color) && (allPieces[xKing+i-1][yKing-i-1]->getName() == "queen" || allPieces[xKing+i-1][yKing-i-1]->getName() == "bishop"))
                return true;
            else break;
        }
    }
    
    // Checking colums
    for(int i=1; yKing-1-i>=POS_MIN-1; i++){
        if(isOccupied(xKing, yKing-i)){
            if(isOccupiedByEnemy(xKing, yKing-i,color) && (allPieces[xKing-1][yKing-i-1]->getName() == "queen" || allPieces[xKing-1][yKing-i-1]->getName() == "rook"))
                return true;
            else break;
        }
    }

    for(int i=1; yKing-1+i<POS_MAX-1; i++){
        if(isOccupied(xKing, yKing+i)){
            if(isOccupiedByEnemy(xKing, yKing+i, color) && (allPieces[xKing-1][yKing+i-1]->getName() == "queen" || allPieces[xKing-1][yKing+i-1]->getName() == "rook"))
                return true;
            else break;
        }
    }

    //Checking rows
    for(int i=1; xKing-1-i>=POS_MIN-1; i++){
        if(isOccupied(xKing-i, yKing)){
            if(isOccupiedByEnemy(xKing-i, yKing, color) && (allPieces[xKing-i-1][yKing-1]->getName() == "queen" || allPieces[xKing-i-1][yKing-1]->getName() == "rook"))
                return true;
            else break;
        }
    }

    for(int i=1; xKing-1+i<POS_MAX-1; i++){
        if(isOccupied(xKing+i, yKing)){
            if(isOccupiedByEnemy(xKing+i, yKing, color) && (allPieces[xKing+i-1][yKing-1]->getName() == "queen" || allPieces[xKing+i-1][yKing-1]->getName() == "rook"))
                return true;
            else break;
        }
    }

    //Checking knight positions
    if(xKing-L_BIG_LEG-1>=POS_MIN-1 && yKing-L_SMALL_LEG-1>=POS_MIN-1){
        if(isOccupied(xKing-L_BIG_LEG, yKing-L_SMALL_LEG)){
            if(isOccupiedByEnemy(xKing-L_BIG_LEG, yKing-L_SMALL_LEG, color) && allPieces[xKing-L_BIG_LEG-1][yKing-L_SMALL_LEG-1]->getName() == "knight")
                return true;
        }
    }   

    if(xKing-L_BIG_LEG-1>=POS_MIN-1 && yKing+L_SMALL_LEG-1>POS_MAX){
        if(isOccupied(xKing-L_BIG_LEG, yKing+L_SMALL_LEG)){
            if(isOccupiedByEnemy(xKing-L_BIG_LEG, yKing+L_SMALL_LEG, color) && allPieces[xKing-L_BIG_LEG-1][yKing+L_SMALL_LEG-1]->getName() == "knight")
                return true;
        }
    }

    if(xKing-L_BIG_LEG-1>=POS_MIN-1 && yKing-L_SMALL_LEG-1>=POS_MIN-1){
        if(isOccupied(xKing-L_BIG_LEG, yKing-L_SMALL_LEG)){        
            if(isOccupiedByEnemy(xKing-L_BIG_LEG, yKing-L_SMALL_LEG, color) && allPieces[xKing-L_BIG_LEG-1][yKing-L_SMALL_LEG-1]->getName() == "knight")
                return true;
        }
    }

    if(xKing+L_BIG_LEG-1<POS_MAX-1 && yKing+L_SMALL_LEG-1<POS_MAX-1){
        if(isOccupied(xKing+L_BIG_LEG, yKing-L_SMALL_LEG)){
            if(isOccupiedByEnemy(xKing+L_BIG_LEG, yKing+L_SMALL_LEG, color) && allPieces[xKing+L_BIG_LEG-1][yKing+L_SMALL_LEG-1]->getName() == "knight")
                return true;
        }
    }
    
    if(xKing-L_SMALL_LEG-1>=POS_MIN-1 && yKing-L_BIG_LEG-1>=POS_MIN-1){
        if(isOccupied(xKing-L_SMALL_LEG, yKing-L_BIG_LEG)){
            if(isOccupiedByEnemy(xKing-L_SMALL_LEG, yKing-L_BIG_LEG, color) && allPieces[xKing-L_SMALL_LEG-1][yKing-L_BIG_LEG-1]->getName() == "knight")
                return true;
        }
    }

    if(xKing-L_SMALL_LEG-1>=POS_MIN-1 && yKing+L_BIG_LEG-1>POS_MAX){
        if(isOccupied(xKing-L_SMALL_LEG, yKing+L_BIG_LEG)){
            if(isOccupiedByEnemy(xKing-L_SMALL_LEG, yKing+L_BIG_LEG, color) && allPieces[xKing-L_SMALL_LEG-1][yKing+L_BIG_LEG-1]->getName() == "knight")
                return true;
        }
    }

    if(xKing-L_SMALL_LEG-1<POS_MAX && yKing-L_BIG_LEG-1>=POS_MIN-1){
        if(isOccupied(xKing+L_SMALL_LEG, yKing-L_BIG_LEG)){
            if(isOccupiedByEnemy(xKing+L_SMALL_LEG, yKing-L_BIG_LEG, color) && allPieces[xKing+L_SMALL_LEG-1][yKing-L_BIG_LEG-1]->getName() == "knight")
                return true;
        }
    }

    if(xKing+L_SMALL_LEG-1<POS_MAX && yKing+L_BIG_LEG-1<POS_MAX){
        if(isOccupied(xKing+L_SMALL_LEG, yKing-L_BIG_LEG)){
            if(isOccupiedByEnemy(xKing+L_SMALL_LEG, yKing+L_BIG_LEG, color) && allPieces[xKing+L_SMALL_LEG-1][yKing+L_BIG_LEG-1]->getName() == "knight")
                return true;
        }
    }

    return false;

}

void Field::printField() {
    //  Peça               Unicode
    // Rei preto       ♔    u2654 
    // Rei branco      ♚    u265A
    // Rainha preta    ♕    u2655
    // Rainha branca   ♛    u265B
    // Torre preta     ♖    u2656
    // Torre branca    ♜    u265C
    // bispo preto     ♗    u2657
    // bispo branco    ♝    u265D
    // cavalo preto    ♘    u2658
    // cavalo branco   ♞    u265E
    // Peão preto      ♙    u2659
    // Peão branco     ♟    u265F
    // Espaço Vazio    .     u2022

    //setlocale(LC_CTYPE,"");
    //wchar_t a=L'\u265F'; // (peão branco)
    //wchar_t b=L'\u2659'; // (peão preto)
    //std::wcout << a << b << std::endl;

    std::cout << std::endl;

    
    for(int i = 7; i >= 0; i--){
        std::wcout << i+1 << " ";
        for(int j = 0; j < 8; j++){
            if((j+i)%2 == 0){
                if(!allPieces[i][j]){
                    std::cout << termcolor::reset << "  ";
                }else if (allPieces[i][j]->getName()=="king"){
                    if(allPieces[i][j]->getColor()=="White"){
                        std::cout << termcolor::reset << "\u265A ";
                    }else{
                        std::cout << termcolor::reset << "\u2654 ";
                    }
                } else if (allPieces[i][j]->getName()=="queen"){
                    if(allPieces[i][j]->getColor()=="White"){
                        std::cout << termcolor::reset << "\u265B ";
                    }else{
                        std::cout << termcolor::reset << "\u2655 ";
                    }
                } else if (allPieces[i][j]->getName()=="rook"){
                    if(allPieces[i][j]->getColor()=="White"){
                        std::cout << termcolor::reset << "\u265C ";
                    }else{
                        std::cout << termcolor::reset << "\u2656 ";
                    }
                } else if (allPieces[i][j]->getName()=="pawn"){
                    if(allPieces[i][j]->getColor()=="White"){
                        std::cout << termcolor::reset << "\u265F ";
                    }else{
                        std::cout << termcolor::reset << "\u2659 ";
                    }
                } else if (allPieces[i][j]->getName()=="knight"){
                    if(allPieces[i][j]->getColor()=="White"){
                        std::cout << termcolor::reset << "\u265E ";
                    }else{
                        std::cout << termcolor::reset << "\u2658 ";
                    }
                } else if (allPieces[i][j]->getName()=="bishop"){
                    if(allPieces[i][j]->getColor()=="White"){
                        std::cout << termcolor::reset << "\u265D ";
                    }else{
                        std::cout << termcolor::reset << "\u2657 ";
                    }
                }

            } else {
                if(!allPieces[i][j]){
                    std::cout << termcolor::on_red << "  ";
                }else if (allPieces[i][j]->getName()=="king"){
                    if(allPieces[i][j]->getColor()=="White"){
                        std::cout << termcolor::on_red << "\u265A ";
                    }else{
                        std::cout << termcolor::on_red << "\u2654 ";
                    }
                } else if (allPieces[i][j]->getName()=="queen"){
                    if(allPieces[i][j]->getColor()=="White"){
                        std::cout << termcolor::on_red << "\u265B ";
                    }else{
                        std::cout << termcolor::on_red << "\u2655 ";
                    }
                } else if (allPieces[i][j]->getName()=="rook"){
                    if(allPieces[i][j]->getColor()=="White"){
                        std::cout << termcolor::on_red << "\u265C ";
                    }else{
                        std::cout << termcolor::on_red << "\u2656 ";
                    }
                } else if (allPieces[i][j]->getName()=="pawn"){
                    if(allPieces[i][j]->getColor()=="White"){
                        std::cout << termcolor::on_red << "\u265F ";
                    }else{
                        std::cout << termcolor::on_red << "\u2659 ";
                    }
                } else if (allPieces[i][j]->getName()=="knight"){
                    if(allPieces[i][j]->getColor()=="White"){
                        std::cout << termcolor::on_red << "\u265E ";
                    }else{
                        std::cout << termcolor::on_red << "\u2658 ";
                    }
                } else if (allPieces[i][j]->getName()=="bishop"){
                    if(allPieces[i][j]->getColor()=="White"){
                        std::cout << termcolor::on_red << "\u265D ";
                    }else{
                        std::cout << termcolor::on_red << "\u2657 ";
                    }
                }
            }
        }
        std::cout << termcolor::reset << "\n";
    }
    std::cout << termcolor::reset << "  A B C D E F G H \n\n";
    
}
