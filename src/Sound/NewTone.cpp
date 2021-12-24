// ---------------------------------------------------------------------------
// Created by Tim Eckel - teckel@leethost.com
// Copyright 2013 License: GNU GPL v3 http://www.gnu.org/licenses/gpl-3.0.html
//
// See "NewTone.h" for purpose, syntax, version history, links, and more.
// ---------------------------------------------------------------------------
#include "HardwareSerial.h"
#include "NewTone.h"

#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define REST 0
#define ONESECOND 20  // Timer2

ISR(TIMER1_COMPA_vect) {  // Timer interrupt vector.
  if (millis() >= NewTone::_nt_time) NewTone::noNewTone(NewTone::buzzer);  // Check to see if it's time for the note to end.
  *NewTone::_pinOutput ^= NewTone::_pinMask;  // Toggle the pin state.
}

bool NewTone::startTone = false;
bool NewTone::toggleTone = false;
uint8_t NewTone::teller = 0;
uint8_t NewTone::toonHoogteIndex = 0;
uint16_t NewTone::_nt_time;               // Time note should end.
uint8_t NewTone::_pinMask = 0;            // Pin bitmask.
volatile uint8_t *NewTone::_pinOutput = new uint8_t{0};  // Output port register
uint8_t NewTone::buzzer = 5;                  // Change this to whichever pin you want to use
uint8_t NewTone::prescaler = 0;
uint16_t NewTone::top = 0;

int NewTone::melody[] {  // Notes of the moledy
    NOTE_E5,  NOTE_B4,  NOTE_C5,  NOTE_D5,  NOTE_C5,  NOTE_B4,
    NOTE_A4,  NOTE_A4,  NOTE_C5,  NOTE_E5,  NOTE_D5,  NOTE_C5,
    NOTE_B4,  NOTE_C5,  NOTE_D5,  NOTE_E5,
    NOTE_C5,  NOTE_A4,  NOTE_A4,  NOTE_A4,  NOTE_B4,  NOTE_C5,

    NOTE_D5,  NOTE_F5,  NOTE_A5,  NOTE_G5,  NOTE_F5,
    NOTE_E5,  NOTE_C5,  NOTE_E5,  NOTE_D5,  NOTE_C5,
    NOTE_B4,  NOTE_B4,  NOTE_C5,  NOTE_D5,  NOTE_E5,
    NOTE_C5,  NOTE_A4,  NOTE_A4,  REST,

    NOTE_E5,  NOTE_B4,  NOTE_C5,  NOTE_D5,  NOTE_C5,  NOTE_B4,
    NOTE_A4,  NOTE_A4,  NOTE_C5,  NOTE_E5,  NOTE_D5,  NOTE_C5,
    NOTE_B4,  NOTE_C5,  NOTE_D5,  NOTE_E5,
    NOTE_C5,  NOTE_A4,  NOTE_A4,  NOTE_A4,  NOTE_B4,  NOTE_C5,

    NOTE_D5,  NOTE_F5,  NOTE_A5,  NOTE_G5,  NOTE_F5,
    NOTE_E5,  NOTE_C5,  NOTE_E5,  NOTE_D5,  NOTE_C5,
    NOTE_B4,  NOTE_B4,  NOTE_C5,  NOTE_D5,  NOTE_E5,
    NOTE_C5,  NOTE_A4,  NOTE_A4,  REST,

    NOTE_E5,  NOTE_C5,
    NOTE_D5,  NOTE_B4,
    NOTE_C5,  NOTE_A4,
    NOTE_GS4, NOTE_B4,  REST,
    NOTE_E5,  NOTE_C5,
    NOTE_D5,  NOTE_B4,
    NOTE_C5,  NOTE_E5,  NOTE_A5,
    NOTE_GS5
};

void NewTone::playTone() {
    NewTone::teller++;
    if (NewTone::teller >= ONESECOND) {
        NewTone::teller = 0;

        if(NewTone::toonHoogteIndex >= 99) {
            NewTone::toonHoogteIndex = 0;
        }

        NewTone::aNewTone(NewTone::buzzer, NewTone::melody[NewTone::toonHoogteIndex], 4);
        NewTone::toonHoogteIndex++;
    }
}

void NewTone::aNewTone(uint8_t pin, uint16_t frequency, uint16_t length) {
    NewTone::prescaler = _BV(CS10);
    NewTone::top = F_CPU / frequency / 4 - 1;  // Calculate the top.

    if (NewTone::top > 65535) {                              // If not in the range for prescaler 1, use prescaler 256 (61 Hz and lower @ 16 MHz).
        NewTone::prescaler = _BV(CS12);                        // Set the 256 prescaler bit.
        NewTone::top = NewTone::top / 256 - 1;                          // Calculate the top using prescaler 256.
    }

    if (length > 0) {
        NewTone::_nt_time = millis() + length;
    } else {
        NewTone::_nt_time = 0xFFFF;  // Set when the note should end, or play "forever".
    }

    if (NewTone::_pinMask == 0) {
        NewTone::_pinMask = digitalPinToBitMask(pin);                     // Get the port register bitmask for the pin.
        NewTone::_pinOutput = portOutputRegister(digitalPinToPort(pin));  // Get the output port register for the pin.
        uint8_t *_pinMode = (uint8_t *) portModeRegister(digitalPinToPort(pin));  // Get the port mode register for the pin.
        *_pinMode |= NewTone::_pinMask;  // Set the pin to OutputW mode.
    }

    NewTone::setTimer1();
}

void NewTone::setTimer1() {
    ICR1 = NewTone::top;                      // Set the top.
    if (TCNT1 > NewTone::top) {
        TCNT1 = NewTone::top;           }           // Counter over the top, put within range.
    TCCR1B  = _BV(WGM13)  | NewTone::prescaler;  // Set PWM, phase and frequency corrected (ICR1) and prescaler.
    TCCR1A  = _BV(COM1B0);
    TIMSK1 |= _BV(OCIE1A);
}

void NewTone::initTimer2() {
    DDRB |= (1 << DDB0);
    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22)|(1 << CS21)|(1 << CS20);
    OCR2A = 255;
    TIMSK2 |= (1 << OCIE2A);
}

void NewTone::noNewTone(uint8_t pin) {
    TIMSK1 &= ~_BV(OCIE1A);   // Remove the timer interrupt.
    TCCR1B  = _BV(CS11);      // Default clock prescaler of 8.
    TCCR1A  = _BV(WGM10);     // Set to defaults so PWM can work like normal (PWM, phase corrected, 8bit).
    *NewTone::_pinOutput &= ~NewTone::_pinMask;  // Set pin to LOW.
    NewTone::_pinMask = 0;  // Flag so we know note is no longer playing.
    NewTone::toonHoogteIndex =0;
}
