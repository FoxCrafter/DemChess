#ifndef CONFIG_GAME_H
#define CONFIG_GAME_H

#include "game.h"
#include "config_pieces.h"

namespace Rules {

void init(Game &game) {
    game.players[0] = new Player(0, 0, Direction((int *){0,  1}));
    game.players[1] = new Player(1, 1, Direction((int *){0, -1}));
    for(unsigned i = 0; i < N_SQUARES; ++i)
        game.board.squares[i] = new Square(Coors(i % 8, i / 8), Color(i % 2));
    int const pawn_y[] = {1, 6};
    int const pieces_y[] = {0, 7};
    unsigned i = 0;
    for(x = 0; x < 8; ++x) {
        game.board.pieces[i++] = new Pawn(*game.players[0], game.board, game.board.squares[8 * pawn_y[0] + x], );
    }

}

#endif
