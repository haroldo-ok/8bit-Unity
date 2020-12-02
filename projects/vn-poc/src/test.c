
// 8bit-Unity SDK
#include "unity.h"

#include <string.h>

#define MSG_COL_COUNT (CHR_COLS - 2)
#define MSG_LINE_COUNT 4

unsigned char* msgLines[MSG_LINE_COUNT];

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
	
	for (i = 0; i != MSG_LINE_COUNT; i++) {
		msgLines[i] = malloc(MSG_COL_COUNT);
		strcpy(msgLines[i], "This is a line");
	}
	
	paperColor = BLACK;
	inkColor = CYAN;	
	ListBox(1, CHR_ROWS - MSG_LINE_COUNT - 4, MSG_COL_COUNT, MSG_LINE_COUNT + 2, "Character name", msgLines, MSG_LINE_COUNT);
	
	// Main Loop
	while (1) {
	}
    	
    // Done
    return EXIT_SUCCESS;
}
