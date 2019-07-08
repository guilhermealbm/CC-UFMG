#include "circulo.h"
#include <math.h>

Circulo::Circulo(std::string cor, double raio){
  this->_cor = cor;
  this->_nome = "circulo";
  this->_raio = raio;
}

std::string Circulo::get_cor(){
  return this->_cor;
}

std::string Circulo::get_nome(){
  return this->_nome;
}

double Circulo::get_area(){
  return (M_PI * this->_raio * this->_raio);
}

double Circulo::get_perimetro(){
  return (2* M_PI * this->_raio);
}
