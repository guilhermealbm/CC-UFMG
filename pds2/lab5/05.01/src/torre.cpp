#include "../include/torre.h"

Torre::Torre(int x, int y, std::string color) : Peca(x, y, color) {}

Torre::~Torre() {}

std::string Torre::getName() {
    return "Torre";
}

bool Torre::movimentValidator(int x, int y) {
    //horizontal check --- vertical check
    if(!(this->getX() == x && this->getY() == y))
        if(this->getX() == x || this->getY() == y)
            return true;
    return false;
}
