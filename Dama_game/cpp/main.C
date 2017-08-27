#include "Board.cc"
#include "Pedina.cc"
//#include "Dama.cc"
//#include <unistd.h>
//#include <thread>
//#include <chrono>

int good_move( int old_x, int old_y, int new_x, int new_y, Board board)
{
    if      (old_x == new_x || old_y == new_y)      return 0; // only diagonal moves
 // else if (board.getStatus(old_x, old_y) != *"")  return 0; // move ony if the new cell is free
    else                                            return 1;
}

int main()
{
  Board board;
  
  std::string team = "";
  std::cin >> team;
  
  board.Initialize(team);
  //board.Print("");
  

  //std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // serve ancora?? mi sa di no..
  std::string vec_positions;
  vec_positions = board.getPositions();
  std::cout << vec_positions;// << std::endl;
  
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
  int move_validity = 0;

  std::string val = "";
  std::string pos = "";

  while(endGame == 0)
    {
      //std::cout << "Quale pedina vuoi muovere?  (Es: A3)" << std::endl;
      //std::cout << "Dove la vuoi muovere? " << std::endl;
      
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
          
          move_validity = good_move( old_x, old_y, new_x, new_y, board);
          if (move_validity != 1)
          {
            //std::string old_positions;
            //old_positions = board.getPositions();
            //std::cout << old_positions;
            std::cout << board.getPositions();
          }
          else
          {
	        val = board.getStatus(old_x, old_y);
	        board.setStatus(old_x, old_y, " ");
      
	        board.setStatus(new_x, new_y, val);
	        //std::cout << pos << std::endl;
          }
	    }
      //board.Print("");
      //board.PrintPositions("positions.txt");
      
      if (move_validity == 1)
      {
        std::string new_positions;
        new_positions = board.getPositions();
        std::cout << new_positions;// << std::endl;
      }

      if(Wpawn.size() == 0 || Bpawn.size() == 0)
	    endGame = 1;
      else
        endGame = 0;
    
      std::cout << endGame << std::endl;
    }

  return 0;

}


/*                                                                                                                                                          
      char buffer[10];
      int tmp = 0;  
      tmp = sprintf (buffer, "%d", cazz);    
      std::cout << "ndosnfomsofos       " << buffer << std::endl; 
*/
