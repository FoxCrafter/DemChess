#ifndef CONFIG_GAME_H
#define CONFIG_GAME_H

#include "game.h"
#include "config_pieces.h"
#include "color.h"

namespace rules {

void init(Game &game) {
    for(int i = 0; i < N_SQUARES; ++i) {
        int const coor_array[] = {i % 8, i / 8};
        game.board.squares[i] = new Square(Coors(coor_array), (i + i / 8) % 2 == 0 ? COLOR_BLUE : COLOR_MAGENTA);
    }
    Color const color[] = {COLOR_YELLOW, COLOR_GREEN};
    int const forward_array[][2] = {{0, 1}, {0, -1}};
    int const pieces_y[] = {0, 7};
    int const pawn_y[] = {1, 6};
    unsigned i_piece = 0;
    for(unsigned i_player = 0; i_player < N_PLAYERS; ++i_player) {
        game.players[i_player] = new Player(i_player, i_player, color[i_player], Direction(forward_array[i_player]));
#       define PIECE_PARAMS(X, Y_ARR) *game.players[i_player], game.board, game.board.squares[8 * (Y_ARR)[i_player] + (X)]
#       define ADD_PIECE game.board.pieces[i_piece++] =
        King *king = new King(PIECE_PARAMS(4, pieces_y));
        ADD_PIECE king;
        ADD_PIECE new Queen (PIECE_PARAMS(3, pieces_y), king);
        ADD_PIECE new Bishop(PIECE_PARAMS(2, pieces_y), king);
        ADD_PIECE new Bishop(PIECE_PARAMS(5, pieces_y), king);
        ADD_PIECE new Knight(PIECE_PARAMS(1, pieces_y), king);
        ADD_PIECE new Knight(PIECE_PARAMS(6, pieces_y), king);
        ADD_PIECE new Rook  (PIECE_PARAMS(0, pieces_y), king);
        ADD_PIECE new Rook  (PIECE_PARAMS(7, pieces_y), king);
        for(int x = 0; x < 8; ++x)
            ADD_PIECE new Pawn(PIECE_PARAMS(x, pawn_y), king);
#       undef ADD_PIECE
#       undef PIECE_PARAMS
    }
    game.board.min_coors[0] = 0;
    game.board.min_coors[1] = 0;
    game.board.max_coors[0] = 7;
    game.board.max_coors[1] = 7;
}

}

#endif
