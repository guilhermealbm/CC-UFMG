#include "esfera.h"
#include <math.h>

Esfera::Esfera(std::string cor, double raio){
  this->_cor = cor;
  this->_nome = "esfera";
  this->_raio = raio;
}

std::string Esfera::get_cor(){
  return this->_cor;
}

std::string Esfera::get_nome(){
  return this->_nome;
}

double Esfera::get_volume(){
  return ((4 * M_PI * this->_raio * this->_raio * this->_raio)/3);
}
