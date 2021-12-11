#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/interrupt.h>
#include "HardwareSerial.h"
#include "Controller/Controller.h"
#include "Game/Character.h"
#include "Display/Display.h"
#include "Communication/IRCommunication.h"

int main() {
    sei();
    Serial.begin(9600);

    Controller::init();
    Display::init();

    IRCommunication::init(38);

    while (true) {
        Display::fillCircle(Character::xPos, Character::yPos, 10, ILI9341_BLACK);
        Controller::update();
        Display::fillCircle(Character::xPos, Character::yPos, 10, ILI9341_MAGENTA);
    }

    return(0);
}
