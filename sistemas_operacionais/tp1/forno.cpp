#include "forno.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <unistd.h>

Forno* Forno::instance = 0;

// criando uma instância singleton do Forno
Forno* Forno::getInstance() {
    if (instance == 0) {
        instance = new Forno();
    }
    return instance;
}

Forno::Forno() {
    if (pthread_mutex_init(&lock, NULL) != 0 || pthread_mutex_init(&fila_lock, NULL)) {
        std::cout << "mutex init falhou" << std::endl;
        exit(1);
    }
    deadlock = false;
}


void Forno::esperar(std::string personagem) {   
    // reorganiza a fila de acordo com o novo personagem que chegar
    pthread_mutex_lock(&fila_lock);
    insereFila(personagem);
    pthread_mutex_unlock(&fila_lock);

    std::string topo_fila;
    pthread_mutex_lock(&fila_lock);
    topo_fila = fila_de_espera.front();
    pthread_mutex_unlock(&fila_lock);
    while(personagem.compare(topo_fila) != 0 || deadlock){
        pthread_mutex_lock(&fila_lock);
        topo_fila = fila_de_espera.front();
        pthread_mutex_unlock(&fila_lock);
    }


    pthread_mutex_lock(&lock);
}

void Forno::liberar(std::string personagem) {
    while (deadlock);

    pthread_mutex_lock(&fila_lock);
    std::vector<std::string>::iterator pos = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), personagem);
    fila_de_espera.erase(pos);
    pthread_mutex_unlock(&fila_lock);

    pthread_mutex_unlock(&lock);
}

void Forno::verificar() {
    if (deadlock) {
        std::vector<std::string> personagens = {"Sheldon", "Amy", "Howard", "Bernadette", "Leonard", "Penny"};
        std::vector<std::string> personagens_fila;

        // descobre personagens que podem causar deadlock que estão na fila
        for (size_t i = 0; i < personagens.size(); i++) {
            if (std::find(std::begin(fila_de_espera), std::end(fila_de_espera), personagens[i]) != std::end(fila_de_espera)) {
                personagens_fila.push_back(personagens[i]);
            }
        }

        // escolhe aleatoriamente um dos personagens da fila
        int indice = rand() % personagens_fila.size();
        std::string personagem_sorteado = personagens_fila[indice];
        std::string companheiro;

        std::vector<std::string> casais;

        // pega o nome do companheiro do personagem selecionado
        if (personagem_sorteado.compare("Sheldon") == 0 || personagem_sorteado.compare("Amy") == 0) {
            companheiro = (personagem_sorteado.compare("Sheldon") == 0) ? "Amy" : "Sheldon";
            casais = {"Howard", "Bernadette", "Leonard", "Penny"};
        } else if (personagem_sorteado.compare("Howard") == 0 || personagem_sorteado.compare("Bernadette") == 0) {
            companheiro = (personagem_sorteado.compare("Howard") == 0) ? "Bernadette" : "Howard";
            casais = {"Leonard", "Penny", "Sheldon", "Amy"};
        } else  {
            companheiro = (personagem_sorteado.compare("Leonard") == 0) ? "Penny" : "Leonard";
            casais = {"Sheldon", "Amy", "Howard", "Bernadette"};
        }

        //Num deadlock, ou todos estão em casais, ou ninguém está em casal. Se entrar no if abaixo, todos os seis personagens estão na lista
        // se o companheiro também está na fila. Temos que mover ambos
        std::vector<std::string>::iterator companheiro_pos = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), companheiro);
        std::vector<std::string>::iterator tempIterator;
        if (companheiro_pos != std::end(fila_de_espera)) {
            fila_de_espera.erase(companheiro_pos);

            std::vector<std::string>::iterator personagem_pos = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), personagem_sorteado);
            fila_de_espera.erase(personagem_pos);

            std::vector<std::string>::iterator membro1_casal1 = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), casais[0]);
            fila_de_espera.erase(membro1_casal1);

            std::vector<std::string>::iterator membro2_casal1 = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), casais[1]);
            fila_de_espera.erase(membro2_casal1);

            std::vector<std::string>::iterator membro1_casal2 = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), casais[2]);
            fila_de_espera.erase(membro1_casal2);

            std::vector<std::string>::iterator membro2_casal2 = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), casais[3]);
            fila_de_espera.erase(membro2_casal2);
            
            fila_de_espera.insert(std::begin(fila_de_espera) + 1, companheiro);
            tempIterator = fila_de_espera.insert(std::begin(fila_de_espera) + 1, personagem_sorteado);

            if(membro1_casal1 > membro2_casal1) {
                fila_de_espera.insert(tempIterator + 2, casais[1]);
                fila_de_espera.insert(tempIterator + 3, casais[0]);
            } else {
                fila_de_espera.insert(tempIterator + 2, casais[0]);
                fila_de_espera.insert(tempIterator + 3, casais[1]);
            }

            if(membro1_casal2 > membro2_casal2) {
                fila_de_espera.insert(tempIterator + 4, casais[3]);
                fila_de_espera.insert(tempIterator + 5, casais[2]);
            } else {
                fila_de_espera.insert(tempIterator + 4, casais[2]);
                fila_de_espera.insert(tempIterator + 5, casais[3]);
            }

        } else { // caso contrário, basta mover só o personagem
            std::vector<std::string>::iterator personagem_pos = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), personagem_sorteado);
            fila_de_espera.erase(personagem_pos);
            tempIterator = fila_de_espera.insert(std::begin(fila_de_espera) + 1, personagem_sorteado);
            std::string proximo_personagem = fila_de_espera[std::distance(fila_de_espera.begin(), tempIterator + 1)];
            //Se a ordem estiver incorreta (e ninguém estiver em casal)
            if (proximo_personagem.compare(casais[0]) != 0 && proximo_personagem.compare(casais[1]) != 0) {
                std::vector<std::string>::iterator proximo_personagem_pos = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), proximo_personagem);
                //Apaga o próximo personagem, que será o último dos três
                fila_de_espera.erase(proximo_personagem_pos);
                //Passa o último dos três para a segunda posição
                //Insere o personagem, previamente na segunda posição, na terceira posição
                fila_de_espera.insert(proximo_personagem_pos + 1, proximo_personagem);

            }
        }
        std::cout << "Raj detectou um deadlock, liberando " << personagem_sorteado << std::endl;
        deadlock = false;
    }
}

void Forno::insereFila(std::string personagem) {
    if (personagem.compare("Stuart") == 0) {
        std::vector<std::string>::iterator kripke_pos = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), "Kripke");
        if (kripke_pos != std::end(fila_de_espera)) {
            if (kripke_pos != std::begin(fila_de_espera)) {
                fila_de_espera.insert(kripke_pos, personagem);
            } else {
                fila_de_espera.push_back(personagem);
            }
        } else
            fila_de_espera.push_back(personagem);
    } else if (personagem.compare("Kripke") == 0) {
        fila_de_espera.push_back(personagem);
    } else {
        std::string companheiro;
        std::vector<std::string> casais;
        //S -> H -> L -> S
        if (personagem.compare("Sheldon") == 0 || personagem.compare("Amy") == 0) {
            companheiro = (personagem.compare("Sheldon") == 0) ? "Amy" : "Sheldon";
            casais = {"Howard", "Bernadette", "Leonard", "Penny"};
        } else if (personagem.compare("Howard") == 0 || personagem.compare("Bernadette") == 0) {
            companheiro = (personagem.compare("Howard") == 0) ? "Bernadette" : "Howard";
            casais = {"Leonard", "Penny", "Sheldon", "Amy"};
        } else { // Leonard/Penny
            companheiro = (personagem.compare("Leonard") == 0) ? "Penny" : "Leonard";
            casais = {"Sheldon", "Amy", "Howard", "Bernadette"};
        }

        std::vector<std::string>::iterator personagem_it = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), companheiro);

        std::vector<std::string>::iterator membro1_casal1 = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), casais[0]);
        std::vector<std::string>::iterator membro2_casal1 = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), casais[1]);
        std::vector<std::string>::iterator membro1_casal2 = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), casais[2]);
        std::vector<std::string>::iterator membro2_casal2 = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), casais[3]);

        bool casal1 = (membro1_casal1 != std::end(fila_de_espera)) && (membro2_casal1 != std::end(fila_de_espera));
        bool casal2 = (membro1_casal2 != std::end(fila_de_espera)) && (membro2_casal2 != std::end(fila_de_espera));

        // achou o companheiro na fila
        if (personagem_it != std::end(fila_de_espera)) {
            if (casal2 && casal1) {
                deadlock = true;
                //Se estiver em casal, entra logo atrás do namorado/a
                fila_de_espera.insert(personagem_it + 1, personagem);
            } else if (casal2) {
                std::vector<std::string>::iterator last_pos = std::max(membro1_casal2, membro2_casal2);
                // apaga posição antiga do companheiro
                fila_de_espera.erase(personagem_it);

                fila_de_espera.insert(last_pos + 1, companheiro);
                fila_de_espera.insert(last_pos + 2, personagem);
            } else if (casal1) {
                if (std::begin(fila_de_espera) == personagem_it) {
                    fila_de_espera.insert(std::begin(fila_de_espera) + 1, personagem);
                } else {
                    // apaga posição antiga do companheiro
                    fila_de_espera.erase(personagem_it);
                    fila_de_espera.insert(std::begin(fila_de_espera) + 1, personagem);
                    fila_de_espera.insert(std::begin(fila_de_espera) + 1, companheiro);
                }
            } else {

                if (std::begin(fila_de_espera) == personagem_it) {
                    fila_de_espera.insert(std::begin(fila_de_espera) + 1, personagem);
                } else {
                    // apaga posição antiga do companheiro
                    fila_de_espera.erase(personagem_it);
                    fila_de_espera.insert(std::begin(fila_de_espera) + 1, personagem);
                    fila_de_espera.insert(std::begin(fila_de_espera) + 1, companheiro);
                }

                deadlock = false;
            }
        } else {    // não achou o companheiro na fila
            if (casal2 && casal1) {
                std::vector<std::string>::iterator last_pos = std::max(membro1_casal2, membro2_casal2);

                fila_de_espera.insert(last_pos + 1, personagem);
            } else if (casal1) {
                std::vector<std::string>::iterator pos = (membro1_casal2 != std::end(fila_de_espera)) ? membro1_casal2 : membro2_casal2;

                if (pos != std::end(fila_de_espera)) {
                    fila_de_espera.insert(pos + 1, personagem);
                } else {
                    stuartKripke(personagem);
                }
            } else if (casal2) {
                std::vector<std::string>::iterator pos = (membro1_casal1 != std::end(fila_de_espera)) ? membro1_casal1 : membro2_casal1;

                if (pos != std::end(fila_de_espera)) {
                    fila_de_espera.insert(pos, personagem);
                } else {
                    stuartKripke(personagem);
                }
            } else {
                std::vector<std::string>::iterator pos_membro1_casal2 = (membro1_casal2 != std::end(fila_de_espera)) ? membro1_casal2 : membro2_casal2;
                std::vector<std::string>::iterator pos_membro1_casal1 = (membro1_casal1 != std::end(fila_de_espera)) ? membro1_casal1 : membro2_casal1;

                if (pos_membro1_casal2 != std::end(fila_de_espera) && pos_membro1_casal1 != std::end(fila_de_espera)) {
                    // só acontece deadlock se todos estiverem esperando na fila. Isso é, se ninguém está esquentando algo (ou seja, está na primeira posição da fila)
                    if (pos_membro1_casal1 == std::begin(fila_de_espera)) {
                        fila_de_espera.insert(pos_membro1_casal2 + 1, personagem);
                    } else if (pos_membro1_casal2 == std::begin(fila_de_espera)) {
                        fila_de_espera.insert(pos_membro1_casal1, personagem);
                    } else{
                        deadlock = true;
                        fila_de_espera.insert(pos_membro1_casal2 + 1, personagem);
                    }
                } else if (pos_membro1_casal2 != std::end(fila_de_espera)) {
                    fila_de_espera.insert(pos_membro1_casal2 + 1, personagem);
                } else if (pos_membro1_casal1 != std::end(fila_de_espera)) {
                    fila_de_espera.insert(pos_membro1_casal1, personagem);
                } else {
                    stuartKripke(personagem);
                }
            }
        }
    }
}


void Forno::stuartKripke(std::string personagem) {
    std::vector<std::string>::iterator pos = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), "Stuart");

    if (pos != std::end(fila_de_espera)) {
        if (pos != std::begin(fila_de_espera))
            fila_de_espera.insert(pos, personagem);
        else
            fila_de_espera.insert(pos + 1, personagem);
    } else {
        pos = std::find(std::begin(fila_de_espera), std::end(fila_de_espera), "Kripke");
        if (pos != std::end(fila_de_espera)) {
            if (pos != std::begin(fila_de_espera))
                fila_de_espera.insert(pos, personagem);
            else
                fila_de_espera.insert(pos + 1, personagem);
        }
        else {
            fila_de_espera.push_back(personagem);
        }
    }
}