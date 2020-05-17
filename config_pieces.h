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
    bool can_move_1(Square &target) {
        if(!can_move_0(target))
            return false;
        Piece *target_piece = board.get_piece(target);
        if(target_piece != nullptr)
            target_piece->disable();
        Square *bak = square;
        square = &target;
        bool check = board.threatened(*(Piece *)king);
        square = bak;
        if(target_piece != nullptr)
            target_piece->enable();
        return !check;
    }
};
class Rook;
class King : public ChessPiece {
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
            RelCoors rel = square->rel_coors(target);
            PieceGroup rooks_not_moved = board.get_pieces_by_flags(ROOK_NOT_MOVED);
            for(unsigned i = 0; i < rooks_not_moved.count(); ++i) {
                Rook *rook = dynamic_cast<Rook *>(rooks_not_moved[i]);
                if(rook == nullptr)
                    throw InvalidPieceFlagException;
                if(rook->get_owner() == owner) {
                    RelCoors rook_rel = square->rel_coors(*rook->get_square());
                    Direction rook_dir(rook_rel);
                    if(rook_rel.distance() > rel.distance() && board.empty_between(*square, *rook->get_square())) {
                        if(rel == rook_dir + rook_dir) {
                            Square *between = board.get_square(square->get_coors() + rook_dir);
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
        }
        return false;
    }
    void move_to(Square &target) {
        RelCoors rel = square->rel_coors(target);
        if(rel.distance() == 4) {
            Direction dir(rel);
            PieceGroup rooks_not_moved = board.get_pieces_by_flags(ROOK_NOT_MOVED);
            for(unsigned i = 0; i < rooks_not_moved.count(); ++i) {
                Rook *rook = dynamic_cast<Rook *>(rooks_not_moved[i]);
                if(rook == nullptr)
                    throw InvalidPieceFlagException;
                Square *rook_square = rook->get_square();
                if(square->direction(*rook_square) == dir && board.empty_between(*square, *rook_square)) {
                    Square *rook_target = board->get_square(square->get_coors() + dir);
                    if(rook_target != nullptr) {
                        rook->set_square(rook_target);
                        rook->unset_flags(ROOK_NOT_MOVED);
                    }
                    break;
                }
            }
        }
        Piece::move_to(square);
    }
};
class Rook : public ChessPiece, public LinearPiece {
public:
    Rook(Player &owner, Board &board, Square *square, King *king, bool original = true)
    : Piece(owner, board, square),
    ChessPiece(owner, board, square, king),
    LinearPiece(owner, board, square, 1, 1) {
        if(original) set_flags(ROOK_NOT_MOVED);
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
class Pawn : public ChessPiece {
    Square *en_passant_square;
    Pawn *get_en_passant_pawn(Square *square) {
        PieceGroup en_passant_pawns = board.get_pieces_by_flags(PAWN_EN_PASSANT);
        for(unsigned i = 0; i < en_passant_pawns.count(); ++i) {
            Pawn *en_passant_pawn = dynamic_cast<Pawn *>(en_passant_pawns[i]);
            if(en_passant_pawn == nullptr)
                throw InvalidPieceFlagException;
            if(en_passant_pawn->en_passant_square == square)
                return en_passant_pawn;
        }
        return nullptr;
    }
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
        Piece *target_piece = board.get_piece(target);
        RelCoors rel = square->rel_coors(target);
        unsigned d = rel.distance();
        if(target_piece == NULL) {
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
        }
        if(threatening(target)) {
            if(target_piece != NULL) {
                return can_take(target_piece);
            }
            else {
                Pawn *en_passant_pawn = get_en_passant_pawn(target);
                if(en_passant_pawn != nullptr)
                    return can_take(en_passant_pawn);
            }
        }
        return false;
    }
    void move_to(Square &target) {
        RelCoors rc = square.rel_coors(target);
        unsigned dis = rc.distance(target);
        Direction dir(rc);
        bool long_move = dis == 4;
        if(long_move) {
            Square *ep_square = board.get_square(square.get_coors() + dir);
            Pawn *prev_en_passant_pawn = get_en_passant_pawn(ep_square);
            if(prev_en_passant_pawn != nullptr)
                prev_en_passant_pawn->unset_flags(PAWN_EN_PASSANT);
            en_passant_square = ep_square;
        }
        else if(dis == 2 && board.get_piece(target) == nullptr) {
            Pawn *en_passant_pawn = get_en_passant_pawn(&target);
            if(en_passant_pawn != nullptr)
                board.remove_piece(en_passant_pawn);
        }
        Piece::move_to(target);
        if(board.get_square(square->get_coors() + dir) == nullptr) {
            evolve();
        }
        else if(long_move)
            set_flags(PAWN_EN_PASSANT);
    }
    void evolve() {
        Piece *new_piece;
        unsigned random = std::rand() % 4;
        switch(random) {
        case 0: new_piece = new Rook  (owner, board, square, king, false); break;
        case 1: new_piece = new Knight(owner, board, square, king       ); break;
        case 2: new_piece = new Bishop(owner, board, square, king       ); break;
        case 3: new_piece = new Queen (owner, board, square, king       ); break;
        }
        board.add_piece(new_piece);
        board.remove_piece(this);
    }
    void on_owners_move() { unset_flags(PAWN_EN_PASSANT); }
};

}

#endif
