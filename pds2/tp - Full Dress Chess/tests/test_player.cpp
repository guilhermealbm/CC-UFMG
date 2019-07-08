#include "../third_party/doctest.h"
#include "../include/player.h"

TEST_CASE("Teste 1: Testando o Construtor"){
    Field f;
    CHECK_NOTHROW(Player("jogador", "Branca", f));   
}

TEST_CASE("Teste 2: Testando Nome"){
    Field f;
    Player p1("jogador 1", "Branca", f);
    CHECK(p1.getName() == "jogador 1");

    Player p2("jogador 2", "Preta", f);
    CHECK(p2.getName() == "jogador 2");
    CHECK(p2.getName() != "jogador 1");
}

TEST_CASE("Teste 3: Testando Cor"){
    Field f;
    Player p1("jogador 1", "Branca", f);
    CHECK(p1.getColor() == "Branca");

    Player p2("jogador 2", "Preta", f);
    CHECK(p2.getColor() == "Preta");
    CHECK(p1.getColor() != p2.getColor());
}

TEST_CASE("Teste 4: Testando Movimento"){
    Field f;
    f.initField();
    Player p1("jogador 1", "White", f);
    Player p2("jogador 2", "Black", f);

    CHECK(p1.makeMove(2, 2, 4, 2));
    CHECK(f.getPiece(4, 2) != nullptr);

    CHECK(p2.makeMove(7, 2, 6, 2));
    CHECK(f.getPiece(6, 2) != nullptr);

    CHECK(!p1.makeMove(4, 2, 4, 3));    //movimento inválido
    CHECK(f.getPiece(4, 3) == nullptr);

    CHECK(!p1.makeMove(5, 5, 6, 5));    //posição vazia
    CHECK(!p1.makeMove(6, 2, 5, 1));    //peça de outra cor
}