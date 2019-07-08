#ifndef PDS2_ESFERA_H
#define PDS2_ESFERA_H

#include "forma3d.h"

class Esfera : public Forma3D {
private:
  double _raio;
public:
  Esfera(std::string cor, double raio);
  virtual std::string get_cor();
  virtual std::string get_nome();
  virtual double  get_volume();
};

#endif
