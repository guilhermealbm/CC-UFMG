#include "../include/pieces.h"
#include <iostream>

Pieces::Pieces(int x, int y, std::string color) {
    this->x = x;
    this->y = y;
    this->color = color;
}

int Pieces::getX(){
    return this->x;
}

void Pieces::setX(int x){
    this->x = x;
}

int Pieces::getY(){
    return this->y;
}

void Pieces::setY(int y){
    this->y = y;
}

std::string Pieces::getColor(){
    return this->color;
}
