#include "../include/bishop.h"

Bishop::Bishop(int x, int y, std::string color) : Pieces(x, y, color) {}

Bishop::~Bishop() {}

std::string Bishop::getName() {
    return "bishop";
}

bool Bishop::movimentValidator(int x, int y) {
    //diagonal check
    if(!(this->getX() == x && this->getY() == y))
        if(abs(this->getX()-x) == abs(this->getY()-y))
            return true;
    return false;
}
