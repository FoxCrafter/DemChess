#include "board.h"
#include "piece.h"
#include "square.h"

Square *Board::get_square(Coors coors) {
    for(unsigned i = 0; i < Rules::N_SQUARES; ++i) {
        if(squares[i]->get_coors() == coors)
            return squares[i];
    }
    return nullptr;
}

Piece *Board::get_piece(Square &square) {
    for(unsigned i = 0; i < Rules::N_PIECES; ++i) {
        if(pieces[i]->get_square() == &square)
            return pieces[i];
    }
    return nullptr;
}

bool Board::threatened(Piece &piece) const {
    for(unsigned i = 0; i < Rules::N_PIECES; ++i) {
        if(pieces[i]->get_owner().get_team() != piece.get_owner().get_team()
        && pieces[i]->threatening(*piece.get_square()))
            return true;
    }
    return false;
}

bool Board::empty_between(Square &s1, Square &s2) {
    Direction dir = s1.direction(s2);
    for(Coors scan_coors = s1.get_coors() + dir; scan_coors != s2.get_coors(); scan_coors += dir) {
        Square *scan_square = get_square(scan_coors);
        if(scan_square != nullptr && get_piece(*scan_square) != nullptr)
            return false;
    }
    return true;
}

Board::~Board() {
    for(unsigned i = 0; i < Rules::N_SQUARES; ++i)
        delete squares[i];
    for(unsigned i = 0; i < Rules::N_PIECES; ++i)
        delete pieces[i];
}
