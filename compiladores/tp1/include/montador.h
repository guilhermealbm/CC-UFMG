#ifndef MONTADOR_H
#define MONTADOR_H

#include <string>
#include <map>
#include <vector>
#include <fstream>

class Montador {
private:
    std::string file_name;
    std::map<std::string, int> labels;
    std::vector<int> instructions;
    int ILC;
    int pre_loads;

public:
    Montador(std::string file_name);
    int decodifica_instrucao(std::string instrucao);
    int tamanho_instrucao(std::string instrucao);
    void primeira_passagem();
    void segunda_passagem();
};

#endif
