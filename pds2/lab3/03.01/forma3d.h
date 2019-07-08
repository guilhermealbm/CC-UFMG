#ifndef PDS2_FORMA_3D_H
#define PDS2_FORMA_3D_H

#include <iostream>

#include "forma.h"

class Forma3D : public Forma {
public:
  virtual double  get_volume() = 0;
};

#endif
