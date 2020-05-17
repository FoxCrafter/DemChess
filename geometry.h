#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "config_consts.h"

class RelCoors;
class Coors {
protected:
    int coors[rules::DIMENSIONS];
public:
    Coors() : coors{0} {}
    Coors(int const *coors);
    int operator[](unsigned i) const { return coors[i]; }
    int &operator[](unsigned i) { return coors[i]; }
    Coors operator+(RelCoors const &rc) const;
    Coors &operator+=(RelCoors const &rc);
    bool operator==(Coors const &c1) const;
    bool operator!=(Coors const &c1) const { return !operator==(c1); }
};

class RelCoors : public Coors {
public:
    RelCoors(int const *coors) : Coors(coors) {}
    RelCoors(Coors const &from, Coors const &to);
    unsigned distance() const;
};

class Direction : public RelCoors {
    void unitize();
public:
    Direction(int const *coors) : RelCoors(coors) {}
    Direction(Coors const &from, Coors const &to) : RelCoors(from, to) { unitize(); }
    Direction(RelCoors coors) : RelCoors(coors) { unitize(); }
};

#endif
