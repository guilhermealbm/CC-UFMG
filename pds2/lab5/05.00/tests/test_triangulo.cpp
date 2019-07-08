#include "doctest.h"
#include "triangulo.h"


TEST_CASE("Teste VPL - Equilatero") {
    Triangulo t(5, 5, 5);
    Tipo tipo = t.determinar_tipo();
    CHECK_EQ(tipo, 0);
}

TEST_CASE("Teste VPL - Isosceles") {
    Triangulo t(5, 5, 6);
    Tipo tipo = t.determinar_tipo();
    CHECK_EQ(tipo, 1);
}

TEST_CASE("Teste VPL - Escaleno") {
    Triangulo t(5, 6, 7);
    Tipo tipo = t.determinar_tipo();
    CHECK_EQ(tipo, 2);
}

TEST_CASE("Teste VPL - Excecao Negativo") {
    CHECK_THROWS(new Triangulo(5, -5, 5));
}

TEST_CASE("Teste VPL - Triangulo Impossível de ser construído") {
    CHECK_THROWS(new Triangulo(5, 5, 12));
}