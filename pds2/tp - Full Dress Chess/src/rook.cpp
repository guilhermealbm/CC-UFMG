#include "../include/rook.h"

Rook::Rook(int x, int y, std::string color) : Pieces(x, y, color) {}

Rook::~Rook() {}

std::string Rook::getName() {
    return "rook";
}

bool Rook::movimentValidator(int x, int y) {
    //horizontal check --- vertical check
    if(!(this->getX() == x && this->getY() == y))
        if(this->getX() == x || this->getY() == y)
            return true;
    return false;
}
