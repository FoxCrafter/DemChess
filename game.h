#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"

class Game;
namespace rules { void init(Game &); }

class Game {
    Player *players[rules::N_PLAYERS];
    Board board;
    unsigned active_player = 0;
    void pass_to_next_player() {
        active_player = (active_player + 1) % rules::N_PLAYERS;
    }
public:
    Game() {
        rules::init(*this);
    }
    virtual ~Game() {
        for(unsigned i = 0; i < rules::N_PLAYERS; ++i)
            delete players[i];
    }
    friend void rules::init(Game &);
};

#endif
