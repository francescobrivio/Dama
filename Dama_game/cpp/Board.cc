#include "include/cppinclude.h"
#include "include/configurable.h"
#include "Board.h"

Board::Board()
{
  _board.resize(Nslot);
  for(int ny=0; ny<Nslot; ny++)
    for(int nx=0; nx<Nslot; nx++)
    {
      _board[nx].resize(Nslot);
      _board[nx][ny] = " ";
    }
  _nmoves = 0;
}

Board::Board(const Board& origin):
  _board (origin.getBoard()),
  _nmoves (origin.getNmoves())
{
}

Board& Board::operator= (const Board& origin)
{
  if (&origin == this) return *this;

  this->Board::operator=(origin);
  
  this->setBoard(origin.getBoard());
  this->setNmoves(origin.getNmoves());
  
  return *this;
}

Board::~Board()
{
}

void Board::Initialize(std::string team)
{
  char buffer[10];
  int tmp = 0;
  for(int n=1; n<Nslot; n++)
    {
      tmp = sprintf (buffer, "%d", n);
      this->setStatus(0, n, buffer);
      this->setStatus(n, 0, this->getAlpha(n));
    }

  if (team == "white")
  {
    for(int nx=Nslot-1; nx>0; nx--) // colonne
      for(int ny=1; ny<Nslot; ny++) // righe
        {
          if(ny<4 && (ny+nx)%2==0)
            this->setStatus(nx, ny, "w");
          else if(ny>5 && (nx+ny)%2==0)
            this->setStatus(nx, ny, "b");
	      else
            this->setStatus(nx, ny, " ");
        }
  }
  else
  {
    for(int nx=Nslot-1; nx>0; nx--) // colonne
      for(int ny=1; ny<Nslot; ny++) // righe
        {
          if(ny<4 && (ny+nx)%2==0)
            this->setStatus(nx, ny, "b");
          else if(ny>5 && (nx+ny)%2==0)
            this->setStatus(nx, ny, "w");
	      else
            this->setStatus(nx, ny, " ");
        }
  }
  
}

void Board::setBoard(Matrix origin)
{
  _board = origin;
}

Matrix Board::getBoard() const
{
  return _board;
}

void Board::setNmoves(int origin)
{
  _nmoves = origin;
}

int Board::getNmoves() const
{
  return _nmoves;
}

void Board::setStatus(int nx, int ny, std::string value)
{
  _board[nx][ny] = value;  
}

char Board::getStatus(int nx, int ny) const
{
  return (_board[nx][ny])[0];
}

std::string Board::getAlpha(int idx) const
{
  std::map<int, std::string> numToAlpha;
  numToAlpha.insert(std::pair<int, std::string>(1, "A"));
  numToAlpha.insert(std::pair<int, std::string>(2, "B"));
  numToAlpha.insert(std::pair<int, std::string>(3, "C"));
  numToAlpha.insert(std::pair<int, std::string>(4, "D"));
  numToAlpha.insert(std::pair<int, std::string>(5, "E"));
  numToAlpha.insert(std::pair<int, std::string>(6, "F"));
  numToAlpha.insert(std::pair<int, std::string>(7, "G"));
  numToAlpha.insert(std::pair<int, std::string>(8, "H"));

  std::string temp = numToAlpha[idx];
  return temp;
}

void Board::autoMove(const char team)
{
  int tmp = 0;
  std::string val = "";
  bool flag = false;
  srand (time(NULL));

  for(int ny=Nslot-1; ny>=0; ny--) // colonne      
    {
      if(flag)
	break;
      
      for(int nx=0; nx<Nslot; nx++) // righe            
	{
	  if(this->getStatus(nx, ny) != team)
	    continue;

	  tmp = rand() % 100 + 1;
	  
	  if(tmp < 81)
	    continue;
	  
	  val = this->getStatus(nx, ny);
	  this->setStatus(nx, ny-1, val);
	  this->setStatus(nx, ny, " ");	  
	  
	  flag = true;
	  break;
	}
    }
}
void Board::Print(const char* name)
{
  std::ofstream output(name);
  
  if(name != "")
    output << "************************" << std::endl << std::endl;
  else
    std::cout << "************************" << std::endl << std::endl;

  for(int ny=Nslot-1; ny>=0; ny--) // colonne   
    {
      for(int nx=0; nx<Nslot; nx++) // righe   
	if(name != "")
	  output << this->getStatus(nx, ny) << "  ";
	else
	  std::cout << this->getStatus(nx, ny) << "  ";
      std::cout << std::endl;
    }
  
  if(name != "")
    output << std::endl << "************************" << std::endl;
  else
    std::cout << std::endl << "************************" << std::endl;

  output.close();
}

void Board::PrintPositions(const char* name)
{
  std::ofstream output(name);
  char val = ' ';

  if(name != "")
    {
      for(int ny=Nslot-1; ny>0; ny--) // colonne 
	for(int nx=1; nx<Nslot; nx++) // righe 
	  {
	    val = this->getStatus(nx, ny);
	    if(val == ' ')
	      val = 'e';
	    output << this->getAlpha(nx) << ny << " " << val << std::endl;
	  }
    }
}


std::string Board::getPositions()
{
    std::string output_vec;
    char val=' ';
    
    for(int ny=1; ny<Nslot; ny++)
        for(int nx=1; nx<Nslot; nx++)
            {
                val = this->getStatus(nx, ny);
                if(val == ' ')
                val = 'e';
                output_vec += val;
            }
    output_vec += "\n";
    
    return output_vec;
}




