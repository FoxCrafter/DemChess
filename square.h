#ifndef SQUARE_H
#define SQUARE_H

#include "geometry.h"

class Square {
    Coors const coors;
    Color const color;
public:
    Square(Coors coors, Color color) : coors(coors), color(color) {}
    Coors const &get_coors() const { return coors; }
    RelCoors rel_coors(Square const &sq1) const {
        return RelCoors(coors, sq1.coors);
    }
    Direction direction(Square const &sq1) const {
        return Direction(coors, sq1.coors);
    }
    unsigned distance(Square const &sq1) const {
        return rel_coors(sq1).distance();
    }
};

#endif
