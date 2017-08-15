#include "Board.cc"
#include "Pedina.cc"
//#include "Dama.cc"
//#include <unistd.h>
//#include <thread>
//#include <chrono>

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
  
  int x = 0, y = 0;
  char xStr = ' ', yStr =  ' ';
  int endGame = 0;

  std::string val = "";
  std::string pos = "";

  while(endGame == 0)
    {
      //std::cout << "Quale pedina vuoi muovere?  (Es: A3)" << std::endl;
      //std::cout << "Dove la vuoi muovere? " << std::endl;
      
      std::cin >> pos;
      
      if(pos == "auto")
	pos = board.autoMove();
      
      yStr = tolower(pos[0]);
      xStr = tolower(pos[1]);
      
      y = (int)(yStr - '0');
      x = (int)(xStr - 'a' + 1);
      
      val = board.getStatus(x, y);
      board.setStatus(x, y, " ");
      
      yStr = tolower(pos[2]);
      xStr = tolower(pos[3]);
	  
      y = (int)(yStr - '0');
      x = (int)(xStr - 'a' + 1);
      
      board.setStatus(x, y, val);
      //std::cout << pos << std::endl;
   
      //board.Print("");
      //board.PrintPositions("positions.txt");
      
      std::string new_positions;
      new_positions = board.getPositions();
      std::cout << new_positions;// << std::endl;

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
