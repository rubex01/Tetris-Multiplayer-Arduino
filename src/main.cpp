#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/interrupt.h>
#include "HardwareSerial.h"
#include "Controller/Controller.h"
#include "Display/Display.h"
#include "Communication/IRCommunication.h"
#include "Scenes/GameScene/GameScene.h"
#include "Communication/ReceivedData.h"
#include "Communication/Frame.h"

int main() {
    sei();
    Serial.begin(9600);

    Controller::init();
    Display::init();
    Scene::setScene(Scene::WIN_SCENE);

    IRCommunication::init(38);

    while (true) {
        Controller::update();
        Scene::draw();
    }

    return(0);
}
