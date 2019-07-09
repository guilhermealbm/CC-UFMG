#ifndef LISTA_H
#define LISTA_H

#include <string>

struct Aluno{
    std::string nome;
    double nota;
    int opcao1;
    int opcao2;
    bool selecionado1;
    bool selecionado2;
};

struct celula{
    Aluno aluno;
    celula *proximo;
};

struct Curso;

class Lista{
    private:
        celula *primeira;
        celula *ultima;
    public:
        Lista(); //Faz lista vazia
        ~Lista();
        bool vazia();
        void insere(Aluno aluno); //Insere os alunos com a nota de forma decrescente
        int busca(Aluno aluno);
        void imprimeNomes(int vagas);
        void insereCursos(Curso *curso, int nCursos);
        void deleta(Aluno aluno);
        void removeClassificados(Curso *cursos);
        double buscaCorte(int nVagas);

};

struct Curso{
    std::string nome;
    int nVagas;
    Lista alunos;
};

#endif