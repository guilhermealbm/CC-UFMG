#ifndef PDS2_FORMA_H
#define PDS2_FORMA_H

#include <string>

class Forma{
public:
  std::string _cor;
  std::string _nome;
  virtual std::string get_cor() = 0;
  virtual std::string get_nome() = 0;
};

#endif
