#include "Board.cc"
#include "Pedina.cc"

Pedina* findPedina(std::vector<Pedina> *pawns, int x, int y);
void updatePositions(Board* board, std::vector<Pedina> *P1pawns, std::vector<Pedina> *P2pawns);
std::vector<Pedina>* erasePawns(std::vector<Pedina> *pawns, std::string move);
std::string autoMove(std::vector<Pedina> *pawns);
std::string ChooseBestMove(Moves moves);

int main(int argc, char *argv[])
{
  Board board;
  
  std::string p1team = "";
  std::string p2team = "";
  std::cin >> p1team;
  
  if(p1team == "white")
    p2team = "black";
  else 
    p2team = "white";
  
  board.Initialize(p1team);

  std::string turn = "";
  std::string player_flag = "";

  std::string vec_positions;
  vec_positions = board.getPositions();
  std::cout << vec_positions;
  
  std::vector<Pedina> *P1pawns = new std::vector<Pedina>;
  std::vector<Pedina> *P2pawns = new std::vector<Pedina>;
    
  for(unsigned int i=0; i<vec_positions.size(); i++)
    {
      int nrow = i/(Nslots-1)+1;
      int ncol = i%(Nslots-1)+1;

      if(vec_positions[i] == p1team[0])
      {
        Pedina temp(p1team, ncol, nrow, &board, 1);
        P1pawns->push_back(temp);
      }
      else if(vec_positions[i] == p2team[0])
      {
        Pedina temp(p2team, ncol, nrow, &board, -1);
        P2pawns->push_back(temp);
      }
    }

  int x = 0, y = 0;
  char xStr = ' ', yStr =  ' ';
  int endGame = 0;
  bool flag_move = false;

  std::string val = "";
  std::string pos = "";

  Pedina* tmp_pawn = new Pedina();
  Moves moves; 
  while(endGame == 0)
    {
      board.setNmoves(board.getNmoves()+1);

      if(board.getNmoves()%2==1)
        turn = "white";
      else
        turn = "black";

      std::cin >> pos;
      
      if(pos == "auto")
        if(turn == P1pawns->at(0).getColor())
          pos = autoMove(P1pawns);
        else if(turn == P2pawns->at(0).getColor())
          pos = autoMove(P2pawns);

      if(pos == "none")
        endGame = 1;
      
      if(endGame == 0)
        {
          yStr = tolower(pos[0]);
          xStr = tolower(pos[1]);
	  
          y = (int)(yStr - '0');
          x = (int)(xStr - 'a' + 1);
	  
          if(turn == P1pawns->at(0).getColor())
            tmp_pawn = findPedina(P1pawns, x, y);
          else if(turn == P2pawns->at(0).getColor())
            tmp_pawn = findPedina(P2pawns, x, y);

          if(tmp_pawn->getColor() == turn)
            {
              flag_move = tmp_pawn->CheckMove(pos);
              player_flag = tmp_pawn->getColor();

              if(flag_move)
                {
                  yStr = tolower(pos[pos.size()-2]);
                  xStr = tolower(pos[pos.size()-1]);
		  
                  y = (int)(yStr - '0');
                  x = (int)(xStr - 'a' + 1);
		  
                  tmp_pawn->Move(x, y);
		  
                  if(turn == P1pawns->at(0).getColor())
                    P2pawns = erasePawns(P2pawns, pos);
                  else if(turn == P2pawns->at(0).getColor())
                    P1pawns = erasePawns(P1pawns, pos);
                }
              else
                {
                  //std::cout << "ERROR: Mossa non consentita!" << std::endl;
                  board.setNmoves(board.getNmoves()-1);
                  flag_move = false;
                }
            }
          else
            {
              //std::cout << "ERROR: Non puoi muovere le pedine avversarie!" << std::endl;
              board.setNmoves(board.getNmoves()-1);
              flag_move = false;
          }
        }
      
      updatePositions(&board, P1pawns, P2pawns);

      std::string new_positions;
      new_positions = board.getPositions();
      std::cout << flag_move << player_flag[0] <<std::endl;
      std::cout << new_positions;

      if(P2pawns->size() == 0 || P1pawns->size() == 0)
        endGame = 1;
          
      std::cout << endGame << std::endl;
    }

  return 0;
}


Pedina* findPedina(std::vector<Pedina> *pawns, int x, int y)
{
  Pedina* tmp = new Pedina();
 
  for(unsigned int i=0; i<pawns->size(); i++)
    if(x == pawns->at(i).getX() && y == pawns->at(i).getY())
      tmp = &pawns->at(i);
   
  return tmp;
}

std::vector<Pedina>* erasePawns(std::vector<Pedina> *pawns, std::string move)
{
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
    if (med_x == pawns->at(i).getX() && med_y == pawns->at(i).getY())
      pawns->erase(pawns->begin() + i);
  
  return pawns;
}


void updatePositions(Board* board, std::vector<Pedina> *P1pawns, std::vector<Pedina> *P2pawns)
{
  int x = 0, y = 0;
  
  std::string color = "";  
  
  for(int nx=Nslots-1; nx>0; nx--)                                                                                                                    
    for(int ny=1; ny<Nslots; ny++) 
      board->setStatus(nx, ny, " ");

  for(unsigned int i=0; i<P1pawns->size(); i++)
    {      
      x = P1pawns->at(i).getX();
      y = P1pawns->at(i).getY();
      color = (P1pawns->at(i).getColor())[0];

      board->setStatus(x, y, color);      
    }  

  for(unsigned int i=0; i<P2pawns->size(); i++)
    {
      x = P2pawns->at(i).getX();
      y = P2pawns->at(i).getY();
      color = (P2pawns->at(i).getColor())[0];

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

