#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"
#include "piece.h"

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
    void execute_move_order(Coors coors) {
        Square *square = board.get_square(coors);
        if(square == nullptr)
            throw MoveException("No such square.");
        Piece *piece = board.get_piece(*square);
        if(piece == nullptr)
            throw MoveException("No piece on selected square.");
        if(piece->get_owner() != *players[active_player])
            throw MoveException("Selected piece is not yours.");
        piece->move();
        pass_to_next_player();
    }
    Board &get_board() { return board; }
    Board const &get_board() const { return board; }
    virtual ~Game() {
        for(unsigned i = 0; i < rules::N_PLAYERS; ++i)
            delete players[i];
    }
    friend void rules::init(Game &);
};

#endif
