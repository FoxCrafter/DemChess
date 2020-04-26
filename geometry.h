#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "config.h"

class Coors {
    int coors[Rules::DIMENSIONS];
protected:
    Coors() {}
public:
    Coors(int const *coors) {
        for(unsigned i = 0; i < Rules::DIMENSIONS; ++i)
            this->coors[i] = coors[i];
    }
    int operator[](unsigned i) const { return coor[i]; }
    int &operator[](unsigned i) { return coor[i]; }
    Coors operator+(RelCoors const &rc) const {
        Coors res;
        for(unsigned i = 0; i < Rules::DIMENSIONS; ++i)
            res[i] = coors[i] + rc[i];
    }
};

class RelCoors : public Coors {
public:
    RelCoors(Coors const &from, Coors const &to) {
        for(unsigned i = 0; i < Rules::DIMENSIONS; ++i)
            coors[i] = to[i] - from[i];
    }
    unsigned distance() const {
        unsigned d = 0;
        for(unsigned i = 0; i < Rules::DIMENSIONS; ++i)
            d += coors[i] * coors[i];
        return d;
    }
}

class Direction : public RelCoors {
    void unitize();
public:
    Direction(Coors const &from, Coors const &to) : RelCoors {
        unitize();
    }
    Direction(RelCoors const coors) : RelCoors(coors) {
        unitize();
    }
};

#endif
