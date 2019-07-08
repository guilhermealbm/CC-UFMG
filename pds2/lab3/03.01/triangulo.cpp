#include "triangulo.h"

Triangulo::Triangulo(std::string cor, int aresta_1, int aresta_2, int aresta_3){
  this->_cor = cor;
  this->_nome = "triangulo";
  this->_aresta_1 = aresta_1;
  this->_aresta_2 = aresta_2;
  this->_aresta_3 = aresta_3;
}

std::string Triangulo::get_cor(){
  return this->_cor;
}

std::string Triangulo::get_nome(){
  return this->_nome;
}

double Triangulo::get_area(){
  double p = ((this->_aresta_1 + this->_aresta_2 + this->_aresta_3));
  return (sqrt(p/2*((p/2-this->_aresta_1)*(p/2-this->_aresta_2)*(p/2-this->_aresta_3))));
}

double Triangulo::get_perimetro(){
  return (this->_aresta_1 + this->_aresta_2 + this->_aresta_3);
}
