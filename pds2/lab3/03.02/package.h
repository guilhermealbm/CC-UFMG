#ifndef PDS2_PACKAGE_H
#define PDS2_PACKAGE_H

#include <string>

class Package{
protected:
  std::string _nome;
  std::string _endereco;
  unsigned int _peso;
  unsigned int _custo;

public:
  Package(unsigned int peso, unsigned int custo, std::string nome, std::string endereco);
  virtual double calculate_cost();
  unsigned int get_peso();
  int get_custo_por_quilo();

  virtual ~Package();

};

#endif
