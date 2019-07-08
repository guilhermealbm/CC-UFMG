#ifndef PDS2_PECA_H
#define PDS2_PECA_H

#include <string>

class Peca {
protected:
  int x;
  int y;
  std::string color;
public:
  bool movementDirection; // for pawn --- 0 - back 1 - ahead
  Peca(int x, int y, std::string color);
  virtual ~Peca(){};
  int getX();
  void setX(int x);
  int getY();
  void setY(int y);
  std::string getColor();
  virtual std::string getName() = 0;
  virtual bool movimentValidator(int x, int y) = 0;
};

#endif
