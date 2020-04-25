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
    int operator[](unsigned i) const { return coor[i] }
    int &operator[](unsigned i) { return coor[i] }
};

class RelCoors : public Coors {
public:
    RelCoors(Coors const &from, Coors const &to) {
        for(unsigned i = 0; i < Rules::DIMENSIONS; ++i)
            coors[i] = to[i] - from[i];
    }
    unsigned distance() {
        unsigned d = 0;
        for(unsigned i = 0; i < Rules::DIMENSIONS; ++i)
            d += coors[i] * coors[i];
        return d;
    }
}

class Direction : public RelCoors {
public:
    Direction(Coors const &from, Coors const &to) : RelCoors(from, to) {
        unsigned i = 0;
        while(coors[i] == 0) {
            ++i;
            if(i >= Rules::DIMENSIONS)
                throw "all zero direction";
        };
        unsigned gcd = coors[i] > 0 ? coors[i] : -coors[i];
        
    }
};

#endif
