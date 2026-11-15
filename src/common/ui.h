#ifndef UI_H
#define UI_H

#include <player.h>

int initUi();
void drawUi(struct PlayerData player_one, struct PlayerData player_two);
void cleanUpUi();

#endif