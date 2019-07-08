#include "../third_party/doctest.h"
#include "../include/rook.h"

TEST_CASE("Teste 1: Testando o Construtor"){
    CHECK_NOTHROW(Rook(1, 1, "Branca"));
}

TEST_CASE("Teste 2: Testando Movimento na Horizontal"){
    Rook r(4, 4, "Branca");
    CHECK(r.movimentValidator(4, 2));   //movimento válido
    CHECK(r.movimentValidator(4, 6));   //movimento válido
    CHECK(r.movimentValidator(4, 1));   //movimento válido
    CHECK(r.movimentValidator(4, 8));   //movimento válido
}

TEST_CASE("Teste 3: Testando Movimento na Vertical"){
    Rook r(4, 4, "Branca");
    CHECK(r.movimentValidator(2, 4));   //movimento válido
    CHECK(r.movimentValidator(6, 4));   //movimento válido
    CHECK(r.movimentValidator(1, 4));   //movimento válido
    CHECK(r.movimentValidator(8, 4));   //movimento válido
}


TEST_CASE("Teste 4: Testando Movimentos Inválidos"){
    Rook r(4, 4, "Branca");
    CHECK(!r.movimentValidator(5, 5));  //movimento inválido - diagonal
    CHECK(!r.movimentValidator(3, 3));  //movimento inválido - diagonal
    CHECK(!r.movimentValidator(5, 8));  //movimento inválido - fora da linha horizontal
    CHECK(!r.movimentValidator(8, 3));  //movimento inválido - fora da linha vertical
    CHECK(!r.movimentValidator(4, 4));  //movimento inválido - parado
}

TEST_CASE("Teste 5: Testando Nome e Cor"){
    Rook r(4, 5, "Preta");
    CHECK(r.getName() == "rook");
    CHECK(r.getColor() == "Preta");

    Rook r2(5, 4, "Branca");
    CHECK(r2.getName() == "rook");
    CHECK(r2.getColor() == "Branca");
}