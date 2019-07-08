#include "../include/king.h"

King::King(int x, int y, std::string color) : Pieces(x, y, color) {}

King::~King() {}

std::string King::getName() {
    return "king";
}

bool King::movimentValidator(int x, int y) {
    //horizontal check --- vertical check
    if(!(this->getX() == x && this->getY() == y))
        if((abs(this->getX() - x) <= MOVE && abs(this->getY() - y) <= MOVE))
            return true;
    return false;
}
