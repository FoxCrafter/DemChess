#include "geometry.h"

Coors::Coors(int const *coors) {
    for(unsigned i = 0; i < Rules::DIMENSIONS; ++i)
        this->coors[i] = coors[i];
}

Coors Coors::operator+(RelCoors const &rc) const {
    Coors res;
    for(unsigned i = 0; i < Rules::DIMENSIONS; ++i)
        res[i] = coors[i] + rc[i];
    return res;
}

Coors &Coors::operator+=(RelCoors const &rc) {
    for(unsigned i = 0; i < Rules::DIMENSIONS; ++i)
        coors[i] += rc[i];
    return *this;
}

bool Coors::operator==(Coors const &c1) const {
    for(unsigned i = 0; i < Rules::DIMENSIONS; ++i)
        if(coors[i] != c1[i])
            return false;
    return true;
}

RelCoors::RelCoors(Coors const &from, Coors const &to) {
    for(unsigned i = 0; i < Rules::DIMENSIONS; ++i)
        coors[i] = to[i] - from[i];
}

unsigned RelCoors::distance() const {
    unsigned d = 0;
    for(unsigned i = 0; i < Rules::DIMENSIONS; ++i)
        d += coors[i] * coors[i];
    return d;
}

inline static unsigned abs(int x) {
    return x > 0 ? x : -x;
}

void Direction::unitize() {
    unsigned i = 0;
    while(coors[i] == 0) {
        if(++i >= Rules::DIMENSIONS)
            throw "all zero direction";
    }
    unsigned gcd = abs(coors[i]);
    while(++i < Rules::DIMENSIONS) {
        if(coors[i] != 0) {
            unsigned tmp0 = gcd;
            unsigned tmp1 = abs(coors[i]);
            while(true) {
                tmp0 %= tmp1;
                if(tmp0 == 0) {
                    gcd = tmp1;
                    break;
                }
                tmp1 %= tmp0;
                if(tmp1 == 0) {
                    gcd = tmp0;
                    break;
                }
            }
        }
    }
    for(i = 0; i < Rules::DIMENSIONS; ++i)
        coors[i] /= gcd;
}
