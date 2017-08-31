#ifndef Pedone_H
#define Pedone_H

#include "include/configurable.h"
#include "Pedina.h"

class Pedone : public Pedina
{
 public:
  Pedone();
  Pedone(const std::string color, int x, int y, Board* board);
  Pedone(const Pedone& origin);
  ~Pedone();
  
  bool CheckMove(const std::string pos);
  std::string CheckEat(const Position oldPos, const Position newPos);
  Moves Check();

  
 private:
  std::string _color;
  int _x;
  int _y;
  Board* _board;

};

#endif //Pedone_H
