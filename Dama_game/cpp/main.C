#include "Board.cc"
#include "Pedina.cc"
#include "Moves.h"

int main()
{
  Board board;
  
  std::string team = "";
  std::cin >> team;
  
  board.Initialize(team);
  
  std::string vec_positions;
  vec_positions = board.getPositions();
  std::cout << vec_positions;
  
  std::vector<Pedina*> Wpawn;
  std::vector<Pedina*> Bpawn;
  for(int i=0; i<Npawn; i++)
    {
      Pedina* temp = new Pedina();
      Wpawn.push_back(temp);
      Bpawn.push_back(temp);
    }
  
  int old_x = 0, old_y = 0, new_x = 0, new_y = 0;
  char old_xStr = ' ', old_yStr =  ' ', new_xStr = ' ', new_yStr = ' ';
  int endGame = 0;
  int allowed_move = 0;
  int eaten = 0;

  std::string val = "";
  std::string pos = "";

  while(endGame == 0)
    {
      
      std::cin >> pos;
      
      if(pos == "auto")
        board.autoMove('b');
      else
        {
	      old_yStr = tolower(pos[0]);
	      old_xStr = tolower(pos[1]);
	  
	      old_y = (int)(old_yStr - '0');
	      old_x = (int)(old_xStr - 'a' + 1);
      
	      new_yStr = tolower(pos[2]);
	      new_xStr = tolower(pos[3]);
	  
	      new_y = (int)(new_yStr - '0');
	      new_x = (int)(new_xStr - 'a' + 1);
          
          allowed_move = pedina_good_move(old_x, old_y, new_x, new_y, board);
          eaten        = eating_pedina(old_x, old_y, new_x, new_y, board);
          if (allowed_move != 1)
            {
              std::cout << board.getPositions();
            }
          else
            {
	          val = board.getStatus(old_x, old_y);
	          board.setStatus(old_x, old_y, " ");
      
	          board.setStatus(new_x, new_y, val);
              
              if (eaten == 1) board.setStatus(old_x+1, old_y+1, " ");
              if (eaten == 2) board.setStatus(old_x-1, old_y+1, " ");
              
            }
	    }
      
      if (allowed_move == 1)
      {
        std::string new_positions;
        new_positions = board.getPositions();
        std::cout << new_positions;
      }

      if(Wpawn.size() == 0 || Bpawn.size() == 0)
	    endGame = 1;
      else
        endGame = 0;
    
      std::cout << endGame << std::endl;
    }

  return 0;

}
