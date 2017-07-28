#include "Pedina.h"
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TRandom3.h>

Pedina::Pedina()
{
  srand (time(NULL));
  _x = rand() % N + 1;
  _y = rand() % N + 1;
  _color = 1;
}

Pedina::Pedina(const TString color, Int_t x, Int_t y)
{
  this->setX(x);
  this->setY(y);
  this->setColor(color);
}

Pedina::Pedina(const Pedina& origin)
{
  this->setX(origin.getX());
  this->setY(origin.getY());
  this->setColor(origin.getColor());
}

Pedina& Pedina::operator= (const Pedina& origin)
{
  if (&origin == this) return *this;

  this->Pedina::operator=(origin);
  
  this->setX(origin.getX());
  this->setY(origin.getY());
  this->setColor(origin.getColor());

  return *this;
}

Pedina::~Pedina()
{
}

Pedina::Move(Int_t x, Int_t y)
{
  this->setX(x);
  this->setY(y);
}

Pedina::Check()
{
  Int_t new_x1[Nmoves_pedina], new_y = 0;
  Int_t isfree[Nmoves_pedina];
  Moves moves;
  Position newPos;
  TString status = "";

  new_y  = this->getY() + 1;
  new_x[0] = this->getX() - 1;
  new_x[1] = this->getX() + 1;

  for(Int_t i=0; i<Nmoves_pedina; i++)
    {
      isfree[i] = this->getBoard()->isFree(new_x[i], new_y);  
      
      if(isfree[i] == 0) status = "free";
      else if (isfree[i] == 1) status = "ally";
      else if (isfree[i] == -1) status = "enemy";
      else status = "error";
      
      newPos = std::pair<Int_t, Int_t>(new_x[i], new_y);
      
      moves.push_back(std::pair<Position, TString>(newPos, status));
    }

  return moves;  
}
