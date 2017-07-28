#ifndef Pedina_H
#define Pedina_H

#include "configurable.h"
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

class Pedina:
{

 public:
  Pedina();
  Pedina(const TString color, Int_t x, Int_t y);
  Pedina(const Pedina& origin);
  ~Pedina();

  Pedina& operator=(const Pedina& origin);

  void setColor(TString color);
  TString getColor();

  void setX(Int_t x);
  void setY(Int_t y);
  
  Int_t getX();
  Int_t getY();

  void Move(Int_t x, Int_t y);
  void Check(Int_t x, Int_t y);
  
 private:
  Int_t _color;
  Int_t _x;
  Int_t _y;
  Player* _player;
  Board* _board;

};

#endif //Pedina_H
