/*
	Circle Pad Pro example based on examples provided in libctru,
	and using source code from Red Viper written by Skyfloogle.
*/

#include<3ds.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "cpp.h" //for cpp services
#include "extrapad.h" //for applet extrapad


int main(int argc, char **argv){
	// Initialize services
	gfxInitDefault(); // gfx

	//Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	consoleInit(GFX_TOP, NULL);

	aptInit();        // applets
	// if(R_FAILED(aptInit())) hang("Error: aptInit()"); //better but not necessary

	hidInit();    // input
	// if(R_FAILED(hidInit())) hang("Error: hidInit()"); //better but not necessary

	bool cppToggle = false;
	bool cppConnected = cppGetConnected();
	char cppSearch[2][9]={"unactive","active  "};
	char cppConnection[2][14]={"not connected","connected    "};
	u8 cppBatteryPercentage = 0; //the percentage of the battery of Circle Pad Pro

	bool new3ds = false;
	APT_CheckNew3DS(&new3ds);//test if the console is a new 3ds

	printf("\x1b[2;1HPress Start to exit.");
	printf("\x1b[4;1HCircle Pad position:          x: +000  y: +000");
	printf("\x1b[6;1Hpress X to toggle the Circle Pad Pro: %s",cppSearch[cppToggle]);
	printf("\x1b[7;1HCircle Pad Pro state: %s",cppConnection[cppConnected]);
	printf("\x1b[8;1HCircle Pad Pro battery:    ");

	printf("\x1b[10;1Hpress A to calibrate the Circle Pad Pro");

	printf("\x1b[12;1HCircle Pad Pro position (old): x: +000  y: +000");

	printf("\x1b[14;1HZR Circle Pad Pro:");
	printf("\x1b[15;1HZL Circle Pad Pro:"); 
	printf("\x1b[16;1HR  Circle Pad Pro:"); 

	printf("\x1b[18;1HCPAD_UP:");
	printf("\x1b[19;1HCPAD_RIGHT:");
	printf("\x1b[20;1HCPAD_DOWN:");
	printf("\x1b[21;1HCPAD_LEFT:");
		
	printf("\x1b[18;20HCSTICK_UP/CPP:");
	printf("\x1b[19;20HCSTICK_RIGHT/CPP:");
	printf("\x1b[20;20HCSTICK_DOWN/CPP:");
	printf("\x1b[21;20HCSTICK_LEFT/CPP:");

	printf("\x1b[23;1Hcstick position (new):         x:+000  y:+000");
	printf("\x1b[25;1HZR new3ds:");
	printf("\x1b[26;1HZL new3ds:"); 


	while(aptMainLoop()) {
		hidScanInput();
		
		//hidKeysHeld returns information about which buttons have are held down in this frame
		u32 kHeld = hidKeysHeld();
		
		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();

		if(kHeld & KEY_START) break;

		circlePosition circlePad;
		//Read the Circle Pad position (see "reads-controls" from libctru's examples)
		hidCircleRead(&circlePad);
		printf("\x1b[4;1HCircle Pad position:           x: %+04d  y: %+04d",circlePad.dx, circlePad.dy);
		if (kHeld & KEY_CPAD_UP) printf("\x1b[18;1HCPAD_UP:    held");
		else printf("\x1b[18;1HCPAD_UP:        ");
		if (kHeld & KEY_CPAD_RIGHT) printf("\x1b[19;1HCPAD_RIGHT: held");
		else printf("\x1b[19;1HCPAD_RIGHT:     ");
		if (kHeld & KEY_CPAD_DOWN) printf("\x1b[20;1HCPAD_DOWN:  held");
		else printf("\x1b[20;1HCPAD_DOWN:      ");
		if (kHeld & KEY_CPAD_LEFT) printf("\x1b[21;1HCPAD_LEFT:  held");
		else printf("\x1b[21;1HCPAD_LEFT:      ");

		if (kDown & KEY_A){ // run the applet program for the calibration of cpp. It doesn't work with the cstick yet.
			if (cppToggle) cppExit(); //warning this is important (if using cpp) otherwise the applet will crash
            extraPadConf conf;
            extraPadInit(&conf);
            extraPadLaunch(&conf);
			if (cppToggle) cppInit();
		} 
		if(!new3ds){
			if(cppConnected){
				kHeld |= cppKeysHeld(); //binary or to add input from Circle Pad Pro
			}
			circlePosition circlePadPro;

			//Read the Circle Pad Pro position
			cppCircleRead(&circlePadPro);
			if (circlePadPro.dx >= 41) kHeld |= KEY_CSTICK_RIGHT;
			else if (circlePadPro.dx <= -41) kHeld |= KEY_CSTICK_LEFT;
			if (circlePadPro.dy >= 41) kHeld |= KEY_CSTICK_UP;
			else if (circlePadPro.dy <= -41) kHeld |= KEY_CSTICK_DOWN;

			if (kDown & KEY_X){
				cppToggle = !cppToggle;
				cppToggle ? cppInit() : cppExit(); //initialise or exit circle pad pro connection service
				printf("\x1b[6;1Hpress X to toggle the Circle Pad Pro: %s",cppSearch[cppToggle]);
			}
			cppConnected = cppGetConnected();
			printf("\x1b[7;1HCircle Pad Pro state: %s",cppConnection[cppConnected]);

			if(cppConnected){
				cppBatteryPercentage = (cppBatteryLevel() * 100) / 255;
				printf("\x1b[8;1HCircle Pad Pro battery: %d%%", cppBatteryPercentage);
			}
			else printf("\x1b[8;1HCircle Pad Pro battery:     ");
			
			printf("\x1b[12;1HCircle Pad Pro position (old): x: %+04d  y: %+04d",circlePadPro.dx, circlePadPro.dy);
			
			if(cppConnected){
				if(kHeld & KEY_ZR) printf("\x1b[14;1HZR Circle Pad Pro: held");
				else printf("\x1b[14;1HZR Circle Pad Pro:     ");
				if(kHeld & KEY_ZL) printf("\x1b[15;1HZL Circle Pad Pro: held");
				else printf("\x1b[15;1HZL Circle Pad Pro:     "); 
				if(kHeld & KEY_R) printf("\x1b[16;1HR  Circle Pad Pro: held");
				else printf("\x1b[16;1HR  Circle Pad Pro:     "); 
			}
		}
		else{
			circlePosition cStick;

			//Read the cstick(new3ds) position
			hidCstickRead(&cStick);
		
			printf("\x1b[23;1Hcstick position (new):         x: %+04d  y: %+04d",cStick.dx, cStick.dy);
			if(kHeld & KEY_ZR) printf("\x1b[25;1HZR new3ds: held");
			else printf("\x1b[25;1HZR new3ds:     ");
			if(kHeld & KEY_ZL) printf("\x1b[26;1HZL new3ds: held");
			else printf("\x1b[26;1HZL new3ds:     "); 
		}
		if (kHeld & KEY_CSTICK_UP) printf("\x1b[18;20HCSTICK_UP/CPP:    held");
		else printf("\x1b[18;20HCSTICK_UP/CPP:        ");
		if (kHeld & KEY_CSTICK_RIGHT) printf("\x1b[19;20HCSTICK_RIGHT/CPP: held");
		else printf("\x1b[19;20HCSTICK_RIGHT/CPP:     ");
		if (kHeld & KEY_CSTICK_DOWN) printf("\x1b[20;20HCSTICK_DOWN/CPP:  held");
		else printf("\x1b[20;20HCSTICK_DOWN/CPP:      ");
		if (kHeld & KEY_CSTICK_LEFT) printf("\x1b[21;20HCSTICK_LEFT/CPP:  held");
		else printf("\x1b[21;20HCSTICK_LEFT/CPP:      ");
		
    	
		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	// Exit services
	if (cppToggle) cppExit();
	aptExit();
	hidExit();
	gfxExit();

	return 0;
}