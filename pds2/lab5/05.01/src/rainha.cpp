#include "../include/rainha.h"

Rainha::Rainha(int x, int y, std::string color) : Peca(x, y, color) {}

Rainha::~Rainha() {}

std::string Rainha::getName() {
    return "Rainha";
}

bool Rainha::movimentValidator(int x, int y) {
    //horizontal check --- vertical check -- diagonal check
    if(!(this->getX() == x && this->getY() == y))
        if((this->getX() == x || this->getY() == y) || (abs(this->getX()-this->getY()) == abs(x-y)))
            return true;
    return false;
}
