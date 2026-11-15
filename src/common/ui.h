#ifndef UI_H
#define UI_H

#include <player.h>
#include <SDL3/SDL.h>

struct RenderedTexture {
    SDL_Texture* texture;
    SDL_FRect text_rect;
    int number;
};

int initUi();
void drawUi(struct PlayerData player_one, struct PlayerData player_two);
void cleanUpUi();
struct RenderedTexture renderText(int life_total, struct RenderedTexture* rendered_texture);

#endif