#include "ligador.h"

#include <sstream>
#include <fstream>
#include <iostream>

Ligador::Ligador(std::vector<std::string> files) 
    : files(files), total_size(0), dynamic_counter(0), main_file_name("") {}

void Ligador::pega_informacoes_principais(std::string file_name) {
    std::string line;
    std::ifstream file_stream;
    std::string number;

    file_stream.open(file_name);

    file_stream >> number;
    this->total_size += stoi(number);

    while (this->main_file_name == "" && std::getline(file_stream, line)) {
        std::string token;
        std::stringstream ss(line);

        ss >> token;
        if (token == "main") {
            this->main_file_name = file_name;
            break;
        }
    }

    file_stream.close();
}

void Ligador::escreve_arquivo(std::string file_name) {
    std::string line;
    std::ifstream file_stream;
    std::ofstream temp_file;
    std::string number;

    file_stream.open(file_name);
    temp_file.open("temp_ligador.txt", std::ios::out | std::ios::app);

    file_stream >> number;
    for (int i = 0; i < 2; i++)
        std::getline(file_stream, line);

    std::getline(file_stream, line);
    temp_file << line;

    while (std::getline(file_stream, line)){
        std::string token;
        std::stringstream ss(line);

        if (ss >> token) {
            std::string num;
            ss >> num;

            this->labels[token] = stoi(num) + this->dynamic_counter;
        }
    }
    this->dynamic_counter += stoi(number);

    file_stream.close();
    temp_file.close();
}

void Ligador::passagem_um() {
    for (auto it = this->files.begin(); it != this->files.end(); it++) {
        this->pega_informacoes_principais(*it);
    }

    // cria arquivo temporário ou apaga dados do arquivo criado anteriomente
    std::ofstream temp_file;
    temp_file.open("temp_ligador.txt", std::ios::out);
    temp_file.close();

    for (auto it = this->files.begin(); it != this->files.end(); it++) {
        if (*it != this->main_file_name)
            this->escreve_arquivo(*it);
    }
    this->escreve_arquivo(this->main_file_name);
}

void Ligador::passagem_dois() {
    // cria arquivo temporário ou apaga dados do arquivo criado anteriomente
    std::ifstream temp_file;
    std::string token; 

    temp_file.open("temp_ligador.txt");
    
    int ILC = 0;
    int n = 100;

    std::cout << "MV-EXE\n" << std::endl;

    std::cout << this->total_size << " " << n <<  " " <<  this->total_size + n + 1000 << " " << n + this->labels["main"] << "\n" << std::endl;

    while (temp_file >> token) {
        try {
            int integer_value = std::stoi(token);
            std::cout << integer_value << " ";
            
        } catch (const std::exception &e) {
            if (this->labels.find(token) != this->labels.end()) {
                int label_ILC = this->labels[token];
                std::cout << (label_ILC - (ILC + 1)) << " ";
            } else {
                std::cout << token << " ";
            }
        }
        ILC ++;
    }
    std::cout << std::endl;
    
    temp_file.close();
}