#include "../third_party/doctest.h"
#include "../include/rei.h"

TEST_CASE("Teste 1: Testando o Construtor"){
    CHECK_NOTHROW(Rei(1, 1, "Branca"));
}

TEST_CASE("Teste 2: Testando Movimento na Vertical"){
    Rei k(4, 4, "Branca");
    CHECK(k.movimentValidator(5, 4));   //movimento válido
    CHECK(k.getName() == "Rei");
    CHECK(k.movimentValidator(3, 4));   //movimento válido
}

TEST_CASE("Teste 3: Testando Movimento na Horizontal"){
    Rei k(4, 4, "Branca");
    CHECK(k.movimentValidator(4, 5));   //movimento válido
    CHECK(k.movimentValidator(4, 3));   //movimento válido
}


TEST_CASE("Teste 4: Testando Movimento na Diagonal"){
    Rei k(4, 4, "Branca");
    CHECK(k.movimentValidator(5, 5));   //movimento válido
    CHECK(k.movimentValidator(5, 3));   //movimento válido
    CHECK(k.movimentValidator(3, 5));   //movimento válido
    CHECK(k.movimentValidator(3, 3));   //movimento válido
}

TEST_CASE("Teste 5: Testando Movimentos Inválidos"){
    Rei k(4, 4, "Branca");
    CHECK(!k.movimentValidator(2, 4));   //movimento inválido - distância > 1
    CHECK(!k.movimentValidator(4, 2));   //movimento inválido - distância > 1
    CHECK(!k.movimentValidator(2, 2));   //movimento inválido - distânciaDiagonal > 1
    CHECK(!k.movimentValidator(6, 6));   //movimento inválido - distânciaDiagonal > 1
    CHECK(!k.movimentValidator(5, 6));   //movimento inválido - fora da diagonal
    CHECK(!k.movimentValidator(4, 4));   //movimento inválido - parado
}
