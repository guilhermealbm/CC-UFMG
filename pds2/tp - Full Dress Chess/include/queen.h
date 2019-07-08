#ifndef QUEEN_H
#define QUEEN_H

#include "pieces.h"
#include <iostream>
#include <string>

class Queen : public Pieces {
public:

    Queen(int x, int y, std::string color);
    virtual ~Queen();
    virtual std::string getName();
    virtual bool movimentValidator(int x, int y);


};

#endif
