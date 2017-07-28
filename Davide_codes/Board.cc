#include "Board.h"
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
//#include <TRandom3.h>

Board::Board()
{
  for(Int_t nx=0; nx<N; nx++)
    for(Int_t ny=0; ny<N; ny++)
      {
	/*
	if(ny<3 && nx%2==0)
	  this->setStatus(nx, ny, 1);
	else if(ny>4 && (nx+1)%2==0)
          this->setStatus(nx, ny, -1);
	else
	this->setStatus(nx, ny, 0);*/
	_board[nx][ny] = 0;
      }
  
}

Board::Board(Int_t** board)
{
  /*for(Int_t nx=0; nx<N; nx++)
    for(Int_t ny=0; ny<N; ny++)
      {
	value = *board[nx][ny];
	this->setStatus(nx, ny, value);
	}*/

  _board = *board;
}

Board::Board(const Board& origin)
{
  for(Int_t nx=0; nx<N; nx++)
    for(Int_t ny=0; ny<N; ny++)
      {
	value = origin[nx][ny];
	this->setStatus(nx, ny, value);
      }
}

Board& Board::operator= (const Board& origin)
{
  if (&origin == this) return *this;

  this->Board::operator=(origin);
  
  return *this;
}

Board::~Board()
{
}

void setStatus(Int_t nx, Int_t ny; Int_t value)
{
  _board[nx][ny] = value;  
}

Int_t getStatus(Int_t nx, Int_t ny)
{
  return _board[nx][ny];
}

void Print(TString name)
{
  std::ofstream output(name, std::ofstream::out);
  
  for(Int_t ny=0; ny<N; ny++)
    for(Int_t nx=0; nx<N; nx++)
      if(name != "")
	output << this->getStatus(nx, ny);
      else
	std::cout << this->getStatus(nx, ny);
  
  output.close();
}
