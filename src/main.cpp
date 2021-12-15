#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <Arduino.h>
#include <avr/interrupt.h>
#include "HardwareSerial.h"
#include "Controller/Controller.h"
#include "Display/Display.h"
#include "Communication/IRCommunication.h"
#include "Scenes/GameScene/GameScene.h"
#include "Communication/ReceivedData.h"
#include "Sound/NewTone.h"

//TEST

#define ONESECOND 125
volatile uint8_t teller = 0;
volatile int thisNote = 0;

ISR(TIMER2_OVF_vect) {
    teller++;
    if(teller >= ONESECOND) {
        PORTB ^= (1<<PORTB0);
        teller = 0;
        // code
        if(thisNote >= NewTone::notes * 2)
            thisNote = 0;
        // calculates the duration of each note
        NewTone::divider = NewTone::melody[thisNote + 1];
        if (NewTone::divider > 0) {
            // regular note, just proceed
            NewTone::noteDuration = (NewTone::wholenote) / NewTone::divider;
        } else if (NewTone::divider < 0) {
            // dotted notes are represented with negative durations!!
            NewTone::noteDuration = (NewTone::wholenote) / abs(NewTone::divider);
            NewTone::noteDuration *= 1.5; // increases the duration in half for dotted notes
        }
        NewTone::aNewTone(NewTone::buzzer, NewTone::melody[thisNote], NewTone::noteDuration*0.9); // timer1 // miss in while
        
        thisNote = thisNote + 2;
        //code
    }
}
//TEST

int main()
{
    //TEST
    DDRB |= (1<<DDB0);
    TCCR2B |= (1<<CS22) |(1<<CS20);
    TIMSK2 |= (1<<TOIE2);
    TCNT2 = 0;
    //TEST

#include "Communication/Frame.h"

int main() {
    sei();
    Serial.begin(9600);

    Controller::init();
    Display::init();
    Scene::setScene(Scene::START_SCENE);

    IRCommunication::init(38);

    // int thisNote = 0;
	NewTone::aNewTone(NewTone::buzzer, NewTone::melody[thisNote], NewTone::noteDuration*0.9);

    while(true) {
        Controller::Update();
        // for (thisNote = 0; thisNote < NewTone::notes * 2; thisNote = thisNote + 2) {
			// PORTD |= (1<<PORTD5);
			// _delay_ms(100);
			// PORTD &= ~(1<<PORTD5);
			// _delay_ms(100);

			// calculates the duration of each note
			// NewTone::divider = NewTone::melody[thisNote + 1];
			// if (NewTone::divider > 0) {
			// 	// regular note, just proceed
			// 	NewTone::noteDuration = (NewTone::wholenote) / NewTone::divider;
			// } else if (NewTone::divider < 0) {
			// 	// dotted notes are represented with negative durations!!
			// 	NewTone::noteDuration = (NewTone::wholenote) / abs(NewTone::divider);
			// 	NewTone::noteDuration *= 1.5; // increases the duration in half for dotted notes
			// }

			// we only play the note for 90% of the duration, leaving 10% as a pause
			// tone(buzzer, melody[thisNote], noteDuration*0.9);
			// NewTone::aNewTone(NewTone::buzzer, NewTone::melody[thisNote], NewTone::noteDuration*0.9); // timer1

			// Wait for the specief duration before playing the next note.
			// delay(noteDuration); // timer0
			// _delay_ms(300); // geen timer alst goed is

			// _delay_ms((long)noteDuration);
			// Serial.println(noteDuration);
			
			// // stop the waveform generation before the next note.
			// noNewTone(NewTone::buzzer);
		// }
    while (true) {
        Controller::update();
        Scene::draw();
    }

    return(0);
}
