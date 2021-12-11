#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include "Arduino.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "HardwareSerial.h"
#include "Controller/Controller.h"
#include "Game/Character.h"
#include "Display/Display.h"
#include "Communication/IRCommunication.h"
#include "Game/Game.h"

int main()
{
    Serial.begin(9600);
    sei();

//    initIRCommunication(38);

    Controller::Init();
    Display::init();
    Game::init();

    while(true) {
        Controller::Update();
    }

    return(0);
}
