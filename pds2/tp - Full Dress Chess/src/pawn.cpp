#include "../include/pawn.h"

Pawn::Pawn(int x, int y, std::string color, bool movementDirection) : Pieces(x, y, color) {
    this->firstMovement = true;
    this->movementDirection = movementDirection;
}

Pawn::~Pawn() {}

std::string Pawn::getName() {
    return "pawn";
}

bool Pawn::movimentValidator(int x, int y) {

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
