#include <iomanip>
#include <iostream>
#include <sstream>
#include <map>


int main() {
  std::cout << std::fixed;
  std::cout << std::setprecision(2);

  std::string linha;
  std::string palavra;
  double totalPalavras = 0;
  std::map<std::string, int> contagem;
  while (std::getline(std::cin, linha)) {
    std::istringstream linha_stream(linha);
    while (std::getline(linha_stream, palavra, ' ')) {
      totalPalavras++;
      if (contagem.count(palavra) == 0) { // 0 se não existe; 1 cc.
        contagem[palavra] = 0;
      }
      contagem[palavra] += 1;
    }
  }

  for (std::pair<std::string, int> pair : contagem) {
    std::cout << pair.first << " " << pair.second << " " << (pair.second/totalPalavras);
    std::cout << std::endl;
  }

  return 0;
}
