#ifndef Pedina_H
#define Pedina_H

#include "include/configurable.h"

class Pedina
{
 public:
  Pedina();
  Pedina(const std::string color, int x, int y, Board* board, const int dir);
  Pedina(const Pedina& origin);
  ~Pedina();

  Pedina& operator=(const Pedina& origin);

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
  
  virtual bool CheckMove(const std::string pos);
  virtual std::string CheckEat(const Position oldPos, const Position newPos);
  virtual Moves Check();
  
  virtual std::string getIdentity() {return "Pedina";};

  
 protected:
  std::string _color;
  int _x;
  int _y;
  int _dir;
  Board* _board;

};

#endif //Pedina_H
