#ifndef CONFIG_PIECES_H
#define CONFIG_PIECES_H

#include "config_consts.h"
#include "piece.h"

namespace Rules {

class King;
class ChessPiece : public virtual Piece {
protected:
    King *king;
public:
    ChessPiece(Player &owner, Board &board, Square *square, King *king)
    : Piece(owner, board, square), king(king) {}
    bool can_move_1(Square &target) {
        if(!can_move_0(target))
            return false;
        Square *bak = square;
        square = &target;
        bool check = board.threatened(*(Piece *)king);
        square = bak;
        return !check;
    }
};
class Rook;
class King : public ChessPiece {
    static unsigned const N_ROOKS_MAX = 2;
    unsigned n_rooks = 0;
    Rook *rooks[N_ROOKS_MAX];
public:
    King(Player &owner, Board &board, Square *square)
    : Piece(owner, board, square),
    ChessPiece(owner, board, square, nullptr) {
        king = this;
    }
    bool threatening(Square &target) {
        unsigned d = square->distance(target);
        return d <= 2 && d > 0;
    }
    bool can_move_0(Square &target) {
        if(threatening(target))
            return true;
        // CASTLING
        if(!has_moved() && board.threatened(*this)) {
            Direction rel = square->rel_coors(target);
            for(unsigned i = 0; i < n_rooks; ++i) {
                if(!((Piece *)rooks[i])->has_moved() && board.empty_between(*square, *((Piece *)rooks[i])->get_square())) {
                    Direction dir = square->direction(*((Piece *)rooks[i])->get_square());
                    if(rel == dir + dir) {
                        Square *between = board.get_square(square->get_coors() + dir);
                        if(between != nullptr) {
                            Square *bak = square;
                            square = between;
                            bool through_check = board.threatened(*this);
                            square = bak;
                            if(!through_check)
                                return true;
                        }
                    }
                }
            }
        }
        return false;
    }
    void add_rook(Rook *rook) {
        if(n_rooks == N_ROOKS_MAX)
            throw "King cant handle this many rooks";
        rooks[n_rooks++] = rook;
    }
};
class Pawn : public ChessPiece {
    bool long_stepped = false;
public:
    Pawn(Player &owner, Board &board, Square *square, King *king)
    : Piece(owner, board, square),
    ChessPiece(owner, board, square, king) {}
    bool threatening(Square &target) {
        RelCoors rel = square->rel_coors(target);
        if(rel.distance() == 2) {
            for(unsigned i = 0; i < DIMENSIONS; ++i) {
                if(rel[i] != 0 && rel[i] == owner.get_forward(i))
                    return true;
            }
        }
        return false;
    }
    bool can_move_0(Square &target) {
        RelCoors rel = square->rel_coors(target);
        unsigned d = rel.distance();
        if(d == 1) {
            for(unsigned i = 0; i < DIMENSIONS; ++i) {
                if(rel[i] != 0 && rel[i] == owner.get_forward(i))
                    return board.get_piece(target) == nullptr;
            }
        }
        else if(!has_moved() && d == 4) {
            for(unsigned i = 0; i < DIMENSIONS; ++i) {
                if(rel[i] != 0 && rel[i] == owner.get_forward(i) * 2 && board.get_piece(target) == nullptr) {
                    Square *between = board.get_square(square->get_coors() + Direction(rel));
                    return between != nullptr && board.get_piece(*between) == nullptr;
                }
            }
        }
        return false;
    }
};
class Rook : public ChessPiece, public LinearPiece {
public:
    Rook(Player &owner, Board &board, Square *square, King *king)
    : Piece(owner, board, square),
    ChessPiece(owner, board, square, king),
    LinearPiece(owner, board, square, 1, 1) {
        king->add_rook(this);
    }
};
class Knight : public ChessPiece {
public:
    Knight(Player &owner, Board &board, Square *square, King *king)
    : Piece(owner, board, square),
    ChessPiece(owner, board, square, king) {}
    bool threatening(Square &target) {
        return square->distance(target) == 5;
    }
};
class Bishop : public ChessPiece, public LinearPiece {
public:
    Bishop(Player &owner, Board &board, Square *square, King *king)
    : Piece(owner, board, square),
    ChessPiece(owner, board, square, king),
    LinearPiece(owner, board, square, 2, 2) {}
};
class Queen : public ChessPiece, public LinearPiece {
public:
    Queen(Player &owner, Board &board, Square *square, King *king)
    : Piece(owner, board, square),
    ChessPiece(owner, board, square, king),
    LinearPiece(owner, board, square, 1, 2) {}
};

}

#endif
