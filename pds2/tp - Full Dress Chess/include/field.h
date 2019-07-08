#ifndef FIELD_H
#define FIELD_H

#include "pieces.h"

#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

#include <string>

#define POS_MIN 1
#define POS_MAX 8

class Field {
private:
    Pieces* allPieces[8][8];
public:

    Field();
    void initField();
    Pieces* getPiece(int x, int y);
    bool isOccupied(int x, int y);
    bool isOccupiedByEnemy(int x, int y, std::string color);
    bool move(Pieces *piece, int x, int y);
    bool hasOtherPieceOnTheWay(Pieces *piece, int x, int y);
    bool kingInCheck(std::string);
    void printField();

};

#endif
