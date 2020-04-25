#ifndef CONFIG_H
#define CONFIG_H

#include "geometry.h"
#include "piece.h"

namespace Rules {

unsigned const N_PLAYERS = 2;

unsigned const DIMENSIONS = 2;

class ChessPiece : public Piece {
    King *
}
class Pawn : public Piece {
public:
    bool can_move_0(Square &) {

    }
};
class Rook : public Piece {
public:
    bool can_move_0(Square &) {

    }
};
class Knight : public Piece {
public:
    bool can_move_0(Square &) {

    }
};
class Bishop : public Piece {
public:
    bool can_move_0(Square &) {

    }
};
class Queen : public Piece {
public:
    bool can_move_0(Square &) {

    }
};
class King : public Piece {
public:
    bool can_move_0(Square &) {

    }
};

}

#endif
