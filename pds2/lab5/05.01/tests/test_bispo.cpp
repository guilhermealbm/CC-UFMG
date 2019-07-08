#include "../third_party/doctest.h"
#include "../include/bispo.h"

TEST_CASE("Teste 1: Testando o Construtor"){
    CHECK_NOTHROW(Bispo(1, 1, "Branca"));
}

TEST_CASE("Teste 2: Testando Movimentos Válidos"){
    Bispo b(4, 4, "Branca");
    CHECK(b.movimentValidator(1, 1));   //movimento válido
    CHECK(b.getName() == "Bispo");
    CHECK(b.movimentValidator(3, 3));   //movimento válido
    CHECK(b.movimentValidator(8, 8));   //movimento válido
}

TEST_CASE("Teste 3: Testando Movimentos Inválidos"){
    Bispo b(4, 4, "Branca");
    CHECK(!b.movimentValidator(1, 2));  //movimento inválido - fora da diagonal
    CHECK(!b.movimentValidator(5, 4));  //movimento inválido - movimento vertical
    CHECK(!b.movimentValidator(2, 3));  //movimento inválido - fora da diagonal
    CHECK(!b.movimentValidator(4, 2));  //movimento inválido - movimento horizontal
    CHECK(!b.movimentValidator(4, 4));  //movimento inválido - parado
}
