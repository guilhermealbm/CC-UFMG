#include "../include/bispo.h"

Bispo::Bispo(int x, int y, std::string color) : Peca(x, y, color) {}

Bispo::~Bispo() {}

std::string Bispo::getName() {
    return "Bispo";
}

bool Bispo::movimentValidator(int x, int y) {
    //diagonal check
    if(!(this->getX() == x && this->getY() == y))
        if(abs(this->getX()-this->getY()) == abs(x-y))
            return true;
    return false;
}
