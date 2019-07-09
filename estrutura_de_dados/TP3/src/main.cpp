#include <iostream>
#include <fstream>
#include "BTree.h"
#include "node.h"

void receives_file_input(BTree &trie){
    std::ifstream myReadFile;
    myReadFile.open("morse.txt"); //Abre o arquivo com o código morse de cada caractere na raiz da pasta contendo o main.
    std::string morse_code, letter;
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) { //Itera até encontrar o fim do arquivo de texto. Gera duas subtrings utilizando o espaço em branco " " para divisão.
            myReadFile >> letter; //Coloca a primeira substring contendo o caractere a ser inserido na árvore.
            myReadFile >> morse_code; //Coloca a segunda substring contendo o código referente ao caractere atual.
            Cell cell = {morse_code, letter[0]};
            trie.insert_cell(cell);
        }
    }
    myReadFile.close();
}

void decode_message(BTree &trie){
    std::string line;
    //https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    std::string delimiter = " "; //Delimita as letras da entrada.
    std::string word_delimiter = "/"; //Delimita as palavras da entrada.
    while (std::getline(std::cin, line)) { //Itera até chegar ao fim da entrada

        size_t pos = 0;
        std::string token;
        while ((pos = line.find(delimiter)) != std::string::npos) { //Itera até que não exista mais nenhum espaço em branco
            token = line.substr(0, pos); //Gera a substring da primeira posição até o delimitador de letra " "
            if(token == word_delimiter)
                std::cout << " ";
            else
                std::cout << trie.find_cell(token);
            line.erase(0, pos + delimiter.length()); //Exclui a parte da linha lida já inserida na trie.
        }
        if(line != "") //Garante que não acontece uma falha de segmentação se a frase terminar com um espaço em branco " "
            std::cout << trie.find_cell(line) << std::endl;
    }
}

int main(int argc, char *argv[]){

    BTree newTrie = BTree();
    receives_file_input(newTrie);
    decode_message(newTrie);
    if(argc == 2 && std::string(argv[1]) == "-a") //Parametro de execução para a impressão da árvore de maneira pré ordenada.
        newTrie.printPreorder();

    return 0;
}
