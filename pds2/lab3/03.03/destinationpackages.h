#ifndef PDS2_DESINATIONPACKAGES_H
#define PDS2_DESTINATIONPACKAGES_H

#include <string>
#include <map>
#include <vector>

#include "package.h"

class DestinationPackages{
private:
  std::map<std::string, std::vector<Package*>> mapa;
public:
  void add_package(Package *g);
  double custo_total();
  double custo_total(std::string usuario);

};

#endif
