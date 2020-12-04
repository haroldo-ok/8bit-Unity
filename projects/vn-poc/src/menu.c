#include "menu.h"

#define MENU_ENTRY_COUNT 8

typedef struct _menuEntry {
	unsigned char *s;
	unsigned char idx;
} menuEntry;

menuEntry menuEntries[MENU_ENTRY_COUNT];
unsigned char usedMenuEntries;
unsigned char menuCursor;

void initMenu() {
	usedMenuEntries = 0;
	menuCursor = 1;	
}

unsigned char addMenuItem(char *s) {
	menuEntry *m = menuEntries + usedMenuEntries;
	usedMenuEntries++;

	m->s = s;
	m->idx = usedMenuEntries;
	
	return m->idx;
}

unsigned char drawMenu() {
	menuEntry *m = menuEntries;
	int i, y;
	char selected;
	
	y = (CHR_ROWS - usedMenuEntries - 2) >> 1;
	Panel(1, y, CHR_COLS - 2, usedMenuEntries + 1, "");
	y++;
	
	for (i = 0; i < usedMenuEntries; i++, y++, m++) {
		selected = m->idx == menuCursor;
		
		PrintNum(1, y, i + 1);
		PrintStr(3, y, m->s);
		/*
		translucentRectangle(8, y, 304, 32, !selected ? 0 : COLOR(3, 3, 3));
		drawWrappedText(m->s, 12, y, 300, 32, !selected ? 0x7FFF : COLOR(0x1F, 0x1F, 0x0F));
		*/
	}
}

unsigned int menuItemCount() {
	return usedMenuEntries;
}