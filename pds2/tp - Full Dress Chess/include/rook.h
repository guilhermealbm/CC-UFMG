#ifndef ROOK_H
#define ROOK_H

#include "pieces.h"
#include <iostream>
#include <string>

class Rook : public Pieces {
public:

    Rook(int x, int y, std::string color);
    virtual ~Rook();
    virtual std::string getName();
    virtual bool movimentValidator(int x, int y);

};

#endif
