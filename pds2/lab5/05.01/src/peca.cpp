#include "../include/peca.h"
#include <iostream>

Peca::Peca(int x, int y, std::string color) {
    this->x = x;
    this->y = y;
    this->color = color;
}

int Peca::getX(){
    return this->x;
}

void Peca::setX(int x){
    this->x = x;
}

int Peca::getY(){
    return this->y;
}

void Peca::setY(int y){
    this->y = y;
}

std::string Peca::getColor(){
    return this->color;
}
