#ifndef PDS2_TWODAYPACKAGE_H
#define PDS2_TWODAYPACKAGE_H

#include "package.h"

//#include <string>

class TwoDayPackage : public Package{
private:
  unsigned int _taxa_fixa;
public:
  TwoDayPackage(unsigned int peso, unsigned int custo, unsigned int taxa_fixa, std::string nome, std::string endereco);
  virtual double calculate_cost() override;

  ~TwoDayPackage();

};

#endif
