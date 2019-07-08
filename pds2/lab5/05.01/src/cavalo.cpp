#include "../include/cavalo.h"

Cavalo::Cavalo(int x, int y, std::string color) : Peca(x, y, color) {}

Cavalo::~Cavalo() {}

std::string Cavalo::getName() {
    return "Cavalo";
}

bool Cavalo::movimentValidator(int x, int y) {
    //L-movement check
    if((abs(x - this->getX()) == L_BIG_LEG && abs(y - this->getY()) == L_SMALL_LEG) || (abs(x - this->getX()) == L_SMALL_LEG && abs(y - this->getY()) == L_BIG_LEG))
        return true;
    return false;
}
