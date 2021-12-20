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

#define ONESECOND 125
volatile uint8_t teller = 0;
volatile int thisNote = 0;

ISR(TIMER2_OVF_vect) {
    teller++;
    if(!NewTone::noNewToneCheck) {
        if (teller >= ONESECOND) {
            // PORTB ^= (1<<PORTB0);
            teller = 0;
            // code
            if (thisNote >= NewTone::notes * 2)
                thisNote = 0;
            // calculates the duration of each note
            NewTone::divider = NewTone::melody[thisNote + 1];
            if (NewTone::divider > 0) {
                // regular note, just proceed
                NewTone::noteDuration = (NewTone::wholenote) / NewTone::divider;
            } else if (NewTone::divider < 0) {
                // dotted notes are represented with negative durations!!
                NewTone::noteDuration = (NewTone::wholenote) / abs(NewTone::divider);
                NewTone::noteDuration *= 1.5;  // increases the duration in half for dotted notes
            }
            NewTone::aNewTone(NewTone::buzzer, NewTone::melody[thisNote], NewTone::noteDuration*0.9);  // timer1 // miss in while

            thisNote = thisNote + 2;
            // code
        }
    }
}
// TEST

int main() {
    // TEST timer 2
    DDRB |= (1 << DDB0);
    TCCR2B |= (1 << CS22)|(1 << CS20);
    TIMSK2 |= (1 << TOIE2);
    TCNT2 = 0;
    // TEST

    sei();
    Serial.begin(9600);

    Controller::init();
    Display::init();
    Scene::setScene(Scene::START_SCENE);

    IRCommunication::init(56);

    // NewTone::aNewTone(NewTone::buzzer, NewTone::melody[thisNote], NewTone::noteDuration*0.9); // toon aan
    // NewTone::noNewTone(NewTone::buzzer); // toon uit

    while (true) {
        Controller::update();
        Scene::draw();
    }

    return(0);
}
