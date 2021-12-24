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

// #define ONESECOND 15  // Timer2 15 goeie, 1024 pre met ovf
#define ONESECOND 20  // Timer2 15 goeie, 1024 pre met COMPA zonder pauze

// ISR(TIMER2_COMPA_vect) {

//     NewTone::teller++;
//     if (!NewTone::noNewToneCheck) {
//         if (NewTone::teller >= ONESECOND) {
//             NewTone::teller = 0;
//             if (NewTone::thisNote >= NewTone::notes * 2)
//                 NewTone::thisNote = 0;
//             // calculates the duration of each note
//             NewTone::divider = NewTone::melody[NewTone::thisNote + 1];
//             if (NewTone::divider > 0) {
//                 // regular note, just proceed
//                 NewTone::noteDuration = (NewTone::wholenote) / NewTone::divider;
//             } else if (NewTone::divider < 0) {
//                 // dotted notes are represented with negative durations!!
//                 NewTone::noteDuration = (NewTone::wholenote) / abs(NewTone::divider);
//                 NewTone::noteDuration *= 1.5;  // increases the duration in half for dotted notes
//             }
//             NewTone::aNewTone(NewTone::buzzer, NewTone::melody[NewTone::thisNote], NewTone::noteDuration*0.9);  // timer1 // miss in while

//             NewTone::thisNote = NewTone::thisNote + 2;
//         }
//     }
// }
#define ONESECOND 20 
int main() {
    sei();
    Serial.begin(9600);

    Controller::init();
    Display::init();
    Scene::setScene(Scene::START_SCENE);

    IRCommunication::init(56);

    // TCCR2A |= (1 << WGM21);
    // TCCR2B |= (1 << CS22)|(1 << CS20);
    // TIMSK2 |= (1 << TOIE2);
    
    // DDRB |= (1 << DDB0);
    // TCCR2B |= (1 << CS22)|(1 << CS21)|(1 << CS20);
    // TIMSK2 |= (1 << TOIE2);
    // TCNT2 = 0;

    // code!!
    DDRB |= (1 << DDB0);
    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22)|(1 << CS21)|(1 << CS20);
    OCR2A = 255;
    TIMSK2 |= (1 << OCIE2A);
    // code
    
    // TCNT2 = 0;


    // NewTone::aNewTone(NewTone::buzzer, NewTone::melody[NewTone::thisNote], NewTone::noteDuration*0.9); // toon aan
    // NewTone::noNewTone(NewTone::buzzer); // toon uit

    while (true) {
        Controller::update();
        Scene::draw();
        if (NewTone::startTone) {
            if (NewTone::toggleTone) {
                // NewTone::testbool = false;
                NewTone::toggleTone = false;
                NewTone::testFunction();
            }   
        }
    }

    return(0);
}
