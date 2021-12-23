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
#include <avr/eeprom.h>

int main() {
    sei();
    Serial.begin(9600);

    Controller::init();
    Display::init();
    Scene::setScene(Scene::START_SCENE);

    IRCommunication::init(38);

    eeprom_write_word((uint16_t*) 0x00, (uint16_t) 0);
    uint16_t a = eeprom_read_word((uint16_t*)0x01);
    Serial.println(a);

    while (true) {
        Controller::update();
        Scene::draw();
    }

    return(0);
}
