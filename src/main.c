#include <common/callback.h>
#include <common/player.h>
#include <common/ui.h>
#include <pspctrl.h>
#include <pspuser.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char **argv)
{

  (void) argc;
  (void) argv;

  int ui_init_status = initUi();
  if (ui_init_status != 0) {
    return ui_init_status;
  }

  SceCtrlData pad;

  setupExitCallback();

  sceCtrlSetSamplingCycle(0);
  sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

  struct PlayerData player_one = initPlayerData();
  struct PlayerData player_two = initPlayerData();

  int pressing = 0;

  while (isRunning())
  {
    sceCtrlReadBufferPositive(&pad, 1);

    if (pad.Buttons != 0)
    {
      if(!pressing)
      {
        //player one life controls
        if (pad.Buttons & PSP_CTRL_RIGHT)
        {
          player_one.life_total++;
        }
        if (pad.Buttons & PSP_CTRL_LEFT)
        {
          player_one.life_total--;
        }
        
        //player two life controls
        if (pad.Buttons & PSP_CTRL_SQUARE)
        {
          player_two.life_total++;
        }
        if (pad.Buttons & PSP_CTRL_CIRCLE)
        {
          player_two.life_total--;
        }
        pressing = 1;
      }
    } else {
      pressing = 0;
    }

    if(drawUi(player_one, player_two) != 0) {
      return 1;
    }
  }

  cleanUpUi();

  return 0;
}
