#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "config.h"

class Color {
    char data;
public:
    Color(char data) : data(data) {}
};

class Square {
    Coors const coors;
    Color const color;
public:
    Square(Coors coors, Color color) : coors(coors), color(color) {}
    Coors const &getCoors() const { return coors; }
    RelCoors relCoors(Square const &sq1) const {
        return RelCoors(coors, sq1.coors);
    }
    Direction direction(Square const &sq1) const {
        return Direction(coors, sq1.coors);
    }
    unsigned distance(Square const &sq1) const {
        return relCoors(sq1).distance();
    }
};

#endif
