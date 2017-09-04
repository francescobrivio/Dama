#ifndef Moves_H
#define Moves_H

#include "include/configurable.h"
#include <typeinfo>


Pedina* findPedina(std::vector<Pedina*> *pawns, int x, int y)
{
  Pedina* tmp = new Pedina();
 
  for(unsigned int i=0; i<pawns->size(); i++)
    if(x == pawns->at(i)->getX() && y == pawns->at(i)->getY())
      tmp = pawns->at(i);

  return tmp;
}

int findPedina2(std::vector<Pedina*> *pawns, int x, int y)
{
  int tmp = -1;
  for(unsigned int i=0; i<pawns->size(); i++)
    if(x == pawns->at(i)->getX() && y == pawns->at(i)->getY())
      tmp = i;

  return tmp;
}

std::vector<Pedina>* erasePawns(std::vector<Pedina*> *pawns, std::string move)
{
  std::vector<Pedina*> *tmp_pawns = new std::vector<Pedina*>;
  
  int old_x = 0, old_y = 0, new_x = 0, new_y = 0, med_x = 0, med_y = 0;
  char old_xStr = ' ', old_yStr =  ' ', new_xStr = ' ', new_yStr =  ' ';
  
  old_yStr = tolower(move[0]);
  old_xStr = tolower(move[1]);
  old_y = (int)(old_yStr - '0');
  old_x = (int)(old_xStr - 'a' + 1);

  new_yStr = tolower(move[move.size()-2]);
  new_xStr = tolower(move[move.size()-1]);
  new_y = (int)(new_yStr - '0');
  new_x = (int)(new_xStr - 'a' + 1);
  
  med_x = (old_x + new_x)/2;
  med_y = (old_y + new_y)/2;
  
  for (unsigned int i=0; i<pawns->size(); i++)
    if (med_x != pawns->at(i).getX() || med_y != pawns->at(i).getY())
      tmp_pawns->push_back(pawns->at(i));
  
  return tmp_pawns;
}

void evolvePedina(std::vector<Pedina*> *pawns)
{
    for(unsigned int i=0; i<pawns->size(); i++)
    {
      if (typeid(*pawns->at(i)) != typeid(Pedina))
        continue;
      else
      {
        if (pawns->at(i)->getY()+pawns->at(i)->getDir() < 1 || pawns->at(i)->getY()+pawns->at(i)->getDir() > 8)
        {
          // Pushback a new Pedone
          if(pawns->at(i)->getColor()[0] == 'w')
            pawns->push_back( new Pedone("W", pawns->at(i)->getX(), pawns->at(i)->getY(), pawns->at(i)->getBoard()) );
          else if (pawns->at(i)->getColor()[0] == 'b')
            pawns->push_back( new Pedone("B", pawns->at(i)->getX(), pawns->at(i)->getY(), pawns->at(i)->getBoard()) );

          // Erase the old Pedina
          pawns->erase(pawns->begin() + i);
        }
      }
    }
}

void updatePositions(Board* board, std::vector<Pedina*> *P1pawns, std::vector<Pedina*> *P2pawns)
{
  int x = 0, y = 0;
  
  std::string color = "";  
  
  for(int nx=Nslots-1; nx>0; nx--)                                                                                                                    
    for(int ny=1; ny<Nslots; ny++) 
      board->setStatus(nx, ny, " ");

  for(unsigned int i=0; i<P1pawns->size(); i++)
    {      
      x = P1pawns->at(i)->getX();
      y = P1pawns->at(i)->getY();
      color = (P1pawns->at(i)->getColor())[0];

      board->setStatus(x, y, color);      
    }  

  for(unsigned int i=0; i<P2pawns->size(); i++)
    {
      x = P2pawns->at(i)->getX();
      y = P2pawns->at(i)->getY();
      color = (P2pawns->at(i)->getColor())[0];

      board->setStatus(x, y, color);
    }  
}

std::string ChooseBestMove(Moves moves)
{
  const int nMoves = moves.size();
  std::string best_move = "";
  char max_y = '0';
  unsigned int max_lenght = 0, max_diff = 0, diff = 0;

  for(int i=0; i<nMoves; i++)
    if(moves.at(i).size() > max_lenght)
      max_lenght = moves.at(i).size();	
  
  return best_move;       
}


std::string autoMove(std::vector<Pedina> *pawns)
{
  Moves moves;
  std::string best_move = "";

  for(unsigned int ipawn = 0; ipawn < pawns->size(); ipawn++)
    {
      Moves tmp_moves;
      tmp_moves = pawns->at(ipawn).Check();
      
      for(unsigned int imove = 0; imove < tmp_moves.size(); imove++)
	moves.push_back(tmp_moves.at(imove));
    }

  best_move = ChooseBestMove(moves);

  return best_move;
}



#endif // Moves_H
