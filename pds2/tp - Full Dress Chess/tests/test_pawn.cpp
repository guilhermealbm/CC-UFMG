#include "../third_party/doctest.h"
#include "../include/pawn.h"

TEST_CASE("Teste 1: Testando o Construtor"){
    CHECK_NOTHROW(Pawn(1, 1, "Branca", 1));
}

TEST_CASE("Teste 2: Testando Movimento Básico"){
    Pawn p(1, 1, "Branca", 1);
    CHECK(p.movimentValidator(2, 1));   //movimento válido

    Pawn p2(3, 4, "Preta", 1);
    CHECK(p2.movimentValidator(4, 4));  //movimento válido
}


//Movimentando peça manualmente apenas para testes
TEST_CASE("Teste 3: Testando Primeiro Movimento"){
    Pawn p(2, 1, "Branca", 1);
    CHECK(p.movimentValidator(4, 1));   //movimento válido
    p.setX(4);
    p.setY(1);
    CHECK(!p.movimentValidator(6, 1));  //movimento inválido - dist(segundo movimento) = 1

    Pawn p2(2, 4, "Preta", 1);
    CHECK(p2.movimentValidator(3, 4));  //movimento válido
    p2.setX(4);
    p2.setY(1);
    CHECK(!p2.movimentValidator(4, 4)); //movimento inválido
}

TEST_CASE("Teste 4: Testando Movimentos Inválidos"){
    Pawn p(1, 1, "Branca", 1);
    CHECK(!p.movimentValidator(4, 1));  //movimento inválido - muito longo
    CHECK(!p.movimentValidator(1, 2));  //movimento inválido - não mexe no eixo Y
    CHECK(!p.movimentValidator(1, 1));  //movimento inválido - parado
}

TEST_CASE("Teste 5: Testando Movimentos para trás"){
    Pawn p(2, 1, "Branca", 1);
    CHECK(!p.movimentValidator(1, 1));   //movimento inválido

    Pawn p1(7, 1, "Preta", 0);
    CHECK(!p1.movimentValidator(8, 1));  //movimento inválido

    Pawn p2(5, 4, "Branca", 1);
    CHECK(p2.movimentValidator(6, 4));   //movimento válido

    Pawn p3(3, 6, "Branca", 0);
    CHECK(p3.movimentValidator(2, 6));   //movimento válido
}

TEST_CASE("Teste 6: Testando Nome e Cor"){
    Pawn p(4, 5, "Preta", 1);
    CHECK(p.getName() == "pawn");
    CHECK(p.getColor() == "Preta");

    Pawn p2(5, 4, "Branca", 0);
    CHECK(p2.getName() == "pawn");
    CHECK(p2.getColor() == "Branca");
}