#include "Controller.h"

#include <Wire.h>
#include "Nunchuk.h"

#define NUNCHUK_ADDRESS 0x52

bool Controller::actionArray[] = {false};
bool Controller::nonContinuingTrigger[] = {false};

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
    for (int i = 0; i < 2; ++i) {
        Nunchuk.getState(NUNCHUK_ADDRESS);
        updateStates();
    }
}

/**
 * Update the state of every button
 */
void Controller::updateStates() {
    if (Nunchuk.state.joy_y_axis > 128+100) {
        actionArray[UP] = true;
    } else if (actionArray[UP]) {
        nonContinuingTrigger[UP] = true;
    }

    if (Nunchuk.state.joy_y_axis < 128-100) {
        actionArray[DOWN] = true;
    } else if (actionArray[DOWN]) {
        nonContinuingTrigger[DOWN] = true;
    }

    if (Nunchuk.state.joy_x_axis < 128-100) {
        actionArray[LEFT] = true;
    } else if (actionArray[LEFT]) {
        nonContinuingTrigger[LEFT] = true;
    }

    if (Nunchuk.state.joy_x_axis > 128+100) {
        actionArray[RIGHT] = true;
    } else if (actionArray[RIGHT]) {
        nonContinuingTrigger[RIGHT] = true;
    }

    if (Nunchuk.state.z_button) {
        actionArray[Z_BUTTON] = true;
    } else if (actionArray[Z_BUTTON]) {
        nonContinuingTrigger[Z_BUTTON] = true;
    }

    if (Nunchuk.state.c_button) {
        actionArray[C_BUTTON] = true;
    } else if (actionArray[C_BUTTON]) {
        nonContinuingTrigger[C_BUTTON] = true;
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

bool* Controller::getNonContinuingTriggerActions() {
    bool* returnArray = new bool[6];
    for (int i = 0; i < 6; ++i) {
        returnArray[i] = nonContinuingTrigger[i];
        actionArray[i] = false;
        nonContinuingTrigger[i] = false;
    }
    return returnArray;
}
