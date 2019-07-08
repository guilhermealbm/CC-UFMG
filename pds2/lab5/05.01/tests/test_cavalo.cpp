#include "../third_party/doctest.h"
#include "../include/cavalo.h"

TEST_CASE("Teste 1: Testando o Construtor"){
    CHECK_NOTHROW(Cavalo(1, 1, "Branca"));
}

TEST_CASE("Teste 2: Testando Movimentos Válidos"){
    Cavalo k(4, 4, "Branca");
    CHECK(k.movimentValidator(5, 6));   //movimento válido
    CHECK(k.getName() == "Cavalo");
    CHECK(k.movimentValidator(6, 5));   //movimento válido
    CHECK(k.movimentValidator(5, 2));   //movimento válido
    CHECK(k.movimentValidator(6, 3));   //movimento válido
    CHECK(k.movimentValidator(3, 6));   //movimento válido
    CHECK(k.movimentValidator(2, 5));   //movimento válido
    CHECK(k.movimentValidator(3, 2));   //movimento válido
    CHECK(k.movimentValidator(2, 3));   //movimento válido
}

TEST_CASE("Teste 3: Testando Movimentos Inválidos"){
    Cavalo k(4, 4, "Branca");
    CHECK(!k.movimentValidator(4, 5));  //movimento inválido - horizontal
    CHECK(!k.movimentValidator(5, 4));  //movimento inválido - vertical
    CHECK(!k.movimentValidator(5, 5));  //movimento inválido - diagonal
    CHECK(!k.movimentValidator(6, 7));  //movimento inválido - l maior
    CHECK(!k.movimentValidator(4, 4));  //movimento inválido - parado
}
