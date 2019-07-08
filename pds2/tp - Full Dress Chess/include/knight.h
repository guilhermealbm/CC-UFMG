#ifndef KNIGHT_H
#define KNIGHT_H

#include "pieces.h"
#include <iostream>
#include <string>

#define L_SMALL_LEG 1
#define L_BIG_LEG 2

class Knight : public Pieces {
public:

    Knight(int x, int y, std::string color);
    virtual ~Knight();
    virtual std::string getName();
    virtual bool movimentValidator(int x, int y);


};

#endif
