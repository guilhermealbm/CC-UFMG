#ifndef PAWN_H
#define PAWN_H

#include "pieces.h"
#include <iostream>
#include <string>

#define BASIC_MOVE 1
#define FIRST_MOVE 2

class Pawn : public Pieces{
private:
    bool firstMovement;
    
public:

    Pawn(int x, int y, std::string color, bool movementDirection);
    virtual ~Pawn();
    virtual std::string getName();
    virtual bool movimentValidator(int x, int y);

};

#endif
