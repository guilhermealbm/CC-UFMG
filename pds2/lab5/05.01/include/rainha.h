#ifndef PDS2_RAINHA_H
#define PDS2_RAINHA_H

#include "peca.h"

#include <iostream>
#include <string>

class Rainha : public Peca {
public:

    Rainha(int x, int y, std::string color);

    virtual ~Rainha();
    virtual std::string getName();
    virtual bool movimentValidator(int x, int y);


};

#endif