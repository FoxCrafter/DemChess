#include "piece.h"

bool LinearPiece::threatening(Square &target) {
    Direction dir = square->direction(target);
    if(dir.distance() < step_size_min || dir.distance() > step_size_max)
        return false;
    for(Coors scan_coors = square->get_coors() + dir; scan_coors != target.get_coors(); scan_coors += dir) {
        Square *scan_square = board.get_square(scan_coors);
        if(scan_square != nullptr && board.get_piece(*scan_square) != nullptr)
            return false;
    }
    return true;
}

void Piece::move_to(Square &target) {
    board.remove_piece(get_piece(&target));
    set_square(&target);
    PieceGroup all_pieces = board.get_pieces_by_flags(0);
    for(unsigned i = 0; i < all_pieces.count(); ++i) {
        if(all_pieces[i].get_owner() == owner)
            all_pieces[i].on_owners_move();
        else if(all_pieces[i].get_owner().get_team() == owner.get_team())
            all_pieces[i].on_friendly_move();
        else
            all_pieces[i].on_enemy_move();
    }
    ++move_counter;
}

void Piece::move() {
    SquareGroup targets = board.get_target_squares(*this);
    if(targets.count() == 0)
        throw MoveException;
    unsigned random = std::rand() % targets.count();
    move_to(*targets[random]);
}
