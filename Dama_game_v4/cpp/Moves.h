#ifndef Moves_H
#define Moves_H

#include "include/configurable.h"

// Function to find the selected pawn to be moved
Pedina* findPedina(std::vector<Pedina*> *pawns, int x, int y)
{
  Pedina* tmp = new Pedina();
 
  for(unsigned int i=0; i<pawns->size(); i++)
    if(x == pawns->at(i)->getX() && y == pawns->at(i)->getY())
      tmp = pawns->at(i);

  return tmp;
}

// Function to delete eatend pawns
void erasePawns(std::vector<Pedina*> *pawns, std::string pos)
{
  char xStr  = ' ', yStr   = ' ';
  int xStart = 0  , yStart = 0;
  int xStop  = 0  , yStop  = 0;
  int med_x  = 0  , med_y  = 0;
  
  // Loop on positions string
  for (unsigned int istep = 1; istep<pos.size()/2; istep++)
  {
    // Get start and stop position for each iteration
    yStr = tolower(pos[istep*2-2]);
    xStr = tolower(pos[istep*2-1]);

    yStart = (int)(yStr - '0');
    xStart = (int)(xStr - 'a' + 1);

    yStr = tolower(pos[istep*2]);
    xStr = tolower(pos[istep*2+1]);

    yStop = (int)(yStr - '0');
    xStop = (int)(xStr - 'a' + 1);
    
    // Position of the eaten pawn
    med_x = (xStart + xStop)/2;
    med_y = (yStart + yStop)/2;
    
    // Delete eaten pawn from the vector
    for (unsigned int j=0; j<pawns->size(); j++)
      if (pawns->at(j)->getX() == med_x && pawns->at(j)->getY() == med_y)
        pawns->erase(pawns->begin() + j);
  }
}

// Function to change pawns into Pedone
void evolvePedina(std::vector<Pedina*> *pawns)
{
    // Loop on pawns
    for(unsigned int i=0; i<pawns->size(); i++)
    {
      // Only pawns can change, not the "big_pawns"
      if (typeid(*pawns->at(i)) != typeid(Pedina))
        continue;
      else
      {
        // Evolution od pawn to Pedone only when it arrives at the last row
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

// Function to update the board positions according to the 2 vectors of pawns
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

// Function to choose the best move for the CPU player
std::string ChooseBestMove(Moves moves)
{
  const int nMoves = moves.size();
  std::string best_move = "";
  char max_y = '0';
  unsigned int max_lenght = 0, max_diff = 0, diff = 0;

  for(int i=0; i<nMoves; i++)
    if(moves.at(i).size() > max_lenght)
      max_lenght = moves.at(i).size();	
  
  best_move = moves[0];
  return best_move;       
}

// Function to make the CPU make its move
std::string autoMove(std::vector<Pedina*> *pawns)
{
  // Vector with all possible moves for CPU player
  Moves moves;
  std::string best_move = "";

  // Loop on pawns
  for(unsigned int ipawn = 0; ipawn < pawns->size(); ipawn++)
    {
      // For each pawn get the possible moves (vec of strings)
      Moves tmp_moves;
      tmp_moves = pawns->at(ipawn)->CPUCheck();
      
      // Push each element of the possible moves in vec of all possible moves for CPU player
      for(unsigned int imove = 0; imove < tmp_moves.size(); imove++)
        moves.push_back(tmp_moves.at(imove));
    }

  // Get the best move for CPU player
  best_move = ChooseBestMove(moves);

  return best_move;
}



#endif // Moves_H
