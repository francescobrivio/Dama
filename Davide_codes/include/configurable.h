#ifndef configurable_H
#define configurable_H

#define N 9
#define Nmoves_pedina 2
#define Nmoves_dama 4

#include "cppinclude.h"

typedef std::pair<int, int> Position; 
typedef std::vector<std::pair<Position, std::string> > Moves;
typedef std::vector<std::vector<std::string> > Matrix;

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
