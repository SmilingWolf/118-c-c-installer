#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <malloc.h>

#include "IOSPatcher.h"
#include "iospatch.h"
#include "wad.h"
#include "tools.h"
#include "network.h"
#include "C118_install.h"
#include "Install_Uninstall.h"

#define IOS36version 3351

// Prevent IOS36 loading at startup
s32 __IOS_LoadStartupIOS()
{
	return 0;
}

s32 __u8Cmp(const void *a, const void *b)
{
	return *(u8 *)a-*(u8 *)b;
}


int main(int argc, char* argv[])
{
	u32 pressed;
	u32 pressedGC;	

	Init_Console();
	printf("\x1b[%u;%um", 37, false);

	PAD_Init();
	WPAD_Init();
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);					

	printheadline();

	printf("WARNING: If you are not connected to the Internet, this app might crash.\n");
	printf("If you get a DSI error, rerun the app and be a little quicker.\n\n");
	printf("\nThis Application will install the 118Channel and IOS118 onto your Wii.\n");
	printf("It relies on the fact that you launched this app with.\n");
	printf("the AHBPROT flags set, so you must be using HBC 1.07 or later.\n");
	printf("\nIOS118 is a patched IOS36 v3351 and this app can be used\n");
	printf("instead of the Trucha Bug Restorer, upon which the app was based.\n");
	printf("\nThis application should work on all Wii firmwares 4.3 and below,\n");
	printf("and as long as the HBC supports AHBPROT, it should work on newer\n");
	printf("firmwares too.  It is safe to use this application to reinstall\n");
	printf("IOS118 or replace a different IOS118.\n");
	printf("\nThanks, in no particular order, go to the Wiitaly\n");
	printf("Team (Step, wasabi, student, Shur'tugal, Zahir71, dafunk and Lupo96),\n");
	printf("Dr. Clipper, Wiipower, oggzee, Team Twiizers, tona, Joseph Jordan\n");
	printf("and anybody else who has code included in the app.\n");
	printf("The app was quite a simple job, built upon their\n");
	printf("actual real work.\n");
	/*printf("\nPlease Wait...\n");
	
	time_t t = time(NULL) + 7;
	while (time(NULL) < t)
	{
		WPAD_ScanPads();
		PAD_ScanPads();
		if(WPAD_ButtonsDown(0) || PAD_ButtonsDown(0)) 
		{
			printf("Don't be impatient, press any button to exit...\n");
			waitforbuttonpress(NULL, NULL);
			Reboot();
		}
	}*/

	printf("Press 1 or Start to start the application...\n");

	
	waitforbuttonpress(&pressed, &pressedGC);
	if (pressed != WPAD_BUTTON_1 && pressedGC != PAD_BUTTON_START)
	{
		printf("Other button pressed, press any button to exit...\n");
		waitforbuttonpress(NULL, NULL);
		Reboot();
	}

	printf("Performing Step 1\n");

	printf("Patching IOS\n");
	if (!IOSPATCH_Apply()) {
        printf("Unable to initialise the initial patches.\n");
		printf("This either means you didn't follow the download\n");
		printf("and launching instructions correctly, or your IOS\n");
		printf("is not vulnerable for an unknown reason.\n");
		printf("Perhaps you need to update the Homebrew Channel (HBC).\n");
		printf("Installation cannot continue.  Press any button to exit...\n");
        waitforbuttonpress(NULL, NULL);
		Reboot();
    }
	printf("IOS patched\n");
	
	what_to_do();
	return 0;
}