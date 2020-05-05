#ifndef BOARD_H
#define BOARD_H

#include "config_consts.h"
#include "square.h"

#include <stdexcept>

class Piece;
class Coors;
class Game;
namespace Rules {
    void init(Game &);
}

class SquareGroup {
    Square *squares[Rules::N_SQUARES];
    unsigned n = 0;
public:
    void add(Square *square) {
        for(unsigned i = 0; i < n; ++i)
            if(squares[i] == square) return;
        if(n >= Rules::N_SQUARES)
            throw std::out_of_range("square group is full? (more unique squares added then all of them)");
        squares[n++] = square;
    }
    unsigned count() { return n; }
    Square *&operator[](unsigned i) { return squares[i]; }
    Square *operator[](unsigned i) const { return squares[i]; }
};

class Board {
    Square *squares[Rules::N_SQUARES];
    Piece *pieces[Rules::N_PIECES];
public:
    Square *get_square(Coors coors);
    Piece *get_piece(Square &square);
    bool threatened(Piece &piece) const;
    bool empty_between(Square &s1, Square &s2);
    SquareGroup get_target_squares(Piece &piece);
    virtual ~Board();
    friend void Rules::init(Game &);
};

#endif
