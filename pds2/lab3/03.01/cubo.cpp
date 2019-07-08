#include "cubo.h"

Cubo::Cubo(std::string cor, double base){
  this->_cor = cor;
  this->_nome = "cubo";
  this->_base = base;
}

std::string Cubo::get_cor(){
  return this->_cor;
}

std::string Cubo::get_nome(){
  return this->_nome;
}

double Cubo::get_volume(){
  return (this->_base * this->_base * this->_base);
}
