#ifndef PDS2_QUADRADO_H
#define PDS2_QUADRADO_H
#include "forma2d.h"

class Quadrado : public Forma2D {
private:
  double _base;
public:
  Quadrado(std::string cor, double base);
  virtual std::string get_cor();
  virtual std::string get_nome();
  virtual double get_area();
  virtual double get_perimetro();
};

#endif
