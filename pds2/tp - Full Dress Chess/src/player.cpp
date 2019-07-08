#include "../include/player.h"
#include <iostream>

Player::Player(std::string name, std::string color, Field &field) {
    this->name = name;
    this->color = color;
    this->field = &field;
}

std::string Player::getName() {
    return this->name;
}

std::string Player::getColor() {
    return this->color;
}
bool Player::makeMove(int pieceX, int pieceY, int nextX, int nextY) {
    Pieces* piece = this->field->getPiece(pieceX, pieceY);
    if(piece == nullptr){
        std::cout << "Posição vazia\n";
        return false;
    }
    else if(piece->getColor() != this->color){
        std::cout << "Peça selecionada não é da sua cor.\n";
        return false;
    }
    else{
        return this->field->move(piece, nextX, nextY);
    }
}