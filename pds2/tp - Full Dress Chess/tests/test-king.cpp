#include "../third_party/doctest.h"
#include "../include/king.h"

TEST_CASE("Teste 1: Testando o Construtor"){
    CHECK_NOTHROW(King(1, 1, "Branca"));
}

TEST_CASE("Teste 2: Testando Movimento na Vertical"){
    King k(4, 4, "Branca");
    CHECK(k.movimentValidator(5, 4));   //movimento válido
    CHECK(k.movimentValidator(3, 4));   //movimento válido
}

TEST_CASE("Teste 3: Testando Movimento na Horizontal"){
    King k(4, 4, "Branca");
    CHECK(k.movimentValidator(4, 5));   //movimento válido
    CHECK(k.movimentValidator(4, 3));   //movimento válido
}


TEST_CASE("Teste 4: Testando Movimento na Diagonal"){
    King k(4, 4, "Branca");
    CHECK(k.movimentValidator(5, 5));   //movimento válido
    CHECK(k.movimentValidator(5, 3));   //movimento válido
    CHECK(k.movimentValidator(3, 5));   //movimento válido
    CHECK(k.movimentValidator(3, 3));   //movimento válido
}

TEST_CASE("Teste 5: Testando Movimentos Inválidos"){
    King k(4, 4, "Branca");
    CHECK(!k.movimentValidator(2, 4));   //movimento inválido - distância > 1
    CHECK(!k.movimentValidator(4, 2));   //movimento inválido - distância > 1
    CHECK(!k.movimentValidator(2, 2));   //movimento inválido - distânciaDiagonal > 1
    CHECK(!k.movimentValidator(6, 6));   //movimento inválido - distânciaDiagonal > 1
    CHECK(!k.movimentValidator(5, 6));   //movimento inválido - fora da diagonal
    CHECK(!k.movimentValidator(4, 4));   //movimento inválido - parado
}

TEST_CASE("Teste 6: Testando Nome e Cor"){
    King k(4, 5, "Preta");
    CHECK(k.getName() == "king");
    CHECK(k.getColor() == "Preta");

    King k2(5, 4, "Branca");
    CHECK(k2.getName() == "king");
    CHECK(k2.getColor() == "Branca");
}