#ifndef Moves_H
#define Moves_H

#include "include/configurable.h"


// Moves permitted to PEDINA
int pedina_good_move (int old_x, int old_y, int new_x, int new_y, Board board) //,player1/player2 -> così so devo muovermi avanti o indietro e che pedine posso muovere
{
    // Same line/column check
    if      (old_x == new_x || old_y == new_y)      return 0; // only diagonal moves

    // Right Direction check
    else if (old_y > new_y)                         return 0; // only forward moves --------------------------------> ????????? but what about the other team ??????????
    else if (new_y > old_y+2)                       return 0; // can't jump three lines forward (max is 2 for eating another pedina) -->   ????? same problem ???????

    // Right cell check
    else if (new_x == old_x+2 && new_y == old_y+1)  return 0; // can't jump to different color cells    -->   ????? same problem ???????
    else if (new_x == old_x+1 && new_y == old_y+2)  return 0; //                                        -->   ????? same problem ???????
    else if (new_x == old_x-2 && new_y == old_y+1)  return 0; //                                        -->   ????? same problem ???????
    else if (new_x == old_x-1 && new_y == old_y+2)  return 0; //                                        -->   ????? same problem ???????
    
    // Empty cell check
    else if (board.getStatus(new_x, new_y) != ' ')  return 0; // move ony if the new cell is free
    
    else                                            return 1; // GOOD move!
}

// Moves permitted to PEDONE
int pedone_good_move (int old_x, int old_y, int new_x, int new_y, Board board)
{
    // Same line/column check
    if      (old_x == new_x || old_y == new_y)      return 0; // only diagonal moves

    // Right Direction check
    else if (new_y > old_y+2)                       return 0; // can't jump three lines forward (max is 2 for eating another pedina) -->   ????? same problem ???????

    // Right cell check
    else if (new_x == old_x+2 && new_y == old_y+1)  return 0; // can't jump to different color cells    -->   ????? same problem ???????
    else if (new_x == old_x+1 && new_y == old_y+2)  return 0; //                                        -->   ????? same problem ???????
    else if (new_x == old_x-2 && new_y == old_y+1)  return 0; //                                        -->   ????? same problem ???????
    else if (new_x == old_x-1 && new_y == old_y+2)  return 0; //                                        -->   ????? same problem ???????
    
    // Empty cell check
    else if (board.getStatus(new_x, new_y) != ' ')  return 0; // move ony if the new cell is free
    
    else                                            return 1; // GOOD move!
}

// Eating opponent pedina
int eating_pedina (int old_x, int old_y, int new_x, int new_y, Board board)
{
    if (new_y == old_y+2)                                                                               //  -->   ????? same problem ???????
    {
        if      (new_x == old_x+2 && board.getStatus(old_x+1, old_y+1) != ' ') return 1; // eat right
        else if (new_x == old_x-2 && board.getStatus(old_x-1, old_y+1) != ' ') return 2; // eat left
        else                                                                   return 0;
    }
    else
      return 0; //nothing eaten
}

#endif // Moves_H
