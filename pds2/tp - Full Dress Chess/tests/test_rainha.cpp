#include "../third_party/doctest.h"
#include "../include/queen.h"

TEST_CASE("Teste 1: Testando o Construtor"){
    CHECK_NOTHROW(Queen(1, 1, "Branca"));
}

TEST_CASE("Teste 2: Testando Movimento na Vertical"){
    Queen q(1, 1, "Branca");
    CHECK(q.movimentValidator(2, 1));   //movimento válido
    CHECK(q.movimentValidator(8, 1));   //movimento válido
    CHECK(q.movimentValidator(5, 1));   //movimento válido
}

TEST_CASE("Teste 3: Testando Movimento na Horizontal"){
    Queen q(1, 1, "Branca");
    CHECK(q.movimentValidator(1, 2));   //movimento válido
    CHECK(q.movimentValidator(1, 5));   //movimento válido
    CHECK(q.movimentValidator(1, 8));   //movimento válido
}


TEST_CASE("Teste 4: Testando Movimento na Diagonal"){
    Queen q(4, 2, "Branca");
    CHECK(q.movimentValidator(3, 1));   //movimento válido
    CHECK(q.movimentValidator(5, 1));   //movimento válido
    CHECK(q.movimentValidator(8, 6));   //movimento válido
    CHECK(q.movimentValidator(2, 4));   //movimento válido
    CHECK(q.movimentValidator(5, 3));   //movimento válido
}

TEST_CASE("Teste 5: Testando Movimentos Inválidos"){
    Queen q(4, 2, "Branca");
    CHECK(!q.movimentValidator(1, 1));  //movimento inválido - fora de reta ou diagonal
    CHECK(!q.movimentValidator(8, 8));  //movimento inválido - fora de reta ou diagonal
    CHECK(!q.movimentValidator(6, 5));  //movimento inválido - fora de reta ou diagonal
    CHECK(!q.movimentValidator(2, 3));  //movimento inválido - fora de reta ou diagonal
    CHECK(!q.movimentValidator(4, 2));  //movimento inválido - parado
}

TEST_CASE("Teste 6: Testando Nome e Cor"){
    Queen q(4, 5, "Preta");
    CHECK(q.getName() == "queen");
    CHECK(q.getColor() == "Preta");

    Queen q2(5, 4, "Branca");
    CHECK(q2.getName() == "queen");
    CHECK(q2.getColor() == "Branca");
}
