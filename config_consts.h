#ifndef CONFIG_CONSTS_H
#define CONFIG_CONSTS_H

namespace rules {

unsigned const N_PLAYERS = 2;

unsigned const DIMENSIONS = 2;    // must be at least 2
unsigned const N_SQUARES = 8 * 8; // must be at least 1
unsigned const N_PIECES = 32;     // the max n of pieces

enum piece_flag {                 // must be 1 << n (1, 2, 4, etc)
    PAWN_EN_PASSANT = 1 << 0,     // as they are bitflags used via
    ROOK_NOT_MOVED  = 1 << 1      // bitwise operations
};

}

#endif
