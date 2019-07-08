#ifndef PDS2_OVERNIGHTPACKAGE_H
#define PDS2_OVERNIGHTPACKAGE_H

#include "package.h"

//#include <string>

class OverNightPackage : public Package{
private:
  unsigned int _taxa_por_kg;
public:
  OverNightPackage(unsigned int peso, unsigned int custo, unsigned int taxa_por_kg, std::string nome, std::string endereco);
  virtual double calculate_cost() override;

  ~OverNightPackage();

};

#endif
