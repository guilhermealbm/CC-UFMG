#include "triangulo.h"

Triangulo::Triangulo(double x, double y, double z){
    if(x >= y + z || y >= x + z || z >= x + y || x <= 0 || y <= 0 || z <= 0){
        throw TrianguloInvalidoException();
    }

    this->x = x;
    this->y = y;
    this->z = z;
}

Tipo Triangulo::determinar_tipo(){
    if(x == y && x == z){
        return EQUILATERO;
    }else if(x != y && x != z && y != z){
        return ESCALENO;
    }
    return ISOSCELES;
    
}