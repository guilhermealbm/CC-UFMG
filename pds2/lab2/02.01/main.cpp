#include <iostream>

#include "listaencadeada.h"

int main(){
    std::cout << "Use o main para testar seu código" << std::endl;
    ListaEncadeada lista; //chamando lista via construtor vazio
    lista.insere_elemento(4);
    lista.insere_elemento(5);
    lista.insere_elemento(1);
    lista.insere_primeiro(8);
    
    int element = lista.get_iesimo(0);
    
    std::cout << element << std::endl;
    
    return 0;
}