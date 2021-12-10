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
#include "Communication/SendQueue.h"
#include "Communication/ReceivedData.h"

int main()
{
    sei();
    Serial.begin(9600);

    Controller::Init();
    Display::Init();

    IRCommunication::init(38);

    // Delay for demo
    _delay_ms(3000);

    // Data for testing
    SendQueue::addToQueue(84);
    SendQueue::addToQueue(12);
    SendQueue::addToQueue(93);
    SendQueue::addToQueue(45);
    SendQueue::addToQueue(55);
    SendQueue::addToQueue(23);
    SendQueue::addToQueue(65);

    while(true) {
        Display::FillCircle(Character::xPos, Character::yPos, 10, ILI9341_BLACK);
        Controller::Update();
        Display::FillCircle(Character::xPos, Character::yPos, 10, ILI9341_MAGENTA);

        // Demo purpose
        if (ReceivedData::newResultsAvailable()) {
            uint8_t* data = ReceivedData::getResults();
            for (int i = 0; i < 20; ++i) {
                if (data[i] != 0) Serial.println(data[i]);
            }
            delete[] data;
        }
    }

    return(0);
}
