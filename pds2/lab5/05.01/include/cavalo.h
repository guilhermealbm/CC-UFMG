#ifndef PDS2_PEAO_H
#define PDS2_PEAO_H

#include "peca.h"

#include <iostream>
#include <string>

#define L_SMALL_LEG 1
#define L_BIG_LEG 2

class Cavalo : public Peca {
public:

    Cavalo(int x, int y, std::string color);

    virtual ~Cavalo();
    virtual std::string getName();
    virtual bool movimentValidator(int x, int y);


};

#endif
