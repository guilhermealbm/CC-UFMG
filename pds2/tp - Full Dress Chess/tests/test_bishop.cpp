#include "../third_party/doctest.h"
#include "../include/bishop.h"

TEST_CASE("Teste 1: Testando o Construtor"){
    CHECK_NOTHROW(Bishop(1, 1, "Branca"));
}

TEST_CASE("Teste 2: Testando Movimentos Válidos"){
    Bishop b(4, 4, "Branca");
    CHECK(b.movimentValidator(1, 1));   //movimento válido
    CHECK(b.movimentValidator(6, 2));   //movimento válido
    CHECK(b.movimentValidator(3, 3));   //movimento válido
    CHECK(b.movimentValidator(2, 6));   //movimento válido
    CHECK(b.movimentValidator(8, 8));   //movimento válido
}

TEST_CASE("Teste 3: Testando Movimentos Inválidos"){
    Bishop b(4, 4, "Branca");
    CHECK(!b.movimentValidator(1, 2));  //movimento inválido - fora da diagonal
    CHECK(!b.movimentValidator(5, 4));  //movimento inválido - movimento vertical
    CHECK(!b.movimentValidator(2, 3));  //movimento inválido - fora da diagonal
    CHECK(!b.movimentValidator(4, 2));  //movimento inválido - movimento horizontal
    CHECK(!b.movimentValidator(4, 4));  //movimento inválido - parado
}

TEST_CASE("Teste 4: Testando Nome e Cor"){
    Bishop b(4, 5, "Preta");
    CHECK(b.getName() == "bishop");
    CHECK(b.getColor() == "Preta");

    Bishop b2(5, 4, "Branca");
    CHECK(b2.getName() == "bishop");
    CHECK(b2.getColor() == "Branca");
}