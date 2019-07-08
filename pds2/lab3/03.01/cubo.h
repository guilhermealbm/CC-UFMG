#ifndef PDS2_CUBO_H
#define PDS2_CUBO_H

#include "forma3d.h"

class Cubo : public Forma3D {
private:
  double _base;
public:
  Cubo(std::string cor, double base);
  virtual std::string get_cor();
  virtual std::string get_nome();
  virtual double  get_volume();
};

#endif
