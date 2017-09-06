#include "Board.cc"
#include "Pedina.cc"
#include "Pedone.cc"
#include "Moves.h"

int main(int argc, char *argv[])
{
  srand(time(NULL));

  Board board;
  
  std::string p1team = "";
  std::string p2team = "";
  std::cin >> p1team;
  
  if(p1team == "white")
    p2team = "black";
  else 
    p2team = "white";
  
  board.Initialize(p1team);
  
  std::string vec_positions;
  vec_positions = board.getPositions();
  std::cout << vec_positions;
  
  std::vector<Pedina*> *P1pawns = new std::vector<Pedina*>;
  std::vector<Pedina*> *P2pawns = new std::vector<Pedina*>;
  
  std::string turn = "";
  std::string player_flag = "";
    
  for(unsigned int i=0; i<vec_positions.size(); i++)
    {
      int nrow = i/(Nslots-1)+1;
      int ncol = i%(Nslots-1)+1;

      if(tolower(vec_positions[i]) == p1team[0])
        P1pawns->push_back(new Pedina(p1team, ncol, nrow, &board, 1));
      else if(tolower(vec_positions[i]) == p2team[0])
        P2pawns->push_back(new Pedina(p2team, ncol, nrow, &board, -1));
    }      
      
  int x = 0, y = 0;
  char xStr = ' ', yStr =  ' ';
  int endGame = 0;
  bool flag_move = false;
  bool isCPU_log = false;
  
  std::string pos = "";

  int tmp_indx = -1;
  Pedina* tmp_pawn = new Pedina();

  //Moves moves;
  while(endGame == 0)
    {
      board.setNmoves(board.getNmoves()+1);

      if(board.getNmoves()%2==1)
        turn = "white";
      else
        turn = "black";

      std::cin >> pos;
      
      if(pos == "auto")
        {
          isCPU_log = true;
          if(turn == P1pawns->at(0)->getColor())
            pos = autoMove(P1pawns);
          else if(turn == P2pawns->at(0)->getColor())
            pos = autoMove(P2pawns);
        }

      //std::cout << " auto pos: " << pos <<std::endl;

      if(pos == "none")
        endGame = 1;
      
      if(endGame == 0)
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
           
          // Log to know who is playing, player or PC?
          if (isCPU_log == true)
            player_flag = "auto";
          else
            player_flag = tmp_pawn->getColor();

          // Check if the move is allowed
          if(tolower(tmp_pawn->getColor()[0]) == turn[0])
            {
              flag_move = tmp_pawn->CheckMove(pos);

              if(flag_move)
                {
                  // Read the new position
                  yStr = tolower(pos[pos.size()-2]);
                  xStr = tolower(pos[pos.size()-1]);
		  
                  y = (int)(yStr - '0');
                  x = (int)(xStr - 'a' + 1);
		  
                  // Move the pawn
                  tmp_pawn->Move(x, y);

                  if(turn == P1pawns->at(0)->getColor())
                    //P2pawns = erasePawns(P2pawns, pos);
                    erasePawns(P2pawns, pos);
                  else if(turn == P2pawns->at(0)->getColor())
                    //P1pawns = erasePawns(P1pawns, pos);
                    erasePawns(P1pawns, pos);
                }
              else
                {
                  board.setNmoves(board.getNmoves()-1);
                  flag_move = false;
                }
            }
          else
            {
              board.setNmoves(board.getNmoves()-1);
              flag_move = false;
          }
        }
   
      // Change pawns into big_pawns
      if(turn == P1pawns->at(0)->getColor())
        evolvePedina(P1pawns);
      else if(turn == P2pawns->at(0)->getColor())
        evolvePedina(P2pawns);

      // Update the board positions
      updatePositions(&board, P1pawns, P2pawns);

      // Pass the new board positions to perl (cpp thread)
      std::cout << pos <<std::endl;
      std::cout << flag_move << player_flag[0] <<std::endl;
      std::string new_positions;
      new_positions = board.getPositions();
      std::cout << new_positions;

      if(P2pawns->size() == 0 || P1pawns->size() == 0)
        endGame = 1;
          
      std::cout << endGame << std::endl;
      
      isCPU_log = false;
    }
  
  return 0;
}
  
