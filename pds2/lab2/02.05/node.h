#ifndef PDS2_NODE_H
#define PDS2_NODE_H
#include "listaencadeada.h"

class Node {
private:
    Node *_esquerda;
    Node *_direita;
    int _elemento;
public:
    Node(int valor);
    ~Node();
    void inserir_elemento(int elemento);
    bool existe_elemento(int elemento);
    ListaEncadeada pre_ordem();
    void pre_ordem_aux(ListaEncadeada &lista);
    ListaEncadeada em_ordem();
    void em_ordem_aux(ListaEncadeada &lista);
    ListaEncadeada pos_ordem();
    void pos_ordem_aux(ListaEncadeada &lista);
};
#endif
