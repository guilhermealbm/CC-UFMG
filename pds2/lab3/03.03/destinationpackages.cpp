#include "destinationpackages.h"

void DestinationPackages::add_package(Package *g){
  std::vector<Package*> vetor;
  std::string nome = g->get_nome();
  Package *ponteiro = g;

  vetor = this->mapa[nome];
  vetor.push_back(ponteiro);
  this->mapa[nome] = vetor;

  //this->_mapa.insert(std::make_pair(nome, &g));
}

double DestinationPackages::custo_total(){
  double custoTotal = 0.0;
  for (std::pair<std::string, std::vector<Package*>> pair : mapa) {
    for(auto indv_package : pair.second){
      custoTotal+= indv_package->calculate_cost();
    }
    // std::cout << pair.first << " " << pair.second << " " << (pair.second/totalPalavras);
    // std::cout << std::endl;
  }
  return custoTotal;
}

double DestinationPackages::custo_total(std::string nome){
  double custoTotal = 0.0;
  for (std::pair<std::string, std::vector<Package*>> pair : mapa) {
    if (pair.first == nome) {
      for(auto indv_package : pair.second){
        custoTotal+= indv_package->calculate_cost();
      }
    }
    // std::cout << pair.first << " " << pair.second << " " << (pair.second/totalPalavras);
    // std::cout << std::endl;
  }
  return custoTotal;
}
