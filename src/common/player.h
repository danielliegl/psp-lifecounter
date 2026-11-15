#ifndef PLAYER_H
#define PLAYER_H

struct PlayerData {
  int life_total;
  int infect;
};

struct PlayerData initPlayerData();
#endif