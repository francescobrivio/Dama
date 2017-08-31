#include "Pedina.h"
#include "include/cppinclude.h"

Pedina::Pedina()
{
  Board* board = new Board(); 
  srand (time(NULL));
  _x = rand() % (Nslots-1) + 1;
  _y = rand() % (Nslots-1) + 1;
  _color = "red";
  _board = board;
  _dir = 0;
  _isPedone = false;
}

Pedina::Pedina(const std::string color, int x, int y, Board* board, const int dir, bool isPedone):
  _x (x),
  _y (y),
  _color (color),
  _board (board),
  _dir (dir),
  _isPedone (isPedone)
{
}

Pedina::Pedina(const Pedina& origin):
  _x (origin.getX()),
  _y (origin.getY()),
  _color (origin.getColor()),
  _board (origin.getBoard()),
  _dir (origin.getDir()),
  _isPedone (origin.getPedone())
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
  this->setDir(origin.getDir());
  this->setPedone(origin.getPedone());

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

void Pedina::setDir(int dir)
{
  _dir = dir;
}

int Pedina::getDir() const
{
  return _dir;
}

void Pedina::setPedone(bool isPedone)
{
  _isPedone = isPedone;
}

bool Pedina::getPedone() const
{
  return _isPedone;
}

void Pedina::Move(int x, int y)
{
  this->setX(x);
  this->setY(y);
}

bool Pedina::CheckMove(const std::string pos)
{
  std::cout << "sksksks" << std::endl;
  char status = ' ';
  char xStr = ' ', yStr =  ' ';
  int xStart = 0, yStart = 0;
  int xStop = 0, yStop = 0;
  bool flag = true;

  for(unsigned int istep = 1; istep<pos.size()/2; istep++)
    {
      yStr = tolower(pos[istep*2-2]);
      xStr = tolower(pos[istep*2-1]);

      yStart = (int)(yStr - '0');
      xStart = (int)(xStr - 'a' + 1);

      yStr = tolower(pos[istep*2]);
      xStr = tolower(pos[istep*2+1]);

      yStop = (int)(yStr - '0');
      xStop = (int)(xStr - 'a' + 1);

      status = this->getBoard()->getStatus(xStop,yStop);
  
      if(status != ' ')
        flag &= false;
      
      else
        if(yStart+this->getDir() == yStop && abs(xStart-xStop) == 1)
          flag &= true;
        else if(yStart+2*this->getDir() == yStop && abs(xStart-xStop) == 2)
          {
            status = this->getBoard()->getStatus((xStart+xStop)/2, (yStart+yStop)/2);
            if(status != ' ' && status != this->getColor()[0])
              flag &= true;
            else
              flag &= false;
          }
        else
	      flag &= false;
    }
  
  return flag;
}


std::string Pedina::CheckEat(const Position oldPos, const Position newPos)
{
  std::string steps = "";
  int oldX = 0, newX = 0, oldY =0, newY = 0;
  int nextX[Nmoves_pedina], nextY = 0;
  int prevX = 0, prevY = 0;
  Position prevPos, nextPos;
  char status = ' ';
 
  oldX = oldPos.first;
  oldY = oldPos.second;
  newX = newPos.first;
  newY = newPos.second;

  nextX[0] = 2*newX-oldX;
  nextY = newY+this->getDir();
  
  if(nextX[0] > 8 || nextX[0] < 1 || nextY < 1 || nextY > 8)
    steps = "";
  else if(this->getBoard()->getStatus(nextX[0], nextY) == ' ')
    { 
      steps += intToString(nextY) + this->getBoard()->getAlpha(nextX[0]);
      
      //std::cout << "POSSO MANGIARE!!!" << std::endl;
      prevX = nextX[0];
      prevY = nextY;
      nextY = newY+2*this->getDir();
      nextX[0] = 2*newX-oldX-1;
      nextX[1] = 2*newX-oldX+1;
      
      for(int i=0; i<Nmoves_pedina; i++)
	{
	  if(nextX[i] > 8 || nextX[i] < 1 || nextY < 1 || nextY > 8)
	    continue;
	  
	  status = this->getBoard()->getStatus(nextX[i], nextY);

	  if(status != (this->getColor())[0] && status != ' ')
	   {
	     prevPos = std::pair<int, int>(prevX, prevY);
	     nextPos = std::pair<int, int>(nextX[i], nextY);
	     steps += CheckEat(prevPos, nextPos);    	
	   }
	} 
    }

  return steps; 
}


Moves Pedina::Check()
{
  int new_x[Nmoves_pedina], new_y = 0;
  Moves moves;
  Position oldPos, newPos;
  char status = ' ';
  std::string steps = "", action = "";

  new_y  = this->getY() + this->getDir();
  new_x[0] = this->getX() - 1;
  new_x[1] = this->getX() + 1;
 
  for(int i=0; i<Nmoves_pedina; i++)
    {
      action = intToString(this->getY()) + this->getBoard()->getAlpha(this->getX());

      if(new_x[i] > 8 || new_x[i] < 1 || new_y < 1 || new_y > 8)
	continue;
      
      status = this->getBoard()->getStatus(new_x[i], new_y);
      newPos = std::pair<int, int>(new_x[i], new_y);

      if(status == this->getColor()[0])
        continue;
      else if(status == ' ')
	action += intToString(new_y) + this->getBoard()->getAlpha(new_x[i]);
      else
        {
          oldPos = std::pair<int, int>(this->getX(), this->getY());
          steps = this->CheckEat(oldPos, newPos);
          if(steps != "")
            action += steps;
        }

      moves.push_back(action);
    }

  return moves;
}
