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
#define ONESECOND 20

ISR(TIMER1_COMPA_vect) {
  if (millis() >= NewTone::_nt_time) NewTone::noNewTone(NewTone::buzzer);  // Check to see if it's time for the note to end.
  *NewTone::_pinOutput ^= NewTone::_pinMask;  // Toggle the pin state.
}

bool NewTone::startTone = false;
bool NewTone::toggleTone = false;
uint8_t NewTone::counter = 0;
uint8_t NewTone::pitchIndex = 0;
uint16_t NewTone::_nt_time;
uint8_t NewTone::_pinMask = 0;
uint8_t NewTone::buzzer = 5;
uint8_t NewTone::prescaler = 0;
uint16_t NewTone::top = 0;
volatile uint8_t *NewTone::_pinOutput = new uint8_t{0};

int NewTone::melody[] {  // Notes of the melody
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

/**
 * Increases counter and checks if needs to play a tone
 */
void NewTone::playTone() {
    NewTone::counter++;
    if (NewTone::counter >= ONESECOND) {
        NewTone::counter = 0;

        if (NewTone::pitchIndex >= 99) {
            NewTone::pitchIndex = 0;
        }

        NewTone::aNewTone(NewTone::buzzer, NewTone::melody[NewTone::pitchIndex], 4);
        NewTone::pitchIndex++;
    }
}

/**
 * Play new tone
 *
 * @param pin
 * @param frequency
 * @param length
 */
void NewTone::aNewTone(uint8_t pin, uint16_t frequency, uint16_t length) {
    NewTone::prescaler = _BV(CS10);
    NewTone::top = F_CPU / frequency / 4 - 1;

    if (NewTone::top > 65535) {
        NewTone::prescaler = _BV(CS12);
        NewTone::top = NewTone::top / 256 - 1;
    }

    if (length > 0) {
        NewTone::_nt_time = millis() + length;
    } else {
        NewTone::_nt_time = 0xFFFF;
    }

    if (NewTone::_pinMask == 0) {
        NewTone::_pinMask = digitalPinToBitMask(pin);
        NewTone::_pinOutput = portOutputRegister(digitalPinToPort(pin));
        uint8_t *_pinMode = (uint8_t *) portModeRegister(digitalPinToPort(pin));
        *_pinMode |= NewTone::_pinMask;
    }

    NewTone::setTimer1();
}

/**
 * Setup timer 1
 */
void NewTone::setTimer1() {
    ICR1 = NewTone::top;
    if (TCNT1 > NewTone::top)
        TCNT1 = NewTone::top;
    TCCR1B  = _BV(WGM13)  | NewTone::prescaler;
    TCCR1A  = _BV(COM1B0);
    TIMSK1 |= _BV(OCIE1A);
}

/**
 * Setup timer 2
 */
void NewTone::initTimer2() {
    DDRB |= (1 << DDB0);
    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22)|(1 << CS21)|(1 << CS20);
    OCR2A = 255;
    TIMSK2 |= (1 << OCIE2A);
}

/**
 * Stops playing music
 *
 * @param pin
 */
void NewTone::noNewTone(uint8_t pin) {
    TIMSK1 &= ~_BV(OCIE1A);   // Remove the timer interrupt.
    TCCR1B  = _BV(CS11);      // Default clock prescaler of 8.
    TCCR1A  = _BV(WGM10);     // Set to defaults so PWM can work like normal (PWM, phase corrected, 8bit).
    *NewTone::_pinOutput &= ~NewTone::_pinMask;  // Set pin to LOW.
    NewTone::_pinMask = 0;  // Flag so we know note is no longer playing.
    NewTone::pitchIndex = 0;
}
