#ifndef CONFIG_CONSTS_H
#define CONFIG_CONSTS_H

namespace Rules {

unsigned const N_PLAYERS = 2;

unsigned const DIMENSIONS = 2;
unsigned const N_SQUARES = 8 * 8;
unsigned const N_PIECES = 32;

enum piece_flag {
    PAWN_EN_PASSANT = 1 << 0,
    ROOK_NOT_MOVED  = 1 << 1
};

}

#endif
