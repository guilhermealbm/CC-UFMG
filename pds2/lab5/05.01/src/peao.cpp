#include "../include/peao.h"

Peao::Peao(int x, int y, std::string color, bool movementDirection) : Peca(x, y, color) {
    this->firstMovement = true;
    this->movementDirection = movementDirection;
}

Peao::~Peao() {}

std::string Peao::getName() {
    return "Peao";
}

bool Peao::movimentValidator(int x, int y) {

    if(this->movementDirection) {
        if(!(x > this->x)) {
            return false;
        }
    }
    else {
        if(!(x < this->x)) {
            return false;
        }
    }

    //vertical check
    if(this->firstMovement) {
        if((this->getY() == y) && (abs(this->getX() - x) <= FIRST_MOVE)) {
            this->firstMovement = false;
            return true;
        }
    }
    else {
        if((this->getY() == y) && (abs(this->getX() - x) == BASIC_MOVE)) {
            return true;
        }
    }
    return false;
}
