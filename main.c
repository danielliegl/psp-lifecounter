#include <pspuser.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>

PSP_MODULE_INFO("Lifecounter", 0, 1, 1);

PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#define printf pspDebugScreenPrintf

int done = 0;

int exit_callback(int arg1, int arg2, void *common)
{
  done = 1;
  return 0;
}

int callback_thread(SceSize args, void *argp)
{
  int cbid = sceKernelCreateCallback("Exit Callback",
    exit_callback, NULL);
  sceKernelRegisterExitCallback(cbid);
  sceKernelSleepThreadCB();
  return 0;
}

int setup_callbacks(void)
{
  int thid = sceKernelCreateThread("update_thread",
      callback_thread, 0x11, 0xFA0, 0, 0);

  if(thid >= 0)
    sceKernelStartThread(thid, 0, 0);
  return thid;
}

int main(void)
{
  SceCtrlData pad;

  pspDebugScreenInit();
  setup_callbacks();

  sceCtrlSetSamplingCycle(0);
  sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

  int player_one_life = 20;
  int player_two_life = 20;

  bool pressing = false;

  while (!done)
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
