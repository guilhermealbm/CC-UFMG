#ifndef PDS2_FORMA_2D_H
#define PDS2_FORMA_2D_H

#include <iostream>

#include "forma.h"

class Forma2D : public Forma {
public:
  virtual double get_area() = 0;
  virtual double get_perimetro() = 0;
};

#endif
