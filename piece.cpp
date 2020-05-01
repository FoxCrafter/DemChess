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
