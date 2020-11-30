#include "script.h"

extern uint16 vg_lecturehall[];

extern uint16 vg_sylvie_giggle[];

extern uint16 vg_club[];

const uint16 *vi_lecturehall = vg_lecturehall;
const uint16 *vi_sylvie_giggle = vg_sylvie_giggle;
const uint16 *vi_club = vg_club;

int gv_val;
int gv_variable;

extern void *vn_another_scene();

void *vn_another_scene() {
  vnScene(vi_lecturehall);
  vnShow(vi_sylvie_giggle);
  vnText("Seems to be working.");
  if (gv_variable == 1) {
    vnText("You chose option 1 previously!");

  } else if (gv_variable == 2) {
    vnText("You chose option 2 previously!");
  }

  return vn_start;
}


void *vn_start()
{
  vnScene(vi_club);
  vnShow(vi_sylvie_giggle);
  gv_val = 456;
  vnTextF("Ok %d", gv_val);
  vnText("Hello.");
  vnText("This is a demonstration of BlocklyVN32X.");
  vnText("Combined with vn32x, it allows you to build visual novels for te Sega 32X.");
  {
    int mn_option_1, mn_choice_2, mn_choice_3;

    initMenu();

    mn_choice_2 = addMenuItem("Option 1");
    mn_choice_3 = addMenuItem("Option 2");

    mn_option_1 = vnMenu();

    if (mn_option_1 == mn_choice_2) {
      vnText("xxxx");
      gv_variable = 1;

    }

    if (mn_option_1 == mn_choice_3) {
      vnText("zzzz");
      gv_variable = 2;

    }
  }
  return vn_another_scene;


  return vn_start;
}