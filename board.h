#ifndef BOARD_H
#define BOARD_H

#include "square.h"

class Board {
    Square **squares;
    Piece **pieces;
public:
    Square *get_square(Coors coors) {
        for(unsigned i = 0; i < Rules::N_SQUARES; ++i) {
            if(squares[i]->getCoors() == coors)
                return squares[i];
        }
        return NULL;
    }
    Piece *get_piece(Square *square) {
        for(unsigned i = 0; i < Rules::N_PIECES; ++i)
    }
    attacked(Piece &piece);
};

#endif
