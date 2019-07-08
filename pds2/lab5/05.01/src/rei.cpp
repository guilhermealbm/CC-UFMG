#include "../include/rei.h"

Rei::Rei(int x, int y, std::string color) : Peca(x, y, color) {}

Rei::~Rei() {}

std::string Rei::getName() {
    return "Rei";
}

bool Rei::movimentValidator(int x, int y) {
    //horizontal check --- vertical check
    if(!(this->getX() == x && this->getY() == y))
        if((abs(this->getX() - x) <= MOVE && abs(this->getY() - y) <= MOVE))
            return true;
    return false;
}
