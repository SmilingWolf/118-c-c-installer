#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ogcsys.h>
#include <gccore.h>
#include <ogc/isfs.h>
#include <wiiuse/wpad.h>

#include "IOSPatcher.h"
#include "iospatch.h"
#include "wad.h"
#include "tools.h"
#include "network.h"
#include "C118_install.h"
#include "uninstall.h"

#define IOS36version 3351

s32 what_to_do()
{
	u32 pressed;
	u32 pressedGC;
	int selection = 0;
	int ret;
	char *optionsstring[3] = { "<Install IOS118 and 118 Channel>", "<Uninstall IOS118 and 118 Channel>", "<Exit>" };
	
	while (true)
	{
		Con_ClearLine();
		
		set_highlight(true);
		printf(optionsstring[selection]);
		set_highlight(false);
		
		waitforbuttonpress(&pressed, &pressedGC);
		
		if (pressed == WPAD_BUTTON_LEFT || pressedGC == PAD_BUTTON_LEFT)
		{
			if (selection > 0)
			{
				selection--;
			} else
			{
				selection =2;
			}
		}

		if (pressed == WPAD_BUTTON_RIGHT || pressedGC == PAD_BUTTON_RIGHT)
		{
			if (selection < 2)
			{
				selection++;
			} else
			{
				selection = 0;
			}
		}

		if (pressed == WPAD_BUTTON_A || pressedGC == PAD_BUTTON_A)
		{
			printf("\n");
			if (selection == 0) {
				printf("About to install IOS118\n");
				ret = Install_patched_IOS(36, IOS36version, true, true, true, true, 118, 65535, false);
				if (ret < 0) {
					printf("IOS118 Install failed.  Press any button to exit...\n");
					waitforbuttonpress(NULL, NULL);
					Reboot();
				}
				
				printf("\nStep 1 Complete!\n");
				printf("IOS118 Installation is complete!\n");
				
				install_channel_118();

				printf("\nStep 2 Complete!\n");
				
				printf("118Channel Installation is complete!\n");
				printf("Press any button to exit...\n");
				waitforbuttonpress(NULL, NULL);
				
				Reboot();
				return 0;
			}
			
			if (selection == 1)
			{
				ISFS_Initialize();
				Uninstall_DeleteTicket(1, 118);
				Uninstall_DeleteTitle(1, 118);
				Uninstall_118Channel_all();
				ISFS_Deinitialize();
			}
			if (selection == 2)
			{
				Reboot();
			}
		}
	}
}