#ifndef PDS2_PEAO_H
#define PDS2_PEAO_H

#include "peca.h"
#include <iostream>
#include <string>

#define BASIC_MOVE 1
#define FIRST_MOVE 2

class Peao : public Peca{
private:
    bool firstMovement;
    
public:

    Peao(int x, int y, std::string color, bool movementDirection);

    virtual ~Peao();
    virtual std::string getName();
    virtual bool movimentValidator(int x, int y);

};

#endif
