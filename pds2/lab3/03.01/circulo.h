#ifndef PDS2_CIRCULO_H
#define PDS2_CIRCULO_H

#include "forma2d.h"

class Circulo : public Forma2D {
private:
  double _raio;
public:
  Circulo(std::string cor, double raio);
  virtual std::string get_cor();
  virtual std::string get_nome();
  virtual double get_area();
  virtual double get_perimetro();
};

#endif
