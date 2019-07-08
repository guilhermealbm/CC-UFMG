#include "../include/knight.h"

Knight::Knight(int x, int y, std::string color) : Pieces(x, y, color) {}

Knight::~Knight() {}

std::string Knight::getName() {
    return "knight";
}

bool Knight::movimentValidator(int x, int y) {
    //L-movement check
    if((abs(x - this->getX()) == L_BIG_LEG && abs(y - this->getY()) == L_SMALL_LEG) || (abs(x - this->getX()) == L_SMALL_LEG && abs(y - this->getY()) == L_BIG_LEG))
        return true;
    return false;
}
