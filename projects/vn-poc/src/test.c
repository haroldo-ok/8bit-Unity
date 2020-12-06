
// 8bit-Unity SDK
#include "unity.h"
#include "menu.h"
#include "vn_engine.h"

#include <string.h>

const char *vi_club = "menu.img";
const char *vi_lecturehall = "arizona.img";
const char *vi_sylvie_giggle = "sylvie_giggle.img";

int main (void) 
{
	unsigned char i;
    int mn_option_1, mn_choice_2, mn_choice_3;
	
	initVN();
	
	// Main Loop
	while (1) {
		vnScene(vi_club);
		vnShow(vi_sylvie_giggle);
		vnChar("Sylvie");
		
		vnText("Testing the VN engine.");
		  
		initMenu();

		mn_choice_2 = addMenuItem("Option 1");
		mn_choice_3 = addMenuItem("Option 2");

		mn_option_1 = vnMenu();

		if (mn_option_1 == mn_choice_2) {
		  vnText("You chose option one");
		}

		if (mn_option_1 == mn_choice_3) {
		  vnText("You chose option two");
		}

		vnTextF("Test number format %d -- %d", 4, 5);
		vnText("This is a test with really long lines let's see if they wrap correctly.\nI hope they do.\nHere's another line...\nAnd another.\n\
		Here's yet another line added to test if the line wrapping is working.");
	}
    	
    // Done
    return EXIT_SUCCESS;
}
