#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "config.h"

class Color {
    char data;
public:

};

class Square {
    Coors const coors;
    Color color;
public:
    Square(Coors coors, Color color) : coors(coors), color(color) {}
    Coors const &getCoors() const { return coors; }
    unsigned distance(Square const &) const;
    int stepsAway(Square const &, Direction const &) const;
};

#endif
