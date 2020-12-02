
// 8bit-Unity SDK
#include "unity.h"

#define LINE_COUNT 4

unsigned char* listNames[16] = {
	"Line 1", "Line 2", "Line 3", "Line 4"
};

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
	inkColor = CYAN;	
	ListBox(1, CHR_ROWS - LINE_COUNT - 4, CHR_COLS - 2, LINE_COUNT + 2, "Character name", listNames, LINE_COUNT);
	
	// Main Loop
	while (1) {
	}
    	
    // Done
    return EXIT_SUCCESS;
}
