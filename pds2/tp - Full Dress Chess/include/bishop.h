#ifndef BISHOP_H
#define BISHOP_H

#include "pieces.h"
#include <iostream>
#include <string>

class Bishop : public Pieces {
public:

    Bishop(int x, int y, std::string color);
    virtual ~Bishop();
    virtual std::string getName();
    virtual bool movimentValidator(int x, int y);

};

#endif
