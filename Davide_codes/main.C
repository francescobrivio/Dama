#include "Board.cc"
#include "Pedina.cc"
//#include "Dama.cc"
//#include "Player.cc"
#include <unistd.h>
#include <thread>
#include <chrono>

int main()
{
  Board board;
  //Player cpu1;
  //Player cpu2;
  
  std::string team="";
  std::cin >> team;
  
  board.Initialize();
  //board.Print("");
  

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::string vec_positions;
  vec_positions = board.getPositions();
  std::cout << vec_positions << std::endl;
  
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
  bool endGame = false;

  std::string val = "";
  std::string pos = "";

  while(!endGame)
    {
      std::cout << "Quale pedina vuoi muovere?  (Es: A3)" << std::endl;
      std::cout << "Dove la vuoi muovere? " << std::endl;
      std::cin >> pos;

      xStr = tolower(pos[0]);
      yStr = tolower(pos[1]);
      
      y = (int)(yStr - '0');
      x = (int)(xStr - 'a' + 1);
      
      val = board.getStatus(x, y);
      board.setStatus(x, y, " ");
      
      xStr = tolower(pos[2]);
      yStr = tolower(pos[3]);

      y = (int)(yStr - '0');
      x = (int)(xStr - 'a' + 1);

      board.setStatus(x, y, val);
      std::cout << pos << std::endl;
      
      //board.Print("");
      //board.PrintPositions("positions.txt");
      
      std::cout << "GREAT!!!!" << std::endl;

      if(Wpawn.size() == 0 || Bpawn.size() == 0)
	endGame = true;
    }

  return 0;

}


/*                                                                                                                                                          
      char buffer[10];
      int tmp = 0;  
      tmp = sprintf (buffer, "%d", cazz);    
      std::cout << "ndosnfomsofos       " << buffer << std::endl; 
*/
