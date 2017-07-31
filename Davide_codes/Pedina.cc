#include "Pedina.h"
#include "include/cppinclude.h"

Pedina::Pedina()
{
  Board* board = new Board(); 
  srand (time(NULL));
  _x = rand() % Nslot + 1;
  _y = rand() % Nslot + 1;
  _color = 1;
  _board = board;
}

Pedina::Pedina(const std::string color, int x, int y, Board* board):
  _x (x),
  _y (y),
  _color (color),
  _board (board)
{
}

Pedina::Pedina(const Pedina& origin):
  _x (origin.getX()),
  _y (origin.getY()),
  _color (origin.getColor()),
  _board (origin.getBoard())
{
}

Pedina& Pedina::operator= (const Pedina& origin)
{
  if (&origin == this) return *this;

  this->Pedina::operator=(origin);
  
  this->setX(origin.getX());
  this->setY(origin.getY());
  this->setColor(origin.getColor());
  this->setBoard(origin.getBoard());

  return *this;
}

Pedina::~Pedina()
{
}

void Pedina::setX(int x)
{
  _x = x;
}

void Pedina::setY(int y)
{
  _y = y;
}

int Pedina::getX() const
{
  return _x;
}

int Pedina::getY() const
{
  return _y;
}

void Pedina::setColor(std::string color)
{
  _color = color;
}

std::string Pedina::getColor() const
{
  return _color;
}

void Pedina::setBoard(Board* board)
{
  _board = board;
}

Board* Pedina::getBoard() const
{
  return _board;
}

void Pedina::Move(int x, int y)
{
  this->setX(x);
  this->setY(y);
}


Moves Pedina::Check()
{
  int new_x[Nmoves_pedina], new_y = 0;
  char isfree[Nmoves_pedina];
  Moves moves;
  Position newPos;
  std::string status = "";

  new_y  = this->getY() + 1;
  new_x[0] = this->getX() - 1;
  new_x[1] = this->getX() + 1;

  for(int i=0; i<Nmoves_pedina; i++)
    {
      isfree[i] = this->getBoard()->getStatus(new_x[i], new_y);  
      
      if(isfree[i] == ' ') status = "free";
      else if (tolower(isfree[i]) == 'w') status = "ally";
      else if (tolower(isfree[i]) == 'b') status = "enemy";
      else status = "error";
      
      newPos = std::pair<int, int>(new_x[i], new_y);
      
      moves.push_back(std::pair<Position, std::string>(newPos, status));
    }

  return moves;  

}

