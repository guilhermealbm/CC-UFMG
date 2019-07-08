#include "quadrado.h"

Quadrado::Quadrado(std::string cor, double base){
  this->_cor = cor;
  this->_nome = "quadrado";
  this->_base = base;
}

std::string Quadrado::get_cor(){
  return this->_cor;
}

std::string Quadrado::get_nome(){
  return this->_nome;
}

double Quadrado::get_area(){
  return (this->_base * this->_base);
}

double Quadrado::get_perimetro(){
  return (4* this->_base);
}
