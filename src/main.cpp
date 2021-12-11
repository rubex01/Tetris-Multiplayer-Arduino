#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/interrupt.h>
#include "HardwareSerial.h"
#include "Controller/Controller.h"
#include "Display/Display.h"
#include "Communication/IRCommunication.h"
#include "Game/Game.h"

int main() {
    sei();
    Serial.begin(9600);

    Controller::init();
    Display::init();
    Game::init();

    IRCommunication::init(38);

    while (true) {
        Controller::update();
    }

    return(0);
}
