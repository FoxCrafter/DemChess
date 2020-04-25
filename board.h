#ifndef BOARD_H
#define BOARD_H

#include "square.h"

class Board {
    Square **squares;
    Piece **pieces;
public:
    Square *getSquare();
    isAttacked(Piece &piece);
};

#endif
