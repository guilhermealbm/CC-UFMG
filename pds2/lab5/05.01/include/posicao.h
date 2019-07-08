#ifndef PDS2_POSICAO_H
#define PDS2_POSICAO_H

#include <string>

class Posicao {
private:
  int x;
  int y;
public:
  int getX();
  void setX(int x);
  int getY();
  void setY(int y);
};
#endif
