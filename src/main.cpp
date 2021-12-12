#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/interrupt.h>
#include "HardwareSerial.h"
#include "Controller/Controller.h"
#include "Display/Display.h"
#include "Communication/IRCommunication.h"
#include "Game/Game.h"
#include "Communication/ReceivedData.h"
#include "Communication/Frame.h"

int main() {
    sei();
    Serial.begin(9600);

    Controller::init();
    Display::init();
    Game::init();

    IRCommunication::init(38);

    while (true) {
        Controller::update();
        if (ReceivedData::newResultsAvailable()) {
            uint8_t* data = ReceivedData::getResults();
            for (int i = 0; i < 20; ++i) {
                if (data[i] == 0) continue;
                Frame a = Frame(data[i]);
                if (a.getType() == Frame::SEED_TYPE) {
                    Game::startGame(a.getData());
                }
            }
            delete[] data;
        }
    }

    return(0);
}
