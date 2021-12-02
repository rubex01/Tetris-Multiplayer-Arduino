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

int main()
{
    Serial.begin(9600);
    sei();

    initIRCommunication(56);

    Controller::Init();
    Display::Init();

    while(true) {
        Controller::Update();
        Display::FillCircle(Character::xPos, Character::yPos, 10, ILI9341_MAGENTA);
        Display::DrawCircle(Character::xPos, Character::yPos, 10, ILI9341_BLACK);
        Display::DrawCircle(Character::xPos, Character::yPos, 11, ILI9341_BLACK);
    }

    return(0);
}
