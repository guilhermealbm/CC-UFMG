#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include "forno.h"

//S -> H -> L -> S
//Stuart sempre depois dos três
//Kripke sempre último
//Quem estiver em casal, tem preferência

struct personagem_data {
    std::string nome;
    int execucoes;
};

pthread_mutex_t print_lock;

void *raj_thread(void *data) {
    Forno *forno = Forno::getInstance();
    while(true) {
        // intervalo de verificação
        sleep(5);

        pthread_mutex_lock(&print_lock);
        forno->verificar();
        pthread_mutex_unlock(&print_lock);
    }
    return NULL;
}

void *personagem_thread(void *data) {
    struct personagem_data *p_data = (struct personagem_data *)data;
    std::string nome = p_data->nome;
    int execucoes = p_data->execucoes;

    Forno *forno = Forno::getInstance();

    // tempo aleatório de 0 a 3 segundos antes de entrar na fila do microondas
    sleep(rand() % 4);
    for (int i = 0; i < execucoes; i++) {
        pthread_mutex_lock(&print_lock);
        std::cout << nome << " quer usar o forno" << std::endl;
        pthread_mutex_unlock(&print_lock);
        forno->esperar(nome);
        
        // esquentar algo
        pthread_mutex_lock(&print_lock);
        std::cout << nome << " começa a esquentar algo" << std::endl;
        pthread_mutex_unlock(&print_lock);
        sleep(1);

        forno->liberar(nome);

        // tempos aleatórios entre 3 e 6 segundos para as outras tarefas
        pthread_mutex_lock(&print_lock);
        std::cout << nome << " vai comer" << std::endl;
        pthread_mutex_unlock(&print_lock);
        sleep((rand() % 4) + 3);   // comer

        pthread_mutex_lock(&print_lock);
        std::cout << nome << " voltou para o trabalho" << std::endl;
        pthread_mutex_unlock(&print_lock);
        sleep((rand() % 4) + 3);   //trabalho
    }

    delete p_data;
    return NULL;
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cout << "Número de parâmetros incorretos." << std::endl;
        return 1;
    }

    /* inicializando a semente random */
    srand (time(NULL));

    int thread_count = 8;
    pthread_t* thread_handles = new pthread_t[thread_count];
    pthread_t raj_thread_id;

    std::string nomes[thread_count] = {"Kripke", "Amy", "Bernadette", "Stuart", "Penny", "Howard", "Sheldon", "Leonard"};

    if (pthread_mutex_init(&print_lock, NULL) != 0) {
        std::cout << "mutex init falhou" << std::endl;
        exit(1);
    }
    
    for (int i = 0; i < thread_count; i++) {
        struct personagem_data *data = new personagem_data;
        data->nome = nomes[i];
        data->execucoes = atoi(argv[1]);
        pthread_create(&thread_handles[i], NULL, personagem_thread, data);
        usleep(1000);
    }
    pthread_create(&raj_thread_id, NULL, raj_thread, NULL);

    for (int i = 0; i < thread_count; i++) {
        pthread_join(thread_handles[i], NULL);
    }
    pthread_cancel(raj_thread_id);
    pthread_join(raj_thread_id, NULL);
    
    delete[] thread_handles;
    pthread_mutex_destroy(&print_lock);

    return 0;
}
