#ifndef Board_H
#define Board_H

#include "configurable.h"
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

class Board:
{
 public:
  Board();
  Board(Int_t**);
  Board(const Board& origin);
  ~Board();
  
  Board& operator=(const Board& origin);

  void setStatus(Int_t nx, Int_t ny, Int_t value);
  Int_t getStatus(Int_t nx, Int_t ny);
  void Print(TString name = "");
  //void Draw();
  //Int_t isFree(Int_t x, Int_t y); 
  
  //private:
  Int_t _board[N][N];

};

#endif // Board_H
