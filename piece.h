#include "board.h"

class Piece {
protected:
    Player &owner;
    Board &board;
    Square *square;
public:
    Piece(Player &owner, Board &board, Square *square)
    : owner(owner), board(board), square(square) {}
    virtual bool threatening(Square &target) = 0;
    virtual bool can_move_0(Square &target) {
        Piece *target_piece = board.get_piece(target);
        return (target_piece == NULL || target_piece->owner.get_team() != owner.get_team()) && threatening(target);
    }
    virtual bool can_move_1(Square &target) { return can_move_0(target); }
};

class LinearPiece : public Piece {
    unsigned const step_size_min, const step_size_max;
public:
    LinearPiece(Player &owner, Board &board, Square *square, unsigned step_size_min, unsigned step_size_max)
    : Piece(owner, board, square), step_size_min(step_size_min), step_size_max(step_size_max) {}
    bool threatening(Square &target) {
        Direction dir = square->direction(target);
        if(dir.distance() < step_size_min || dir.distance() > step_size_max)
            return false;
        for(RelCoors scan_coors = square->getCoors() + dir; scan_coors != target; scan_coors += dir) {
            Square *scan_square = board.get_square(scan_coors);
            if(scan_square != NULL && board.get_piece(scan_square) != NULL)
                return false;
        }
        return true;
    }
}
