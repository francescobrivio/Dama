#ifndef Moves_H
#define Moves_H

#include "include/configurable.h"

// Forward declaration of the implemented functions
Pedina* findPedina(std::vector<Pedina*>*, int, int);
void erasePawns(std::vector<Pedina*>*, std::string);
void evolvePedina(std::vector<Pedina*>*);
void updatePositions(Board*, std::vector<Pedina*>*, std::vector<Pedina*>*);
std::string ChooseBestMoveRand(Moves);
Moves SelectMoves(Moves);
std::string ChooseBestMoveAI(Moves, std::string, std::string, int);
std::string autoMove(std::vector<Pedina*>*, bool);




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
      if (typeid(pawns->at(i)) != typeid(Pedina*))
        continue;
      else
      {
        // Evolution od pawn to Pedone only when it arrives at the last row
        if (pawns->at(i)->getY()+pawns->at(i)->getDir() < 1 || pawns->at(i)->getY()+pawns->at(i)->getDir() > 8)
        {
          // Pushback a new Pedone
          if(pawns->at(i)->getColor()[0] == 'w')
            pawns->push_back( new Pedone("White", pawns->at(i)->getX(), pawns->at(i)->getY(), pawns->at(i)->getBoard()) );
          else if (pawns->at(i)->getColor()[0] == 'b')
            pawns->push_back( new Pedone("Black", pawns->at(i)->getX(), pawns->at(i)->getY(), pawns->at(i)->getBoard()) );

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
std::string ChooseBestMoveRand(Moves moves)
{
  std::string best_move = "none";
  Moves eating_moves, longer_moves;
  unsigned int max_lenght = 0;
  int max_diff = 0, diff = 0;

  // Find the longest moves, i.e. that eat more pawns
  for (unsigned int i=0; i<moves.size(); i++)
    if (moves.at(i).size() > max_lenght)
      max_lenght = moves.at(i).size();
    
  // Fill eating_moves with all moves that have same lenght == max_lenght
  for (unsigned int j=0; j<moves.size(); j++)
    if (moves.at(j).size() == max_lenght)
      eating_moves.push_back(moves.at(j));

  if (eating_moves.size() == 0)
    best_move = "none";
  else if (eating_moves.size() == 1)
    best_move = eating_moves.at(0);
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
	if(abs(eating_moves.at(h)[max_lenght-2]-eating_moves.at(h)[0]) == max_diff)
	  longer_moves.push_back(eating_moves.at(h));
      
      if (longer_moves.size() == 1)
        best_move = longer_moves.at(0);
      else
	best_move = longer_moves.at(rand()%(longer_moves.size()));
    }

  if(best_move.size() == 2)
    best_move = "none";

  return best_move;       
}

// Function to select the more useful moves for the CPU player                                                                                                    
Moves SelectMoves(Moves moves)
{
  Moves eating_moves, longer_moves;
  unsigned int max_lenght = 0;
  int max_diff = 0, diff = 0;

  // Find the longest moves, i.e. that eat more pawns                                                                                                             
  for (unsigned int i=0; i<moves.size(); i++)
    if (moves.at(i).size() > max_lenght)
      max_lenght = moves.at(i).size();

  // Fill eating_moves with all moves that have same lenght == max_lenght                                                                                         
  for (unsigned int j=0; j<moves.size(); j++)
    if (moves.at(j).size() == max_lenght)
      eating_moves.push_back(moves.at(j));

  // Find the longest diff, i.e. pawns that go                                                                                                                    
  for (unsigned int k=0; k<eating_moves.size(); k++)
    {
      diff = abs(eating_moves.at(k)[max_lenght-2]-eating_moves.at(k)[0]);
      if (diff > max_diff)
	max_diff = diff;
    }
  // Fill longer_moves with moves with longest diff                                                                                                               
  for (unsigned int h=0; h<eating_moves.size(); h++)
    if(abs(eating_moves.at(h)[max_lenght-2]-eating_moves.at(h)[0]) == max_diff)
      longer_moves.push_back(eating_moves.at(h));

  return longer_moves;
}

std::string ChooseBestMoveAI(Moves moves, 
			     std::string positions, 
			     std::string team,
			     int dir)
{
  std::string best_move = "none";
  std::string team2 = "", pos = "";
  std::string test_move = "";
  std::string team_tmp = "";

  char xStr  = ' ', yStr   = ' ';
  int x = 0, y = 0, imove = 0;
  int val = 0, max_val = -Nmatch;
  std::map<std::string, int> list_moves;
  bool endgame = false;
  bool flag_move = true;

  if(team == "white")
    team2 = "black";
  else
    team2 = "white";

  Board board;
  std::string vec_positions;

  std::vector<Pedina*> *P1pawns = new std::vector<Pedina*>;
  std::vector<Pedina*> *P2pawns = new std::vector<Pedina*>;

  std::string turn = "";

  Pedina* tmp_pawn = new Pedina();

  for(unsigned int idx = 0; idx < moves.size(); idx++)
    list_moves.insert(std::pair<std::string, int>(moves[idx], val));

  for(int imatch = 0; imatch < Nmatch; imatch++)
    {
      imove = rand() % moves.size();
      test_move = moves[imove];
      flag_move = true;
      endgame = false;

      P1pawns->clear();
      P2pawns->clear();
      
      board.setNmoves(0);
      board.setPositions(positions);
      vec_positions = board.getPositions();

      for(unsigned int i=0; i<vec_positions.size(); i++)
	{
	  int nrow = i/(Nslots-1)+1;
	  int ncol = i%(Nslots-1)+1;
	  
	  if(vec_positions[i] == 'w') team_tmp = "white";
	  else if(vec_positions[i] == 'W') team_tmp = "White";
	  else if(vec_positions[i] == 'b') team_tmp = "black";
	  else if(vec_positions[i] == 'B') team_tmp = "Black";

	  if(vec_positions[i] == team[0])
	    P1pawns->push_back(new Pedina(team_tmp, ncol, nrow, &board, dir));
	  else if(tolower(vec_positions[i]) == team[0])
	    P1pawns->push_back(new Pedone(team_tmp, ncol, nrow, &board));
	  else if(vec_positions[i] == team2[0])
	    P2pawns->push_back(new Pedina(team_tmp, ncol, nrow, &board, -dir));
	  else if(tolower(vec_positions[i]) == team2[0])
	    P2pawns->push_back(new Pedone(team_tmp, ncol, nrow, &board));
	}
        
      while(!endgame)
	{
	  board.setNmoves(board.getNmoves()+1);
	  
	  // Whose turn is it?  
	  if(board.getNmoves()%2==1)
	    turn = team;
	  else
	    turn = team2;

	  if(board.getNmoves()==1)
	    pos = test_move;
	  else if(turn[0] == tolower(P1pawns->at(0)->getColor()[0]))
	    pos = autoMove(P1pawns, true);
	    //std::cin >> pos;
	  else if(turn[0] == tolower(P2pawns->at(0)->getColor()[0]))
	    pos = autoMove(P2pawns, true);
	    //std::cin >> pos;

	  if(pos == "none")
	    {
	      endgame = true;
	      flag_move = false;
	      if(turn == team)
		list_moves[test_move] -= 1;
	      else
		list_moves[test_move] += 1;
	    }

	  if(flag_move)
	    {
	      // Read starting position  
	      yStr = tolower(pos[0]);
	      xStr = tolower(pos[1]);

	      y = (int)(yStr - '0');
	      x = (int)(xStr - 'a' + 1);

	      // Select the correct pawn  
	      if(turn[0] == tolower(P1pawns->at(0)->getColor()[0]))
		tmp_pawn = findPedina(P1pawns, x, y);
	      else if(turn[0] == tolower(P2pawns->at(0)->getColor()[0]))
		tmp_pawn = findPedina(P2pawns, x, y);

	      // Read the new position   
	      yStr = tolower(pos[pos.size()-2]);
	      xStr = tolower(pos[pos.size()-1]);
	      
	      y = (int)(yStr - '0');
	      x = (int)(xStr - 'a' + 1);
	      
	      // Move the pawn   
	      tmp_pawn->Move(x, y);
	      
	      // Change pawns into big_pawns 
	      if(turn == P1pawns->at(0)->getColor())
		evolvePedina(P1pawns);
	      else if(turn == P2pawns->at(0)->getColor())
		evolvePedina(P2pawns);
	      
	      if(turn[0] == tolower(P1pawns->at(0)->getColor()[0]))
		erasePawns(P2pawns, pos);
	      else if(turn[0] == tolower(P2pawns->at(0)->getColor()[0]))
		erasePawns(P1pawns, pos);
	    }

	  // Update the board positions  
	  updatePositions(&board, P1pawns, P2pawns);
	    
	  if(P2pawns->size() == 0 || P1pawns->size() == 0)
	    {
	      endgame = true;
	      if(P1pawns->size() == 0)
		list_moves[test_move] -= 1;
	      else
		list_moves[test_move] += 1;
	    }
	}
    }

  std::map<std::string,int>::iterator it = list_moves.begin();
  for (it=list_moves.begin(); it!=list_moves.end(); ++it)
    {
      if(it->second > max_val)
	{
	  max_val = it->second;
	  best_move = it->first;
	}
    }

  return best_move;
}

// Function to make the CPU make its move   
std::string autoMove(std::vector<Pedina*> *pawns, bool flag_sim = false)
{
  // Vector with all possible moves for CPU player   
  Moves moves, longer_moves;
  std::string best_move = "none";
  std::string team = "", positions = "";
  int dir = 0;

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
  if(flag_sim)
    best_move = ChooseBestMoveRand(moves);
  else
    {
      team = pawns->at(0)->getColor();
      if(team == "White") team = "white";
      else if (team == "Black") team = "black";

      positions = pawns->at(0)->getBoard()->getPositions();
      dir = pawns->at(0)->getDir();

      longer_moves = SelectMoves(moves);
      best_move = ChooseBestMoveAI(longer_moves, positions, team, dir);
    }

  return best_move;
}


#endif // Moves_H
