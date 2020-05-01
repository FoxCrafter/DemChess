#ifndef PIECE_H
#define PIECE_H

#include "board.h"
#include "player.h"

class Piece {
protected:
    Player &owner;
    Board &board;
    Square *square;
    unsigned move_counter = 0;
public:
    Piece(Player &owner, Board &board, Square *square)
    : owner(owner), board(board), square(square) {}
    virtual bool threatening(Square &target) = 0;
    virtual bool can_take(Piece *target_piece) {
        return target_piece == nullptr || target_piece->owner.get_team() != owner.get_team();
    }
    virtual bool can_move_0(Square &target) {
        return can_take(board.get_piece(target)) && threatening(target);
    }
    virtual bool can_move_1(Square &target) { return can_move_0(target); }
    virtual void move() { /* TODO */ }
    bool has_moved() { return move_counter == 0; }
    Square *&get_square() { return square; }
    Square *get_square() const { return square; }
    Player &get_owner() { return owner; }
    Player const &get_owner() const { return owner; }
    virtual ~Piece() {}
};

class LinearPiece : public virtual Piece {
    unsigned const step_size_min;
    unsigned const step_size_max;
public:
    LinearPiece(Player &owner, Board &board, Square *square, unsigned step_size_min, unsigned step_size_max)
    : Piece(owner, board, square), step_size_min(step_size_min), step_size_max(step_size_max) {}
    bool threatening(Square &target);
};

#endif
