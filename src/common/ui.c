#include <player.h>
#include <ui.h>
#include <math.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;

// set text and background colors
SDL_Color text_color = {0x00, 0x00, 0x00, 0xff};
SDL_Color bg_color = {0xff, 0xff, 0xff, 0xff};

SDL_Event event;

struct RenderedTexture player_one_texture;
struct RenderedTexture player_two_texture;

int initUi()
{
  // Initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
  {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return 1;
  }

  // Initialize SDL TTF
  if (!TTF_Init())
  {
    SDL_Log("Couldn't initialize SDL ttf: %s", SDL_GetError());
    SDL_Quit();
    return 2;
  }

  if (!SDL_CreateWindowAndRenderer("window", SCREEN_WIDTH, SCREEN_HEIGHT,
                                   0, &window, &renderer))
  {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    SDL_Quit();
    return 3;
  }

  // load the font file. make sure it is in the same directory as the eboot file
  font = TTF_OpenFont("Roboto-SemiBold.ttf", 40);
  if (!font)
  {
    SDL_Log("Couldn't load font: %s", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 4;
  }

  return 0;
}

void drawUi(struct PlayerData player_one, struct PlayerData player_two)
{
  if (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_EVENT_GAMEPAD_ADDED: // Activate any gamepad that is connected
      SDL_OpenGamepad(event.cdevice.which);
      break;
    }
  }

  char* life_total_string = malloc(sizeof(char)*(int)log10(player_one.life_total));
  player_one_texture = renderText(player_one.life_total, &player_one_texture);

  SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
  SDL_RenderClear(renderer);
  SDL_RenderTexture(renderer, player_one_texture.texture, NULL, &player_one_texture.text_rect);
  SDL_RenderPresent(renderer);
}

void cleanUpUi() {
  SDL_DestroyTexture(player_one_texture.texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
}

struct RenderedTexture renderText(int life_total, struct RenderedTexture* rendered_texture){
  
  // if the life total did not change, do not rerender.
  if(rendered_texture->number == life_total) {
    return *rendered_texture;
  }

  char* text = malloc(sizeof(char)*(int)log10(life_total));

  // Create a texture using a string and SDL ttf
  SDL_Surface *surface = TTF_RenderText_Solid(font, text, SDL_strlen(text), text_color);
  if (!surface)
  {
    SDL_Log("Couldn't render text: %s", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FRect text_rect = {0,0,0,0};

  // Get text dimensions
  text_rect.w = (float)surface->w;
  text_rect.h = (float)surface->h;

  SDL_DestroySurface(surface);
  free(text);

  text_rect.x = (SCREEN_WIDTH - text_rect.w) / 2.0f;
  text_rect.y = text_rect.h + 30.0f;

  struct RenderedTexture retval = {texture, text_rect, life_total};
  return retval;
}