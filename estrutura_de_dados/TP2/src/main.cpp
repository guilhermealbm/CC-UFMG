#include "geraVetor.h"
#include <iostream>
#include "quicksort.h"
#include <cstdlib>
#include <chrono>

//Faz a impressão de um vetor passado como argumento
void imprimeVetor(int* vetor, int n){
    for (int i = 0; i < n; i++)
        std::cout << vetor[i] << " ";
    std::cout << std::endl;
}

//Executa os testes exigidos
void executa(int n, std::string tipoAlgoritmo, std::string tipoVetor, bool toPrint){
    int nTests = 20; //Numero de testes
    int times_[20]; //Vetor para armazenar os tempos
    int* copiaVetores[20]; //Armazena cópia dos vetores originais caso necessário (parametro -p)

    long int totalComparisons = 0, totalMoviments = 0;

    for (int i = 0; i < nTests; i++){
        int vetor[n];
        stats resultado;

        //Pega o horário do sistema antes da execução do código (em ms)
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        if (tipoVetor == "Ale")
            GeraVetor::aleatorio(vetor, n);
        else if (tipoVetor == "OrdC")
            GeraVetor::crescente(vetor, n);
        else
            GeraVetor::decrescente(vetor, n);

        if(toPrint)
            copiaVetores[i] = GeraVetor::clonaVetor(vetor, n);

        if(tipoAlgoritmo == "QC") resultado = QuickSort::classico(0, n-1, vetor, CLASSICO);
        else if(tipoAlgoritmo == "QM3") resultado = QuickSort::classico(0, n-1, vetor, MEDIANA_DE_TRES);
        else if(tipoAlgoritmo == "QPE") resultado = QuickSort::classico(0, n-1, vetor, PRIMEIRO_ELEMENTO);
        else if(tipoAlgoritmo == "QI1") resultado = QuickSort::insercao(vetor, 0, n-1, ((n*1)/100));
        else if(tipoAlgoritmo == "QI5") resultado = QuickSort::insercao(vetor, 0, n-1, ((n*5)/100));
        else if(tipoAlgoritmo == "QI10") resultado = QuickSort::insercao(vetor, 0, n-1, ((n*10)/100));
        else resultado = QuickSort::naoRecursivo(vetor, n);

        //Pega o horário do sistema depois da execução do código (em ms)
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        //Obtem a diferença entre os horários de início e término da execução (em ms)
        std::chrono::duration<double, std::micro> elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

        times_[i] = elapsed_time.count();

        totalComparisons += resultado.comparisons;
        totalMoviments += resultado.moviments;

    }

    //Ordena os tempos utilizando o algoritmo com o melhor desempenho segundo testes.
    QuickSort::classico(0, 20, times_, CLASSICO);
    int medianTime = times_[10];

    //Imprime a saída conforme especificado no enunciado
    std::cout << tipoAlgoritmo  << " " 
    << tipoVetor << " " 
    << n << " " 
    << (totalComparisons / 20) << " " 
    << (totalMoviments / 20) << " " 
    << medianTime << std::endl;

    //Imprime os vetores se necessário
    if (toPrint) {
        for (int i = 0; i < nTests; i++){
            imprimeVetor(copiaVetores[i], n); 
            delete[] copiaVetores[i];
        }
    }
    
}

int main(int argc, char *argv[]){

    srand(time(NULL)); //Gerando números aleatórios diferentes a cada execução do programa.

    if(argc < 4){ //Verifica quantidade de argumentos passados por CLI
        std::cerr << "Número de argumentos inválidos." << std::endl;
        return 1;
    }

    //Leitura das variaveis por CLI
    int n = atoi(argv[3]);
    std::string tipoVetor = std::string(argv[2]);
    std::string tipoAlgoritmo = std::string(argv[1]);
    bool toPrint = (argc == 5 && std::string(argv[4]) == "-p");

    executa(n, tipoAlgoritmo, tipoVetor, toPrint);

    return 0;
}