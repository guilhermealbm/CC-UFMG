#ifndef PIECES_H
#define PIECES_H

#include <string>

class Pieces {
protected:
  int x;
  int y;
  std::string color;
public:
  bool movementDirection; // for pawn --- 0 - back 1 - ahead
  Pieces(int x, int y, std::string color);
  virtual ~Pieces(){};
  int getX();
  void setX(int x);
  int getY();
  void setY(int y);
  std::string getColor();
  virtual std::string getName() = 0;
  virtual bool movimentValidator(int x, int y) = 0;
};

#endif
