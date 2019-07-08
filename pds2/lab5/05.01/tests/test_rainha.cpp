#include "../third_party/doctest.h"
#include "../include/rainha.h"

TEST_CASE("Teste 1: Testando o Construtor"){
    CHECK_NOTHROW(Rainha(1, 1, "Branca"));
}

TEST_CASE("Teste 2: Testando Movimento na Vertical"){
    Rainha q(1, 1, "Branca");
    CHECK(q.movimentValidator(2, 1));   //movimento válido
    CHECK(q.movimentValidator(8, 1));   //movimento válido
    CHECK(q.movimentValidator(5, 1));   //movimento válido
}

TEST_CASE("Teste 3: Testando Movimento na Horizontal"){
    Rainha q(1, 1, "Branca");
    CHECK(q.movimentValidator(1, 2));   //movimento válido
    CHECK(q.movimentValidator(1, 5));   //movimento válido
    CHECK(q.movimentValidator(1, 8));   //movimento válido
}


TEST_CASE("Teste 4: Testando Movimento na Diagonal"){
    Rainha q(4, 2, "Branca");
    CHECK(q.movimentValidator(3, 1));   //movimento válido
    CHECK(q.movimentValidator(8, 6));   //movimento válido
    CHECK(q.movimentValidator(5, 3));   //movimento válido
}

TEST_CASE("Teste 5: Testando Movimentos Inválidos"){
    Rainha q(4, 2, "Branca");
    CHECK(!q.movimentValidator(1, 1));  //movimento inválido - fora de reta ou diagonal
    CHECK(!q.movimentValidator(8, 8));  //movimento inválido - fora de reta ou diagonal
    CHECK(!q.movimentValidator(6, 5));  //movimento inválido - fora de reta ou diagonal
    CHECK(!q.movimentValidator(2, 3));  //movimento inválido - fora de reta ou diagonal
    CHECK(!q.movimentValidator(4, 2));  //movimento inválido - parado
}
