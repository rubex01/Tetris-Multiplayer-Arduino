#include "Controller.h"
#include "../Game/Character.h"

#define NUNCHUK_ADDRESS 0x52

void Controller::Init(){
    Wire.begin();
    Nunchuk.begin(NUNCHUK_ADDRESS);
}

void Controller::Update(){
    Nunchuk.getState(NUNCHUK_ADDRESS);

    if(Nunchuk.state.joy_x_axis > 128+100){
        Character::yPos+=1;
    }
    if(Nunchuk.state.joy_x_axis < 128-100){
        Character::yPos-=1;
    }
    if(Nunchuk.state.joy_y_axis > 128+100){
        Character::xPos+=1;
    }
    if(Nunchuk.state.joy_y_axis < 128-100){
        Character::xPos-=1;
    }
}