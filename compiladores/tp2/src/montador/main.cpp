#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

#include "montador.h"

int check_file(char *file_name) {
    std::ifstream f;

    f.open(file_name);
    if (!f.is_open()) return 1;

    f.close();
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Erro: comando inválido!\n"
                << "Uso: montador <path/to/file>\n";
    } else if (check_file(argv[1])) {
        std::cerr << "Erro: arquivo fonte inválido!\n";
        return 1;
    }

    Montador m(argv[1]);
    m.primeira_passagem();
    m.segunda_passagem();

    return 0;
}
