#ifndef QUICKSORT_H
#define QUICKSORT_H

//Enum usado para saber qual tipo de variação do quicksort executar.
enum TipoClassico{
    CLASSICO = 1,
    MEDIANA_DE_TRES = 2,
    PRIMEIRO_ELEMENTO = 3
};

//Struct para armazenas os dados de número de comparações e número de movimentações
struct stats{
    long int comparisons;
    long int moviments;

    //Sobrescreve o operador += para facilitar operações com a struct
    stats& operator+=(const stats& atual){
        comparisons += atual.comparisons;
        moviments += atual.moviments;
        return *this;
    }
};


class QuickSort{
private:
    //Impossibilita a criação de uma instância da classe. Por isso, é necessário que todos os métodos sejam estáticos.
    QuickSort(){};

public:
    //Particiona o array em duas metades, a depender do pivo x escolhido.
    static void particao(int left, int right,int *i, int *j, int* vetor, int x, stats& resultado);
    //Calcula a mediana de três números quaisquer. Utilizado no QuickSort com pivo mediana de tres.
    static int medianaDeTres(int first, int middle, int last, stats &resultado);

    //Executa a variação mais eficiente, para a maior parte dos casos, do algoritmo de ordenação QuickSort
    static stats classico(int left, int right, int* vetor, TipoClassico tipo);

    //Implementa o quicksort com inserção.
    static stats insercao(int* vetor, int left, int right, int cut);
    //Compara e insere os valores com base no insertion sort
    static void insere(int* vetor, int left, int right, stats &resultado);

    //Implementa a versão não recusriva do QuickSort. As chamadas recursivas são trocadas pela utilização da estrutura de dados Pilha (stack)
    static stats naoRecursivo(int* vetor, int n);
};

#endif