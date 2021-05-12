#ifndef FORNO_H
#define FORNO_H

#include <pthread.h>
#include <vector>
#include <string>

class Forno {
    private:
        static Forno* instance;
        Forno();
        pthread_mutex_t lock;
        pthread_mutex_t fila_lock;
        std::vector<std::string> fila_de_espera;
        bool deadlock;

    public:
        static Forno* getInstance();
        void esperar(std::string personagem);
        void liberar(std::string personagem);
        void verificar();
        void insereFila(std::string personagem);
        void stuartKripke(std::string personagem);
};

#endif