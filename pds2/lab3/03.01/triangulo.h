#ifndef PDS2_TRIANGULO_H
#define PDS2_TRIANGULO_H

#include <math.h>
#include <iostream>

#include "forma2d.h"

class Triangulo : public Forma2D {
private:
  int _aresta_1;
  int _aresta_2;
  int _aresta_3;
public:
  Triangulo(std::string cor, int vertice_1, int vertice_2, int vertice_3);
  virtual std::string get_cor();
  virtual std::string get_nome();
  virtual double get_area();
  virtual double get_perimetro();
};

#endif
