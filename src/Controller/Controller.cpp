#include "Controller.h"
#include "../Game/Character.h"

#include <Wire.h>
#include "Nunchuk.h"

#define NUNCHUK_ADDRESS 0x52

void Controller::init() {
    Wire.begin();
    Nunchuk.begin(NUNCHUK_ADDRESS);
}

void Controller::update() {
    Nunchuk.getState(NUNCHUK_ADDRESS);

    if (Nunchuk.state.joy_x_axis > 128+100) {
        Character::yPos++;
    }
    if (Nunchuk.state.joy_x_axis < 128-100) {
        Character::yPos--;
    }
    if (Nunchuk.state.joy_y_axis > 128+100) {
        Character::xPos++;
    }
    if (Nunchuk.state.joy_y_axis < 128-100) {
        Character::xPos--;
    }
}
