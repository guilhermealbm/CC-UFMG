#include "lista.h"
#include <iostream>

Lista::Lista(){ //Faz lista vazia
    this->primeira = nullptr;
    this->ultima = nullptr;
}

bool Lista::vazia(){ //Checa se a lista está vazia
    return (this->primeira == nullptr && this->ultima == nullptr);
}
//Insere os alunos com a nota de forma decrescente
void Lista::insere(Aluno aluno){

    celula* no = new celula;
    no->aluno = aluno;
    no->proximo = nullptr;

    //Insere o primeiro elemento da lista
    if (vazia()){
        this->primeira = no;
        this->ultima = no;
        return;
    }

    //insere o elemento no inicio
    if(this->primeira->aluno.nota < aluno.nota){
        no->proximo = this->primeira;
        this->primeira = no;
        return;
    }

    celula *elementoAtual = this->primeira;
    celula* aux = nullptr;
    while(elementoAtual->aluno.nota > aluno.nota && elementoAtual->proximo != nullptr){
        aux = elementoAtual;
        elementoAtual = elementoAtual->proximo;
    }

    //Insere um elemento no meio da lista (antes do elemento atual)
    if(elementoAtual->aluno.nota < aluno.nota){
        no->proximo = elementoAtual;
        aux->proximo = no;
        return;
    }

    //Insere o ultimo elemento da lista
    this->ultima->proximo = no;
    this->ultima = no;
    return;
}

int Lista::busca(Aluno aluno){
    
    if(this->vazia()){
        return -1;
    }
    int i = 0;
    celula *elementoAtual = this->primeira;
    while(elementoAtual->aluno.nome != aluno.nome){
        i++;
        if(elementoAtual->proximo != nullptr){
            elementoAtual = elementoAtual->proximo;
        }else if(elementoAtual->aluno.nome != aluno.nome){
        //Chegou ao fim da lista e o elemento não foi encontrado
            return -1;
        }
    }

    return i;
}

void Lista::imprimeNomes(int vagas){
    int i = 0;
    if(this->vazia()){
        std::cout << "Classificados" << std::endl;
        std::cout << "Lista de espera" << std::endl << std::endl;
        return;
    }
    celula *elementoAtual = this->primeira;
    std::cout << "Classificados" << std::endl;
    while(elementoAtual->proximo != nullptr){
        std::cout << elementoAtual->aluno.nome << " "<<elementoAtual->aluno.nota << std::endl;
        elementoAtual = elementoAtual->proximo;
        i++;
        if(i == vagas){
            std::cout << "Lista de espera" << std::endl;
        }
    }

    std::cout << elementoAtual->aluno.nome << " "<< elementoAtual->aluno.nota << std::endl;

    //Imprime a string "Lista de espera" mesmo que não existam mais alunos na lista
    if(i < vagas){
        std::cout << "Lista de espera" << std::endl << std::endl;
    }else{
        std::cout << std::endl;
    }
}

void Lista::insereCursos(Curso *cursos, int ncursos){
    celula *elementoAtual = this->primeira;
    while(elementoAtual->proximo != nullptr){
            
        //Resolvendo o problema do empate
        if(elementoAtual->aluno.nota == elementoAtual->proximo->aluno.nota){
            celula* inicioEmpate = elementoAtual;
            
            while (inicioEmpate->aluno.nota == elementoAtual->aluno.nota){
                if(!elementoAtual->aluno.selecionado1){
                    elementoAtual->aluno.selecionado1 = true;
                    cursos[elementoAtual->aluno.opcao1].alunos.insere(elementoAtual->aluno);
                }
                if(elementoAtual->proximo != nullptr){
                    elementoAtual = elementoAtual->proximo;
                }else{
                    //Fim da lista
                    break;
                }
            }
            
            elementoAtual = inicioEmpate;
        
        }else if(!elementoAtual->aluno.selecionado1){
            elementoAtual->aluno.selecionado1 = true;
            cursos[elementoAtual->aluno.opcao1].alunos.insere(elementoAtual->aluno);
        }
        
        if(!elementoAtual->aluno.selecionado2){
            elementoAtual->aluno.selecionado2 = true;
            cursos[elementoAtual->aluno.opcao2].alunos.insere(elementoAtual->aluno);
        }
        
        elementoAtual = elementoAtual->proximo;

    }

    if(!elementoAtual->aluno.selecionado1){
        elementoAtual->aluno.selecionado1 = true;
        cursos[elementoAtual->aluno.opcao1].alunos.insere(elementoAtual->aluno);
    }
    
    if(!elementoAtual->aluno.selecionado2){
        elementoAtual->aluno.selecionado2 = true;
        cursos[elementoAtual->aluno.opcao2].alunos.insere(elementoAtual->aluno);
    }
    
}

void Lista::deleta(Aluno aluno){
    celula *elementoAtual = this->primeira;
    celula* aux = elementoAtual;
    while(elementoAtual->proximo != nullptr){
        if(elementoAtual->aluno.nome == aluno.nome){
            if(elementoAtual == this->primeira){
                this->primeira = this->primeira->proximo;
            }else{
                aux->proximo = elementoAtual->proximo;
            }
            delete elementoAtual;
        }
        aux = elementoAtual;
        elementoAtual = elementoAtual->proximo;
    }
    
    //deleta o 1 elemento de uma lista com 1 elemento.
    if (elementoAtual->aluno.nome == aluno.nome && elementoAtual == this->primeira && this->primeira == this->ultima){
        this->primeira = nullptr;
        this->ultima = nullptr;
        delete elementoAtual;
        return;
    }

    if (elementoAtual->aluno.nome == aluno.nome && elementoAtual == this->primeira && this->primeira != this->ultima){
        this->primeira = this->primeira->proximo;
        delete elementoAtual;
        return;
    }

    if(elementoAtual->aluno.nome == aluno.nome){
        aux->proximo = elementoAtual->proximo;
        delete elementoAtual;
    }  

}

void Lista::removeClassificados(Curso *cursos){
    celula *elementoAtual = this->primeira;
    int opcao1 = elementoAtual->aluno.opcao1;
    while(elementoAtual->proximo != nullptr){
        //Verifica se está selecionado na opção 1 e deleta na opcao 2
        if(cursos[opcao1].alunos.busca(elementoAtual->aluno) < cursos[opcao1].nVagas && elementoAtual->aluno.selecionado1){
            elementoAtual->aluno.selecionado1 = false;
            cursos[elementoAtual->aluno.opcao2].alunos.deleta(elementoAtual->aluno);
        }

        
        elementoAtual = elementoAtual->proximo;
        opcao1 = elementoAtual->aluno.opcao1;
    }

    if(cursos[opcao1].alunos.busca(elementoAtual->aluno) < cursos[opcao1].nVagas && elementoAtual->aluno.selecionado1){
        elementoAtual->aluno.selecionado1 = false;
        cursos[elementoAtual->aluno.opcao2].alunos.deleta(elementoAtual->aluno);
    }


}

double Lista::buscaCorte(int nVagas){
    if(this->vazia()){
        return 0;
    }
    celula *elementoAtual = this->primeira;
    //Existe curso com nota de corte 0?
    for (int i = 0; i < nVagas-1; i++){
        if(elementoAtual->proximo != nullptr){
            elementoAtual = elementoAtual->proximo;
        }else{
            return 0;
        }
    }

    return elementoAtual->aluno.nota;
    
}

Lista::~Lista(){
    if(this->vazia()){
        return;
    }

    celula *elementoAtual = this->primeira;
    celula *apaga = this->primeira;

    while (elementoAtual->proximo != nullptr){
        apaga = elementoAtual;
        elementoAtual = elementoAtual->proximo;
        delete apaga;
    }

    delete elementoAtual;    
}