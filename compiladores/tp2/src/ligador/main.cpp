#include <iostream>
#include <fstream>

#include "ligador.h"

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
    }

    std::vector<std::string> files;
    for (int i = 1; i < argc; i++) {
        if (check_file(argv[i])) {
            std::cerr << "Erro: arquivo fonte inválido!\n";
            return 1;
        }
        files.push_back(argv[i]);
    }

    Ligador l(files);
    l.passagem_um();
    l.passagem_dois();

    return 0;
}
