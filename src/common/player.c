#include <player.h>

struct PlayerData initPlayerData() {
  struct PlayerData player_data;
  player_data.life_total = 20;
  player_data.infect = 0;
  return player_data;
}