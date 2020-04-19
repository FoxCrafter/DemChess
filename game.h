#ifndef GAME_H
#define GAME_H

#include "config.h"

class Game {
    Player players[Rules::N_PLAYERS];
public:
    void init();
};

#endif
