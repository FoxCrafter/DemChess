#include "board.h"

class Piece {
protected:
    Player &owner;
    Square *square;
public:
    virtual bool can_move_0(Square &target) = 0;
};
