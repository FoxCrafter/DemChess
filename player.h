#ifndef PLAYER_H
#define PLAYER_H

#include "config_consts.h"
#include "geometry.h"

class Player {
    int const team;
    int const id;
    Color const color;
    Direction const forward;
public:
    Player(int team, int id, Direction forward) : team(team), id(id), color(color), forward(forward) {}
    int get_team() const { return team; }
    int get_id() const { return id; }
    int get_color() const { return color; }
    int get_forward(unsigned i) const { return forward[i]; }
    bool operator==(Player const &p1) const { return id == p1.id; }
    bool operator!=(Player const &p1) const { return !(*this == p1); }
};

#endif
