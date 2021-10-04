#ifndef LIGADOR_H
#define LIGADOR_H

#include <string>
#include <vector>
#include <map>

class Ligador {
private:
    std::vector<std::string> files;
    int total_size;
    int dynamic_counter;
    std::string main_file_name;
    std::map<std::string, int> labels;

public:
    Ligador(std::vector<std::string> files);
    void pega_informacoes_principais(std::string file_name);
    void escreve_arquivo(std::string file_name);
    void passagem_um();
    void passagem_dois();
};

#endif
