
// 8bit-Unity SDK
#include "unity.h"

#include <string.h>

#define MSG_COL_COUNT (CHR_COLS - 2)
#define MSG_LINE_COUNT 4

unsigned char* msgLines[MSG_LINE_COUNT];

char *bufferWrappedTextLine(char *s, char x, char y, char w) {
	char *o, ch;
	char tx = x;
	
	char *startOfLine, *endOfLine;
	char currW, bestW, charW, spaceW;
	
	startOfLine = s;
	
	currW = 0;
	bestW = 0;

	// Skips initial spaces for current line
	for (o = startOfLine; *o == ' '; o++) {
		msgLines[y][tx] = ' ';
		tx++;
		currW++;
		bestW = currW;
	}
	startOfLine = o;
	
	if (!*o || currW >= w) {
		msgLines[y][tx] = 0;
		return 0;
	}

	// Scans words that fit the maximum width
	endOfLine = startOfLine;
	for (o = startOfLine; *o && *o != '\n' && currW <= w; o++) {
		ch = *o;
		if (ch == ' ') {
			currW++;
			if (currW <= w) {
				endOfLine = o;
				bestW = currW;
			}
		} else {
			currW++;
		}
	}
	
	// Corner cases: last word in string, and exceedingly long words
	if (currW <= w || !bestW) {
		endOfLine = o;
		bestW = currW;		
	}

	// Renders the line of text
	for (o = startOfLine; o <= endOfLine; o++) {
		ch = *o;
		if (ch && ch != '\n') {
			msgLines[y][tx] = ch;
			tx++;
		}
	}
	
	// Skips spaces at end of line.
	while (*endOfLine == ' ') {
		endOfLine++;
	}

	// Skips one line break, if necessary.
	if (*endOfLine == '\n') {
		endOfLine++;
	}

	msgLines[y][tx] = 0;
	return *endOfLine ? endOfLine : 0;
}

char *bufferWrappedText(char *s, char x, char y, char w, char h) {
	char *o = s;
	char ty = y;
	char maxY = y + h;
	
	while (o && *o && ty < maxY) {
		o = bufferWrappedTextLine(o, x, ty, w);
		ty++;
	}
	
	return o;
}

void bufferClear() {
	unsigned char i;
	
	for (i = 0; i != MSG_LINE_COUNT; i++) {
		msgLines[i][0] = 0;
	}
}

int main (void) 
{
	unsigned char i;
	char *s;
	
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
		strcpy(msgLines[i], "");
	}
	
	// Main Loop
	while (1) {
		s = "This is a test with really long lines let's see if they wrap correctly.\nI hope they do.\nHere's another line...\nAnd another.\n\
		Here's yet another line added to test if the line wrapping is working.";
		while (s) {
			bufferClear();
			s = bufferWrappedText(s, 0, 0, MSG_COL_COUNT, MSG_LINE_COUNT);			
			
			paperColor = BLACK;
			inkColor = CYAN;	
			ListBox(1, CHR_ROWS - MSG_LINE_COUNT - 4, MSG_COL_COUNT, MSG_LINE_COUNT + 2, "Character name", msgLines, MSG_LINE_COUNT);	
			
			cgetc();
			while (kbhit()) { cgetc(); }
		}
	}
    	
    // Done
    return EXIT_SUCCESS;
}
