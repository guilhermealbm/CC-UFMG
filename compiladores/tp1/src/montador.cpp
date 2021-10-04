#include <sstream>
#include <iostream>

#include "montador.h"

Montador::Montador(std::string file_name) : file_name(file_name), ILC(0), pre_loads(0) { }

int Montador::decodifica_instrucao(std::string instrucao) {
    if (instrucao == "HALT" || instrucao == "R0") return 0;
    else if (instrucao == "LOAD" || instrucao == "R1") return 1;
    else if (instrucao == "STORE" || instrucao == "R2") return 2;
    else if (instrucao == "READ" || instrucao == "R3") return 3;
    else if (instrucao == "WRITE") return 4;
    else if (instrucao == "COPY") return 5;
    else if (instrucao == "PUSH") return 6;
    else if (instrucao == "POP") return 7;
    else if (instrucao == "ADD") return 8;
    else if (instrucao == "SUB") return 9;
    else if (instrucao == "MUL") return 10;
    else if (instrucao == "DIV") return 11;
    else if (instrucao == "MOD") return 12;
    else if (instrucao == "AND") return 13;
    else if (instrucao == "OR") return 14;
    else if (instrucao == "NOT") return 15;
    else if (instrucao == "JUMP") return 16;
    else if (instrucao == "JZ") return 17;
    else if (instrucao == "JN") return 18;
    else if (instrucao == "CALL") return 19;
    else if (instrucao == "RET") return 20;
    else return -1;
}

int Montador::tamanho_instrucao(std::string instrucao) {
    if (instrucao == "HALT") return 1;
    else if (instrucao == "LOAD") return 3;
    else if (instrucao == "STORE") return 3;
    else if (instrucao == "READ") return 2;
    else if (instrucao == "WRITE") return 2;
    else if (instrucao == "COPY") return 3;
    else if (instrucao == "PUSH") return 2;
    else if (instrucao == "POP") return 2;
    else if (instrucao == "ADD") return 3;
    else if (instrucao == "SUB") return 3;
    else if (instrucao == "MUL") return 3;
    else if (instrucao == "DIV") return 3;
    else if (instrucao == "MOD") return 3;
    else if (instrucao == "AND") return 3;
    else if (instrucao == "OR") return 3;
    else if (instrucao == "NOT") return 2;
    else if (instrucao == "JUMP") return 2;
    else if (instrucao == "JZ") return 2;
    else if (instrucao == "JN") return 2;
    else if (instrucao == "CALL") return 2;
    else if (instrucao == "RET") return 1;
    else if (instrucao == "WORD") return 1;
    else return 0;
}

void Montador::primeira_passagem() {
    std::string line;
    std::ifstream file_stream;
    std::ofstream temp_file;
    bool load_occurred = false;

    file_stream.open(this->file_name);
    temp_file.open("temp.txt");

    while (std::getline(file_stream, line)){
        if (line[0] == ';' || line == "") continue;
        
        std::string token;
        std::stringstream ss(line);

        while(ss >> token) {
            if (token[token.length() - 1] == ':') {
                std::string label = token.substr(0, token.length() - 1);

                this->labels[label] = this->ILC;
            } else {
                if (token[0] == ';' || token == "END") break;

                temp_file << token << " ";

                ILC += this->tamanho_instrucao(token);
                
                // calculating pre loads (WORDs before program start)
                if (token == "WORD" && (ILC == 1 || load_occurred)) {
                    pre_loads ++;
                    load_occurred = true;
                    ss >> token;
                    temp_file << token << " ";
                } else {
                    load_occurred = false;
                }
                
            }
        }
        if (token == "END") break;
        temp_file << std::endl;
    }
    temp_file.close();
    file_stream.close();
}

void Montador::segunda_passagem() {
    std::string token;
    std::ifstream temp_file;
    int n = 100;

    temp_file.open("temp.txt");

    std::cout << "MV-EXE\n" << std::endl;
    std::cout << this->ILC << " " << n <<  " " <<  this->ILC + n + 1000 << " " << n+pre_loads << "\n" << std::endl;

    this->ILC = 0;

    while (temp_file >> token) {
        int value = decodifica_instrucao(token);

        if (value >= 0){
            std::cout << value << " ";
            ILC ++;
        } else {
            if (token != "WORD") {
                try {
                    int integer_value = std::stoi(token);
                    std::cout << integer_value << " ";
                    
                } catch (const std::exception &e) {
                    if (this->labels.find(token) != this->labels.end()) {
                        int label_ILC = this->labels[token];
                        std::cout << (label_ILC - (ILC + 1)) << " ";
                    }
                }
                ILC ++;
            }
        }
    }
    std::cout << std::endl;


    temp_file.close();
}