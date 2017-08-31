#ifndef Pedina_H
#define Pedina_H

#include "include/configurable.h"

class Pedina
{
 public:
  Pedina();
  Pedina(const std::string color, int x, int y, Board* board, const int dir, bool isPedone);
  Pedina(const Pedina& origin);
  ~Pedina();

  Pedina& operator=(const Pedina& origin);

  void setColor(std::string color);
  std::string getColor() const;

  void setX(int x);
  int getX() const;
  
  void setY(int y);
  int getY() const;

  void setBoard(Board* board);
  Board* getBoard() const;

  void setDir(int dir);
  int getDir() const;

  void setPedone(bool isPedone);
  bool getPedone() const;

  void Move(int x, int y);
  
  virtual bool CheckMove(const std::string pos);
  virtual std::string CheckEat(const Position oldPos, const Position newPos);
  virtual Moves Check();
  
  
 protected:
  std::string _color;
  int _x;
  int _y;
  int _dir;
  Board* _board;
  bool _isPedone;

};

#endif //Pedina_H
