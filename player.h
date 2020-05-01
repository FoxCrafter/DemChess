#ifndef PLAYER_H
#define PLAYER_H

#include "config_consts.h"
#include "geometry.h"

class Player {
    int team;
    int id;
    Direction forward;
public:
    Player(int team, int id, Direction forward) : team(team), id(id), forward(forward) {}
    int get_team() const { return team; }
    int get_forward(unsigned i) { return forward[i]; }
};

#endif
