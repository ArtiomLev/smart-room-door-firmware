#include "buttons.h"
#include "config.h"

Button buttons::builtin_btn(BUILTIN_BUTTON);
Button buttons::left_rot_btn(LEFT_ROT_BTN);
Button buttons::right_rot_btn(RIGHT_ROT_BTN);

void buttons::tick() {
    builtin_btn.tick();
    left_rot_btn.tick();
    right_rot_btn.tick();
}