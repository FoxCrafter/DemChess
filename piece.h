#ifndef PIECE_H
#define PIECE_H

#include "board.h"
#include "player.h"

#include <stdexcept>

class MoveException : public std::exception {
public:
    MoveException() : std::exception("No legal move.") {}
};

class InvalidPieceFlagException : public std::exception {
public:
    InvalidPieceFlagException() : std::exception("Invalid flag on piece.") {}
};

class Piece {
    bool enabled;
protected:
    Player &owner;
    Board &board;
    Square *square;
    unsigned move_counter = 0;
    int flags;
public:
    Piece(Player &owner, Board &board, Square *square)
    : enabled(true), owner(owner), board(board), square(square), flags(0) {}
    void enable() { enabled = true; }
    void disable() { enabled = false; }
    bool is_enabled() { return enabled; }
    virtual bool threatening(Square &target) = 0;
    virtual bool can_take(Piece *target_piece) {
        return target_piece == nullptr || target_piece->owner.get_team() != owner.get_team();
    }
    virtual bool can_move_0(Square &target) {
        return can_take(board.get_piece(target)) && threatening(target);
    }
    virtual bool can_move_1(Square &target) { return can_move_0(target); }
    virtual void move_to(Square &target);
    virtual void move();
    virtual void on_owners_move() {}
    virtual void on_friendly_move() {}
    virtual void on_enemy_move() {}
    virtual void on_purge() {}
    bool has_moved() { return move_counter > 0; }
    void set_square(Square *square) { this->square = square; }
    Square *get_square() const { return square; }
    Player &get_owner() { return owner; }
    Player const &get_owner() const { return owner; }
    bool check_flags(int flags) const { return (this->flags & flags) == flags; }
    void set_flags(int flags) { this->flags |= flags; }
    void unset_flags(int flags) { this->flags &= ~flags; }
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
