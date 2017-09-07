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

  // Return pawn if found, else return NULL (i.e. when the starting position was empty)
  if (tmp->getColor() == "red")
    return NULL;
  else
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
  
  // Begin with all empty positions
  for(int nx=Nslots-1; nx>0; nx--)                                                                                                                    
    for(int ny=1; ny<Nslots; ny++) 
      board->setStatus(nx, ny, " ");

  // Fill board with the first team
  for(unsigned int i=0; i<P1pawns->size(); i++)
    {      
      x = P1pawns->at(i)->getX();
      y = P1pawns->at(i)->getY();
      color = (P1pawns->at(i)->getColor())[0];

      board->setStatus(x, y, color);      
    }  

  // Fill the board with the second team
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

  // Loop on the possible moves 
  for(int i=0; i<nMoves; i++)
    // Look for the maximum move lenght -> longer means that it eats more pawns 
    if(moves.at(i).size() > max_lenght)
      max_lenght = moves.at(i).size();
  
  // Loop on the possible moves
  for(int i=0; i<nMoves; i++)
    {
      // If the lenght is different from the maximum then continue
      // i.e. take only the longest moves
      if(moves.at(i).size() != max_lenght)
        continue;

      // else evaluate the difference long the y axis
      diff = abs(moves.at(i)[max_lenght-2]-moves.at(i)[0]);

      // Look for the best move
      // If diff is greater than max_diff, it means that I'm eating more pawns
      // So this should be my best move
      if(diff > max_diff)
        {
          max_diff = diff;
          best_move = moves.at(i);
          max_y = best_move[0];
        }
      // else if diff is equal to the maximum, then I'm eating the same 
      // number of pawns
      else if(diff == max_diff)
        {
          // first I choose the one that has the higher y,
          // i.e. the one that is more advanced
          if(moves.at(i)[0] > max_y)
            {
              best_move = moves.at(i);
              max_y = best_move[0];
            }
        }
      }
  
  // If the lenght of the best move is equal to 2 it means that 
  // I'm not moving anything, so I have lost
  if(best_move.size() == 2)
    best_move = "none";

  return best_move;       
}

// Function to choose the best move for the CPU player
std::string ChooseBestMoveRand(Moves moves)
{
  std::string best_move = "";
  Moves eating_moves, longer_moves;
  unsigned int max_lenght = 0;
  int max_diff = 0, diff = 0;

  // Find the longest moves, i.e. that eat more pawns
  for (unsigned int i=0; i<moves.size(); i++)
    {
      if (moves.at(i).size() > max_lenght)
        max_lenght = moves.at(i).size();
    }
    
  // Fill eating_moves with all moves that have same lenght == max_lenght
  for (unsigned int j=0; j<moves.size(); j++)
    {
      if (moves.at(j).size() == max_lenght)
        eating_moves.push_back(moves.at(j));
    }

  if (eating_moves.size() == 1)
    best_move = eating_moves[0];
  else
    {
      // Find the longest diff, i.e. pawns that go
      for (unsigned int k=0; k<eating_moves.size(); k++)
        {
          diff = abs(eating_moves.at(k)[max_lenght-2]-eating_moves.at(k)[0]);
          if (diff > max_diff)
            max_diff = diff;
        }
      // Fill longer_moves with moves with longest diff
      for (unsigned int h=0; h<eating_moves.size(); h++)
        {
          if(abs(eating_moves.at(h)[max_lenght-2]-eating_moves.at(h)[0]) == max_diff)
            longer_moves.push_back(eating_moves.at(h));
        }
        
      if (longer_moves.size() == 1)
        best_move = longer_moves[0];
      else
        best_move = longer_moves.at( rand()%(longer_moves.size()) );
    }

  if(best_move.size() == 2)
    best_move = "none";

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
  //best_move = ChooseBestMove(moves);
  best_move = ChooseBestMoveRand(moves);

  return best_move;
}



#endif // Moves_H
