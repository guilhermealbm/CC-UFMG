#include "overnightpackage.h"

OverNightPackage::OverNightPackage(unsigned int peso, unsigned int custo, unsigned int taxa_por_kg, std::string nome, std::string endereco) : Package(peso, custo, nome, endereco){
  this->_taxa_por_kg = taxa_por_kg;
}

double OverNightPackage::calculate_cost(){
  return (this->_peso * (this->_custo + this->_taxa_por_kg));
}

OverNightPackage::~OverNightPackage(){

}
