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
            if(status != ' ' && status != tolower(this->getColor()[0]))
              flag &= true;
            else
              flag &= false;
          }
        else
	      flag &= false;
    }
  
  return flag;
}


std::string Pedone::CPUCheckEat(const Position oldPos, const Position eatPos)
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
	  for(int j=0; j<Nmoves_pedone; j++)
	    {
	      if(newX[i] > 8 || newX[i] < 1 || newY[j] < 1 || newY[j] > 8)
		continue;
	      
	      if(newX[i] == eatX && newY[j] == eatY)
		continue;

	      status = tolower(this->getBoard()->getStatus(newX[i], newY[j]));
	      
	      if(status != tolower((this->getColor())[0]) && status != ' ')
		{
		  prevPos = std::pair<int, int>(prevX, prevY);
		  nextPos = std::pair<int, int>(newX[i], newY[j]);
		  steps += CPUCheckEat(prevPos, nextPos);    	
		}
	    } 
	}
    }

  return steps; 
}

/*
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
          steps = this->CPUCheckEat(oldPos, newPos);
          if(steps != "")
            action += steps;
        }

      moves.push_back(action);
    }

  return moves;
}

*/

Moves Pedone::CPUCheck() 
{                          
  int new_x = 0, new_y = 0, new_x2 = 0, new_y2 = 0;   
  int x = 0, y = 0;
  Moves moves, pawns_pos;  
  Position oldPos, newPos;  
  char status = ' ';    
  std::string steps = "", action = "", pos = "";  
  bool flag = false;
  int rad = 1, side = 0;
  char xStr = ' ', yStr = ' ';

  srand (time(NULL));

  while(!flag)
    {
      // Number of blocks around the big pawn at radius = rad
      side = 2*rad + 1; // lenght of the square side around the big pawn

      // look for opponent pawns on the circle of radius rad around the big
      // look into the top and the bottom sides
      for(int i=0; i<side; i++)
	{
	  x = this->getX()-rad+i;
	  if(x > 8 || x < 1)
	    continue;
	
	  y = this->getY()+rad;	  
	  if(y > 0 && y < 9) 
	    {
	      status = tolower(this->getBoard()->getStatus(x, y));

	      if(status != ' ' && status != tolower(this->getColor()[0]))
		{
		  pos = intToString(y) + this->getBoard()->getAlpha(x); 
		  pawns_pos.push_back(pos);
		}
	    }
	  
	  y = this->getY()-rad;
	  if(y > 0 && y < 9)
            {
	      status = tolower(this->getBoard()->getStatus(x, y));

	      if(status != ' ' && status != tolower(this->getColor()[0]))
		{
		  pos = intToString(y) + this->getBoard()->getAlpha(x);
		  pawns_pos.push_back(pos);
		}
	    }
	}
      
      side = 2*(rad-1)+1;
      // look into the right and the left side, but no the corners (already checked);
      for(int i=0; i<side; i++)
        {
          y = this->getY()-(rad-1)+i;
          if(y > 8 || y < 1)
            continue;

          x = this->getX()+rad;
          if(x > 0 && x < 9)
            {
	      status = tolower(this->getBoard()->getStatus(x, y));
	      if(status != ' ' && status != tolower(this->getColor()[0]))
		{
		  pos = intToString(y) + this->getBoard()->getAlpha(x);
		  pawns_pos.push_back(pos);
		}
	    }
	  
          x = this->getX()-rad;
          if(x > 0 && x < 9)
            {
	      status = tolower(this->getBoard()->getStatus(x, y));
	      if(status != ' '&& status != tolower(this->getColor()[0]))
		{
		  pos = intToString(y) + this->getBoard()->getAlpha(x);
		  pawns_pos.push_back(pos);
		}
	    }
	}

      if(pawns_pos.size() > 0)
	{
	  for(unsigned int i=0; i<pawns_pos.size(); i++)
	    {
	      action = intToString(this->getY())+this->getBoard()->getAlpha(this->getX());

	      if(rad == 1)
		{     
		  pos = pawns_pos[i];
		  yStr = tolower(pos[0]);
		  xStr = tolower(pos[1]);
		  y = (int)(yStr - '0');
		  x = (int)(xStr - 'a' + 1);

		  oldPos = std::pair<int, int>(this->getX(), this->getY()); 
		  newPos = std::pair<int, int>(x, y);
		  steps = this->CPUCheckEat(oldPos, newPos);       
		  if(steps != "") 
		    {
		      action += steps;  
		      moves.push_back(action);	
		    }
		}
	      else
		{
	     	  pos = pawns_pos[i];
                  yStr = tolower(pos[0]);
                  xStr = tolower(pos[1]);
		  y = (int)(yStr - '0');
		  x = (int)(xStr - 'a' + 1);

		  new_x2 = 0, new_y2 = 0;
		  
		  if(x>this->getX())
		    new_x = this->getX()+1;
		  else if(x == this->getX())
		    {
		      new_x  = this->getX()+1;
		      new_x2 = this->getX()-1;
		    }
		  else
		    new_x = this->getX()-1;
		  		  
		  if(y>this->getY())
                    new_y = this->getY()+1;
                  else if(y == this->getY())
                    {
		      new_y  = this->getY()+1;
                      new_y2 = this->getY()-1;
		    }
                  else
                    new_y = this->getY()-1;

		  if(new_x2 != 0)
		    {
		      if(new_x2 > 0 && new_x2 < 9)
			{
			  if(new_x > 0 && new_x < 9)
			    {
			      status = tolower(this->getBoard()->getStatus(new_x, new_y));
			      if(status != ' ')
				new_x = new_x2;
			      else
				{
				  status = tolower(this->getBoard()->getStatus(new_x2, new_y));
				  if(status == ' ')
				    if(rand()%100 > 50)
				      new_x = new_x2;
				}
			    }
			  else
			    new_x = new_x2;
			}
		    }
	
		  if(new_y2 != 0)
                    {
                      if(new_y2 > 0 && new_y2 < 9)
			{
                          if(new_y > 0 && new_y < 9)
                            {
                              status = tolower(this->getBoard()->getStatus(new_x, new_y));
                              if(status != ' ')
				new_y = new_y2;
                              else
				{
                                  status = tolower(this->getBoard()->getStatus(new_x, new_y2));
                                  if(status == ' ')
                                    if(rand()%100 > 50)
                                      new_y = new_y2;
                                }
                            }
                          else
                            new_y = new_y2;
                        }
		    }

		  status = tolower(this->getBoard()->getStatus(new_x, new_y));
		  
		  if(status == ' ')
		    {
		      steps = intToString(new_y) + this->getBoard()->getAlpha(new_x);
		      action += steps;
		      moves.push_back(action);		  
		    }
		}
	    }
	}
      
      if(moves.size() > 0)
	flag = true;
      
      pawns_pos.clear();
      rad++;

      if(rad>Nslots-1)
	break;
    }

  return moves;
}
