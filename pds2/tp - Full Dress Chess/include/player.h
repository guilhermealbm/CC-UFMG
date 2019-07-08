#ifndef PLAYER_H
#define PLAYER_H

#include "field.h"

class Player {
private:
    std::string name;
    std::string color;
    Field* field;
public:
    Player(std::string name, std::string color, Field &field);
    std::string getName();
    std::string getColor();
    bool makeMove(int pieceX, int pieceY, int nextX, int nextY);
};

#endif