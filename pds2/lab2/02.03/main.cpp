#include <iostream>

#include "listaencadeada.h"

int main(){
    std::cout << "Use o main para testar seu código" << std::endl;

    ListaEncadeada lista; //chamando lista via construtor vazio
    lista.insere_elemento(4);
    lista.insere_elemento(7);
    lista.insere_elemento(3);
    lista.insere_elemento(9);
    lista.insere_elemento(6);
    lista.insere_elemento(8);
    lista.insere_elemento(5);
    lista.insere_elemento(1);

    return 0;
}
