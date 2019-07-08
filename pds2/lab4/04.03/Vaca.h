#ifndef VACA_H
#define VACA_H

#include <iostream>
#include "Animal.h"

class Vaca : public Animal {
    private:
        float _producao_leite;
    public:
        Vaca(std::string cor,float producao_leite);
        ~Vaca(){}
        virtual Animal* reproduz() override;
        virtual void faz_barulho() override;
        virtual unsigned int get_id() override;
};


#endif