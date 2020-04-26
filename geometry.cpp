#include "geometry.h"

inline static unsigned abs(int x) {
    return x > 0 ? x : -x;
}

Direction::unitize() {
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
