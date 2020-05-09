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

template<class T, unsigned MAX_SIZE>
class Group {
    T *entries[MAX_SIZE];
    unsigned n = 0;
public:
    void add(T *entry) {
        for(unsigned i = 0; i < n; ++i)
            if(entries[i] == entry) return;
        if(n >= MAX_SIZE)
            throw std::out_of_range("group is full? (shouldnt be possible: more unique entries added then all of them)");
        entries[n++] = entry;
    }
    unsigned count() { return n; }
    Square *&operator[](unsigned i) { return entries[i]; }
    Square *operator[](unsigned i) const { return entries[i]; }
};

typedef Group<Square, Rules::N_SQUARES> SquareGroup;
typedef Group<Piece, Rules::N_PIECES> PieceGroup;

class PieceGroup

class Board {
    Square *squares[Rules::N_SQUARES];
    Piece *pieces[Rules::N_PIECES];
public:
    Square *get_square(Coors coors);
    Piece *get_piece(Square &square);
    void remove_piece(Piece *piece);
    void add_piece(Piece *piece);
    bool threatened(Piece &piece) const;
    bool empty_between(Square &s1, Square &s2);
    SquareGroup get_target_squares(Piece &piece);
    PieceGroup get_pieces_by_flags(int flags);
    virtual ~Board();
    friend void Rules::init(Game &);
};

#endif
