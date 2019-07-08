#ifndef PDS2_BISPO_H
#define PDS2_BISPO_H

#include "peca.h"
#include <iostream>
#include <string>

class Bispo : public Peca {
public:

    Bispo(int x, int y, std::string color);

    virtual ~Bispo();
    virtual std::string getName();
    virtual bool movimentValidator(int x, int y);

};

#endif
