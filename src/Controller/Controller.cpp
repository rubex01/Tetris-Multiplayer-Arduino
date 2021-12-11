#include "Controller.h"

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
        // up
    }
    if (Nunchuk.state.joy_x_axis < 128-100) {
        // down
    }
    if (Nunchuk.state.joy_y_axis > 128+100) {
        // right
    }
    if (Nunchuk.state.joy_y_axis < 128-100) {
        // left
    }
}
