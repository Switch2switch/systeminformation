#include <3ds.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	consoleClear();
    hidInit();
    gspLcdInit();
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	printf("X: Check your screen types\n");
	printf("Start: Close Application\n\n");
	printf("Software by HB4U Homebrew\n");
	printf("More features coming soon...");

	// Main loop
	while (aptMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		int gobacktomenu() {
			consoleClear();
			return main;
		}
		int tnorips(){
		 consoleClear();
		 
		 //finish making the return to the main function
		 /*
		 maybe try to create a function that loads on start that would maybe avoid all the errors when compiling 
		 the software.
		 */
		 
		 
		 if (kDown & KEY_X) gobacktomenu();
		bool isNew3DS = 0;
    APT_CheckNew3DS(&isNew3DS);
    if (isNew3DS)
    {
        u8 Screens = 0;
        GSPLCD_GetVendors(&Screens);
        
		
        switch ((Screens >> 4) & 0xF)
        {
            case 1:
                printf("Your top screen is IPS\n");
                break;
            case 0xC:
                printf("Your top screen is TN\n");
                break;
            default:
                printf("We don't know what your screen is.\n");
                break;
        }
         switch (Screens & 0xF)
        {
            case 1:
                printf("Your bottom screen is IPS\n");
                break;
            case 0xC:
                printf("Your bottom screen is TN\n");
                break;
            default:
                printf("We don't know what your botton screen is.\n");
                break;
        }
    }
    else
    {
        printf("\nCan't check O3DS Screen vendors.\n");
    }
		 
		 
	}
		if (kDown & KEY_START) break; // break in order to return to hbmenu
		if (kDown & KEY_X) tnorips();
		
		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}
	
	gfxExit();
	return 0;
}
