#ifndef PLAYER_H
#define PLAYER_H

class Player {
    int team;
    int id;
public:
    Player(int team, int id) : team(team), id(id) {}
    int get_team() const { return team; }
};

#endif
