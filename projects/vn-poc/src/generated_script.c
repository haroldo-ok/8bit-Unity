#include "script.h"

/*
const char *vi_lecturehall = "lecturehall.img";
const char *vi_sylvie_giggle = "sylvie_giggle.img";
const char *vi_club = "club.img";
const char *vi_sylvie_normal = "sylvie_normal.img";
*/
const char *vi_lecturehall = "menu.img";
const char *vi_sylvie_giggle = "sylvie_giggle.img";
const char *vi_club = "arizona.img";
const char *vi_sylvie_normal = "sylvie_normal.img";

int gv_val;
int gv_variable;

extern void *vn_another_scene();

void *vn_another_scene() {
  int mn_option_1, mn_choice_2, mn_choice_3;
  int mn_option_4, mn_choice_5, mn_choice_6;

  vnScene(vi_lecturehall);
  vnShow(vi_sylvie_giggle);
  vnText("Seems to be working.");
  if (gv_variable == 1) {
    vnText("You chose option 1 previously!");

  } else if (gv_variable == 2) {
    vnText("You chose option 2 previously!");
  }
  {

    initMenu();

    mn_choice_2 = addMenuItem("One option");
    mn_choice_3 = addMenuItem("Another option");

    mn_option_1 = vnMenu();

    if (mn_option_1 == mn_choice_2) {

    }

    if (mn_option_1 == mn_choice_3) {

    }
  }
  {

    initMenu();

    mn_choice_5 = addMenuItem("One more option");
    mn_choice_6 = addMenuItem("Yet another option");

    mn_option_4 = vnMenu();

    if (mn_option_4 == mn_choice_5) {

    }

    if (mn_option_4 == mn_choice_6) {

    }
  }

  return vn_start;
}


void *vn_start()
{
  int mn_option_7, mn_choice_8, mn_choice_9;

  vnScene(vi_club);
  vnShow(vi_sylvie_normal);
  gv_val = 456;
  vnTextF("Ok %d", gv_val);
  vnText("Hello.");
  vnText("This is a demonstration of BlocklyVN32X.");
  vnText("Combined with vn32x, it allows you to build visual novels for te Sega 32X.");
  {

    initMenu();

    mn_choice_8 = addMenuItem("Option 1");
    mn_choice_9 = addMenuItem("Option 2");

    mn_option_7 = vnMenu();

    if (mn_option_7 == mn_choice_8) {
      vnText("xxxx");
      gv_variable = 1;

    }

    if (mn_option_7 == mn_choice_9) {
      vnText("zzzz");
      gv_variable = 2;

    }
  }
  return vn_another_scene;


  return vn_start;
}