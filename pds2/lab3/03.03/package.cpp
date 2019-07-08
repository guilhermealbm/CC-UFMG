#include "package.h"

Package::Package(unsigned int peso, unsigned int custo, std::string nome, std::string endereco){
  this->_peso = peso;
  this->_custo = custo;
  this->_nome = nome;
  this->_endereco = endereco;
}

double Package::calculate_cost(){
  return (this->_peso * this->_custo);
}

unsigned int Package::get_peso(){
    return this->_peso;
}

int Package::get_custo_por_quilo(){
    return this->_custo;
}

std::string Package::get_nome(){
  return this->_nome;
}

Package::~Package(){

}
