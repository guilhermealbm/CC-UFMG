#ifndef PDS2_ROOK_H
#define PDS2_ROOK_H

#include "peca.h"
#include <iostream>
#include <string>

class Torre : public Peca {
public:

    Torre(int x, int y, std::string color);

    virtual ~Torre();
    virtual std::string getName();
    virtual bool movimentValidator(int x, int y);

};

#endif
