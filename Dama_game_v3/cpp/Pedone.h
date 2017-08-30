#ifndef Pedone_H
#define Pedone_H

#include "include/configurable.h"
#include "Pedina.h"

class Pedone : public Pedina
{
 public:
  Pedone();
  Pedone(const std::string color, int x, int y, Board* board, const int dir);
  Pedone(const Pedone& origin);
  ~Pedone();

  Pedone& operator=(const Pedone& origin);

  void setColor(std::string color);
  std::string getColor() const;

  void setX(int x);
  void setY(int y);
  
  int getX() const;
  int getY() const;

  Board* getBoard() const;
  void setBoard(Board* board);

  void setDir(int dir);
  int getDir() const;

  void Move(int x, int y);
  bool CheckMove(const std::string pos);
  std::string CheckEat(const Position oldPos, const Position newPos);
  Moves Check();

  
 private:
  std::string _color;
  int _x;
  int _y;
  int _dir;
  Board* _board;

};

#endif //Pedone_H
