#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "field.h"

#include "pieces.h"

#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>

#define CHARTOLETTER 96
#define CHARTOINT 48

class Game {
private:
    Player player1;
    Player player2;
    Field field;
public:

    Game(std::string namePlayer1, std::string namePlayer2);
    void initGame();
    void playGame();

};

#endif
