#include "lista.h"
#include <iostream>
#include <string>
#include <iomanip>

Lista* sisu(){

    int numCursos, numAlunos;
    std::cin >> numCursos >> numAlunos;

    Curso cursos[numCursos];

    for(int i = 0; i < numCursos; i++){
        std::string nomeCurso;
        std::cin.ignore(); //"Pula linha do inteiro anterior"
        std::getline (std::cin,nomeCurso);

        int numVagas;
        std::cin >> numVagas;

        //std::cout << "Inserindo o curso: " << nomeCurso << std::endl;
        cursos[i] = {nomeCurso, numVagas};

    }

    Lista *alunos = new Lista();

    for(int i = 0; i < numAlunos; i++){
        std::string nomeAluno;
        std::cin.ignore(); //"Pula linha do inteiro anterior"
        std::getline (std::cin,nomeAluno);
        double nota;
        int op1, op2;

        std::cin >> nota >> op1 >> op2;

        Aluno aluno = {nomeAluno, nota, op1, op2, false, false};
        alunos->insere(aluno);

    }

    alunos->insereCursos(cursos, numCursos);
    alunos->removeClassificados(cursos);


    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    for (int i = 0; i < numCursos; i++){
        std::cout << cursos[i].nome << " " << cursos[i].alunos.buscaCorte(cursos[i].nVagas) << std::endl;
        cursos[i].alunos.imprimeNomes(cursos[i].nVagas);
    }

    return alunos;
    
}

int main(){

    Lista* alunos = sisu();
    
    delete alunos;
    
}