#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "config.h"

class Coors {
    int coors[Rules::DIMENSIONS];
public:
    int const &operator[](unsigned i) const { return coor[i] }
    int &operator[](unsigned i) { return coor[i] }
};

class RelCoors : public Coors {
public:
    RelCoors(Coors const &, Coors const &);
}

class Direction : public RelCoors {
public:
    Direction(Coors const &, Coors const &);
};

#endif
