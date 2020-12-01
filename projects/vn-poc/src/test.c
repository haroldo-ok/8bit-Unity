
// 8bit-Unity SDK
#include "unity.h"

int main (void) 
{
	unsigned char i;
	
	// Reset screen
	clrscr();
	bordercolor(COLOR_BLACK);
    bgcolor(COLOR_BLACK);

	// Initialize modules
	InitJoy();
	InitBitmap();

    LoadBitmap("menu.img");
	EnterBitmapMode();
	
	paperColor = BLACK;
	for (i=1; i< 15; i++) {
		inkColor = i;
		PrintStr(15, i+1, "Hello, 8BIT-UNITY");
	}
	
	// Main Loop
	while (1) {
	}
    	
    // Done
    return EXIT_SUCCESS;
}
