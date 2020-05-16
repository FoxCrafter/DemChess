#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"

class Game;
namespace rules { void init(Game &); }

class Game {
    Player *players[rules::N_PLAYERS];
    Board board;
public:
    Game() {
        rules::init(*this);
    }
    virtual ~Game() { delete [] players; }
    friend void rules::init(Game &);
};

#endif
