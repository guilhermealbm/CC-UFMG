#include <iostream>
#include "BST.h"
#include "node.h"
#include "listaencadeada.h"

int main(){
    std::cout << "Use o main para testar seu código" << std::endl;

    BST arvore = BST();
    arvore.inserir_elemento(7); 
    arvore.inserir_elemento(3);
    arvore.inserir_elemento(2);
    arvore.inserir_elemento(5);       
    arvore.inserir_elemento(4);
    arvore.inserir_elemento(6);
    
    ListaEncadeada L_pre=arvore.pre_ordem();
    
    std::cout << L_pre.get_iesimo(0) << '\n';
    std::cout << L_pre.get_iesimo(1) << '\n';
    std::cout << L_pre.get_iesimo(2) << '\n';
    std::cout << L_pre.get_iesimo(3) << '\n';
    std::cout << L_pre.get_iesimo(4) << '\n';
    std::cout << L_pre.get_iesimo(5) << '\n';

    return 0;
}
