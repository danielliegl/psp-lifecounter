#include <pspuser.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>
#include <./common/callback.h>

PSP_MODULE_INFO("Lifecounter", 0, 1, 1);

PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#define printf pspDebugScreenPrintf

int main(void)
{
  SceCtrlData pad;

  pspDebugScreenInit();
  setupExitCallback();

  sceCtrlSetSamplingCycle(0);
  sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

  int player_one_life = 20;
  int player_two_life = 20;

  int pressing = 0;

  while (isRunning())
  {
    pspDebugScreenSetXY(0, 2);
    sceCtrlReadBufferPositive(&pad, 1);

    if (pad.Buttons != 0)
    {
      if(!pressing)
      {
        //player one life controls
        if (pad.Buttons & PSP_CTRL_RIGHT)
        {
          player_one_life++;
        }
        if (pad.Buttons & PSP_CTRL_LEFT)
        {
          player_one_life--;
        }
        
        //player two life controls
        if (pad.Buttons & PSP_CTRL_SQUARE)
        {
          player_two_life++;
        }
        if (pad.Buttons & PSP_CTRL_CIRCLE)
        {
          player_two_life--;
        }
        pressing = 1;
      }
    } else {
      pressing = 0;
    }

    printf("Player One: %d - Player Two: %d", player_one_life, player_two_life);
  }

  sceKernelExitGame();
  return 0;
}
