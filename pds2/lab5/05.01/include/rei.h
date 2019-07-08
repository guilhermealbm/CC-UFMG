#ifndef PDS2_REI_H
#define PDS2_REI_H

#include "peca.h"
#include <iostream>
#include <string>

#define MOVE 1

class Rei : public Peca {
public:

    Rei(int x, int y, std::string color);

    virtual ~Rei();
    virtual std::string getName();
    virtual bool movimentValidator(int x, int y);

};

#endif
