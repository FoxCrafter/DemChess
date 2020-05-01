#ifndef BOARD_H
#define BOARD_H

#include "config_consts.h"
#include "square.h"

class Piece;
class Coors;
class Game;
namespace Rules {
    void init(Game &);
}

class Board {
    Square *squares[Rules::N_SQUARES];
    Piece *pieces[Rules::N_PIECES];
public:
    Square *get_square(Coors coors);
    Piece *get_piece(Square &square);
    bool threatened(Piece &piece) const;
    bool empty_between(Square &s1, Square &s2);
    virtual ~Board();
    friend void Rules::init(Game &);
};

#endif
