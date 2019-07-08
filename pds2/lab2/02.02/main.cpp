#include <iostream>

#include "listaencadeada.h"

int main(){
    //std::cout << "Use o main para testar seu código" << std::endl;

    ListaEncadeada lista; //chamando lista via construtor vazio
    lista.insere_elemento(1);
    lista.insere_elemento(1);
    lista.insere_elemento(2);
    lista.insere_elemento(1);
    lista.insere_elemento(2);
    lista.insere_elemento(2);
    lista.insere_elemento(3);
    lista.insere_elemento(1);
    lista.insere_elemento(3);
    lista.insere_elemento(3);
    lista.insere_elemento(3);
    lista.insere_elemento(2);

    //lista.imprimir();

    lista.remove_consecutivos();

    //lista.imprimir();

    return 0;
}
