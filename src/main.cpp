#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include "Arduino.h"
#include <avr/interrupt.h>
#include "HardwareSerial.h"
#include "Controller/Controller.h"
#include "Display/Display.h"
#include "Communication/IRCommunication.h"
#include "Scenes/GameScene/GameScene.h"
#include "Communication/ReceivedData.h"
#include "Sound/NewTone.h"
#include "Communication/Frame.h"

// TEST


// volatile uint8_t teller = 0;
// volatile int thisNote = 0;


// TEST

int main() {
    // TEST timer 2
    // DDRB |= (1 << DDB0);
    // TCCR2B |= (1 << CS22)|(1 << CS20);
    // TIMSK2 |= (1 << TOIE2);
    // TCNT2 = 0;
    // TEST
    NewTone::initTimer2();

    sei();
    Serial.begin(9600);

    Controller::init();
    Display::init();
    Scene::setScene(Scene::START_SCENE);

    IRCommunication::init(56);

    // NewTone::aNewTone(NewTone::buzzer, NewTone::melody[NewTone::thisNote], NewTone::noteDuration*0.9); // toon aan
    // NewTone::noNewTone(NewTone::buzzer); // toon uit

    while (true) {
        Controller::update();
        Scene::draw();
    }

    return(0);
}
