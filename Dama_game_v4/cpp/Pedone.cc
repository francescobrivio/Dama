#include "Pedone.h"
#include "include/cppinclude.h"

Pedone::Pedone()
{
  Board* board = new Board(); 
  srand (time(NULL));
  _x = rand() % (Nslots-1) + 1;
  _y = rand() % (Nslots-1) + 1;
  _color = "blue";
  _board = board;
}

Pedone::Pedone(const std::string color, int x, int y, Board* board)
{
  _x = x;
  _y = y;
  _color = color;
  _board = board;
}

/*Pedone::Pedone(const Pedone& origin):
{
  _x (origin.getX()),
  _y (origin.getY()),
  _color (origin.getColor()),
  _board (origin.getBoard())
}*/

Pedone::~Pedone()
{
}

bool Pedone::CheckMove(const std::string pos)
{
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

      status = tolower(this->getBoard()->getStatus(xStop,yStop));
  
      if(status != ' ')
        flag &= false;
      
      else
        if( abs(yStart-yStop) == 1 && abs(xStart-xStop) == 1)
          flag &= true;
        else if(abs(yStart-yStop) == 2 && abs(xStart-xStop) == 2)
          {
            status = tolower(this->getBoard()->getStatus((xStart+xStop)/2, (yStart+yStop)/2));
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


std::string Pedone::CheckEat(const Position oldPos, const Position eatPos)
{
  std::string steps = "";
  int oldX = 0, eatX = 0, oldY =0, eatY = 0;
  int newX[Nmoves_pedone], newY[Nmoves_pedone];
  int prevX = 0, prevY = 0;
  Position prevPos, nextPos;
  char status = ' ';
 
  oldX = oldPos.first;
  oldY = oldPos.second;
  eatX = eatPos.first;
  eatY = eatPos.second;

  newX[0] = 2*eatX-oldX;
  newY[0] = 2*eatY-oldY;
  
  if(newX[0] > 8 || newX[0] < 1 || newY[0] < 1 || newY[0] > 8)
    steps = "";
  else if(this->getBoard()->getStatus(newX[0], newY[0]) == ' ')
    { 
      steps += intToString(newY[0]) + this->getBoard()->getAlpha(newX[0]);
      
      prevX = newX[0];
      prevY = newY[0];
      newY[0] = 2*eatY-oldY-1;
      newY[1] = 2*eatY-oldY+1;
      newX[0] = 2*eatX-oldX-1;
      newX[1] = 2*eatX-oldX+1;
      
      for(int i=0; i<Nmoves_pedone; i++)
	{
	  if(newX[i] > 8 || newX[i] < 1 || newY[i] < 1 || newY[i] > 8)
	    continue;
	  
	  status = this->getBoard()->getStatus(newX[i], newY[i]);

	  if(status != (this->getColor())[0] && status != ' ')
	   {
	     prevPos = std::pair<int, int>(prevX, prevY);
	     nextPos = std::pair<int, int>(newX[i], newY[i]);
	     steps += CheckEat(prevPos, nextPos);    	
	   }
	} 
    }

  return steps; 
}


Moves Pedone::CPUCheck()
{
  int new_x[Nmoves_pedone], new_y[Nmoves_pedone];
  Moves moves;
  Position oldPos, newPos;
  char status = ' ';
  std::string steps = "", action = "";

  new_y[0] = this->getY() - 1;
  new_y[1] = this->getY() + 1;
  new_x[0] = this->getX() - 1;
  new_x[1] = this->getX() + 1;
 
  for(int i=0; i<Nmoves_pedone; i++)
    {
      action = intToString(this->getY()) + this->getBoard()->getAlpha(this->getX());

      if(new_x[i] > 8 || new_x[i] < 1 || new_y[i] < 1 || new_y[i] > 8)
	continue;
      
      status = this->getBoard()->getStatus(new_x[i], new_y[i]);
      newPos = std::pair<int, int>(new_x[i], new_y[i]);

      if(status == this->getColor()[0])
        continue;
      else if(status == ' ')
	action += intToString(new_y[i]) + this->getBoard()->getAlpha(new_x[i]);
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
