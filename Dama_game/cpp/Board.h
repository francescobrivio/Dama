#ifndef Board_H
#define Board_H

#include "include/configurable.h"

class Board
{
 public:
  Board();
  Board(const Board& origin);
  ~Board();
  
  Board& operator=(const Board& origin);

  void Initialize(std::string team);
  void setNmoves(int origin);
  int getNmoves() const;
  void setBoard(Matrix origin);
  Matrix getBoard() const;
  void setStatus(int nx, int ny, std::string value);
  char getStatus(int nx, int ny) const;
  std::string getAlpha(int idx) const;
  void autoMove(const char val);
  void Print(const char* name = "");
  void PrintPositions(const char* name = "");
  
  std::string getPositions();
    
 private:
  Matrix _board;
  int _nmoves;
};

#endif // Board_H
