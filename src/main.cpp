#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include "Arduino.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "HardwareSerial.h"
#include "Controller.h"
#include "Character.h"
#include "Display.h"
#include "Communication/IRCommunication.h"

int main()
{
    Serial.begin(9600);

    sei();

    initIRCommunication(56);

    Controller::Init();
    Display::Init();

    while(true) {
        Display::FillCircle(Character::xPos, Character::yPos, 10, ILI9341_BLACK);
        Controller::Update();
        Display::FillCircle(Character::xPos, Character::yPos, 10, ILI9341_MAGENTA);
        _delay_ms(50);
    }

    return(0);
}
