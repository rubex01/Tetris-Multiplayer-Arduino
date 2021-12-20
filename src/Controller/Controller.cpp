#include "Controller.h"

#include <Wire.h>
#include "Nunchuk.h"

#define NUNCHUK_ADDRESS 0x52

bool Controller::actionArray[] = {false};

/**
 * Init controller
 */
void Controller::init() {
    Wire.begin();
    Nunchuk.begin(NUNCHUK_ADDRESS);
}

/**
 * Updates state of the nunchuk
 */
void Controller::update() {
    Nunchuk.getState(NUNCHUK_ADDRESS);

    if (Nunchuk.state.joy_x_axis > 128+100) {
        actionArray[0] = true;
        // right
    }
    if (Nunchuk.state.joy_x_axis < 128-100) {
        actionArray[1] = true;
        // left
    }
    if (Nunchuk.state.joy_y_axis > 128+100) {
        actionArray[2] = true;
        // up
    }
    if (Nunchuk.state.joy_y_axis < 128-100) {
        actionArray[3] = true;
        // down
    }
    if (Nunchuk.state.z_button) {
        actionArray[4] = true;
    }
    if (Nunchuk.state.c_button) {
        actionArray[5] = true;
    }
}

/**
 * Returns a bool array that contains the state of every possible action on the nunchuk
 *
 * @return bool *
 */
bool* Controller::getActions() {
    bool* returnArray = new bool[6];
    for (int i = 0; i < 6; ++i) {
        returnArray[i] = actionArray[i];
        actionArray[i] = false;
    }
    return returnArray;
}
