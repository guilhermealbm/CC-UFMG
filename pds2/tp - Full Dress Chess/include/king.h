#ifndef KING_H
#define KING_H

#include "pieces.h"
#include <iostream>
#include <string>

#define MOVE 1

class King : public Pieces {
public:

    King(int x, int y, std::string color);
    virtual ~King();
    virtual std::string getName();
    virtual bool movimentValidator(int x, int y);

};

#endif
