#include "../include/queen.h"

Queen::Queen(int x, int y, std::string color) : Pieces(x, y, color) {}

Queen::~Queen() {}

std::string Queen::getName() {
    return "queen";
}

bool Queen::movimentValidator(int x, int y) {
    //horizontal check --- vertical check -- diagonal check
    if(!(this->getX() == x && this->getY() == y))
        if((this->getX() == x || this->getY() == y) || (abs(this->getX()-x) == abs(this->getY()-y)))
            return true;
    return false;
}
