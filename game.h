#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"

class Game;
namespace Rules { void init(Game &); }

class Game {
    Player *players[Rules::N_PLAYERS];
    Board board;
public:
    Game() {
        Rules::init(*this);
    }
    friend void Rules::init(Game &);
};

#endif
