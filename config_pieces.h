#ifndef CONFIG_PIECES_H
#define CONFIG_PIECES_H

#include "config_consts.h"
#include "piece.h"

namespace rules {

class King;
class ChessPiece : public virtual Piece {
protected:
    King *king;
public:
    ChessPiece(Player &owner, Board &board, Square *square, King *king)
    : Piece(owner, board, square), king(king) {}
    bool can_move_1(Square &target);
};
class Rook : public ChessPiece, public LinearPiece {
public:
    Rook(Player &owner, Board &board, Square *square, King *king, bool original = true)
    : Piece(owner, board, square),
    ChessPiece(owner, board, square, king),
    LinearPiece(owner, board, square, 1, 1) {
        if(original) set_flags(ROOK_NOT_MOVED);
        display_char = '\u265C';
    }
};
class King : public ChessPiece {
public:
    King(Player &owner, Board &board, Square *square)
    : Piece(owner, board, square),
    ChessPiece(owner, board, square, nullptr) {
        king = this;
        display_char = '\u265A';
    }
    bool threatening(Square &target) {
        unsigned d = square->distance(target);
        return d <= 2 && d > 0;
    }
    bool can_move_0(Square &target);
    void move_to(Square &target);
};
class Knight : public ChessPiece {
public:
    Knight(Player &owner, Board &board, Square *square, King *king)
    : Piece(owner, board, square),
    ChessPiece(owner, board, square, king) {
        display_char = '\u265E';
    }
    bool threatening(Square &target) {
        return square->distance(target) == 5;
    }
};
class Bishop : public ChessPiece, public LinearPiece {
public:
    Bishop(Player &owner, Board &board, Square *square, King *king)
    : Piece(owner, board, square),
    ChessPiece(owner, board, square, king),
    LinearPiece(owner, board, square, 2, 2) {
        display_char = '\u265D';
    }
};
class Queen : public ChessPiece, public LinearPiece {
public:
    Queen(Player &owner, Board &board, Square *square, King *king)
    : Piece(owner, board, square),
    ChessPiece(owner, board, square, king),
    LinearPiece(owner, board, square, 1, 2) {
        display_char = '\u265B';
    }
};
class Pawn : public ChessPiece {
    Square *en_passant_square;
    Pawn *get_en_passant_pawn(Square *square);
public:
    Pawn(Player &owner, Board &board, Square *square, King *king)
    : Piece(owner, board, square),
    ChessPiece(owner, board, square, king) {
        display_char = '\u265E';
    }
    bool threatening(Square &target);
    bool can_move_0(Square &target);
    void move_to(Square &target);
    void evolve();
    void on_owners_move() { unset_flags(PAWN_EN_PASSANT); }
};

}

#endif
