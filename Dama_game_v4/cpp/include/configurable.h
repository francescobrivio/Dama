#ifndef configurable_H
#define configurable_H

#define Nslots 9
#define Npawns 12
#define Nplayers 2
#define Nmoves_pedina 2
#define Nmoves_pedone 2
#define Nmatch 100

#include "cppinclude.h"

typedef std::pair<int, int> Position; 
typedef std::vector<std::string> Moves;
typedef std::vector<std::vector<std::string> > Matrix;

std::string intToString(int i)
{
  std::stringstream ss;
  std::string s;
  ss << i;
  s = ss.str();

  return s;
}

/*std::map<Int_t, TString> numToAlpha;
numToAlpha[1] = "A";
numToAlpha[2] = "B";
numToAlpha[3] = "C";
numToAlpha[4] = "D";
numToAlpha[5] = "E";
numToAlpha[6] = "F";
numToAlpha[7] = "G";
numToAlpha[8] = "H";
*/

#endif
