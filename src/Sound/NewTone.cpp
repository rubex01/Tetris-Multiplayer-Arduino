// ---------------------------------------------------------------------------
// Created by Tim Eckel - teckel@leethost.com
// Copyright 2013 License: GNU GPL v3 http://www.gnu.org/licenses/gpl-3.0.html
//
// See "NewTone.h" for purpose, syntax, version history, links, and more.
// ---------------------------------------------------------------------------
#include "HardwareSerial.h"
#include "NewTone.h"

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0
#define ONESECOND 20  // Timer2

bool NewTone::noNewToneCheck = true;

bool NewTone::startTone = false;
bool NewTone::toggleTone = false;

uint8_t NewTone::teller = 0;  // Timer2
int NewTone::thisNote = 2;

int maat = 0; 

void NewTone::testFunction() {
  // int yes = maat;
  //Serial.println(yes);  
  
  // if(NewTone::testbool){
    NewTone::teller++;
    // if (!NewTone::noNewToneCheck) {
        if (NewTone::teller >= ONESECOND) {
            NewTone::teller = 0;
            // if (maat >= NewTone::notes * 2 + 1)
            //     // maat = 0;
            if(maat >= 99) {
              maat = 0;
            }
            
            // // calculates the duration of each note
            // NewTone::divider = NewTone::melody[NewTone::thisNote + 1];
            // // NewTone::noteDurationTest = 2;
            // NewTone::setNoteDurationTest();
            // if (NewTone::divider > 0) {
            //     // regular note, just proceed
            //     NewTone::noteDuration = (NewTone::wholenote) / NewTone::divider;
            // } else if (NewTone::divider < 0) {
            //     // dotted notes are represented with negative durations!!
            //     NewTone::noteDuration = (NewTone::wholenote) / abs(NewTone::divider);
            //     NewTone::noteDuration *= 1.5;  // increases the duration in half for dotted notes
            // }
            // NewTone::aNewTone(NewTone::buzzer, NewTone::melody[NewTone::thisNote], NewTone::noteDuration*0.9);  // timer1 // miss in while
            NewTone::a2NewTone(NewTone::buzzer, NewTone::testmelody[maat], 4);
            // yes += 2;
            maat = maat + 1;
        }
    // }
  // }
}

ISR(TIMER1_COMPA_vect) {  // Timer interrupt vector.
  if (millis() >= NewTone::_nt_time) NewTone::noNewTone();  // Check to see if it's time for the note to end.
  *NewTone::_pinOutput ^= NewTone::_pinMask;  // Toggle the pin state.
}

uint16_t NewTone::_nt_time;       // Time note should end.
uint8_t NewTone::_pinMask = 0;         // Pin bitmask.
volatile uint8_t *NewTone::_pinOutput = new uint8_t{0};  // Output port register

// change this to make the song slower or faster
// int NewTone::wholenote = (60000 * 4) / tempo;
int NewTone::tempo = 108;
// change this to whichever pin you want to use
int NewTone::buzzer = 5;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int NewTone::testmelody[] {
  NOTE_E5, NOTE_B4,   NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4,
  NOTE_A4,  NOTE_A4,  NOTE_C5,  NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4,  NOTE_C5,  NOTE_D5,  NOTE_E5,
  NOTE_C5,   NOTE_A4,  NOTE_A4,  NOTE_A4,  NOTE_B4, NOTE_C5,

  NOTE_D5,  NOTE_F5,   NOTE_A5, NOTE_G5,   NOTE_F5, 
  NOTE_E5,   NOTE_C5,  NOTE_E5,  NOTE_D5,  NOTE_C5, 
  NOTE_B4,   NOTE_B4,  NOTE_C5,  NOTE_D5,  NOTE_E5, 
  NOTE_C5,   NOTE_A4,  NOTE_A4, REST, 

  NOTE_E5,   NOTE_B4,  NOTE_C5,  NOTE_D5,  NOTE_C5, NOTE_B4,
  NOTE_A4,  NOTE_A4,  NOTE_C5,  NOTE_E5,   NOTE_D5,  NOTE_C5, 
  NOTE_B4,   NOTE_C5,   NOTE_D5,  NOTE_E5,
  NOTE_C5,   NOTE_A4,   NOTE_A4, NOTE_A4, NOTE_B4, NOTE_C5,

  NOTE_D5,   NOTE_F5, NOTE_A5,  NOTE_G5,   NOTE_F5,
  NOTE_E5,   NOTE_C5,   NOTE_E5,   NOTE_D5,  NOTE_C5, 
  NOTE_B4,   NOTE_B4,  NOTE_C5, NOTE_D5, NOTE_E5, 
  NOTE_C5,   NOTE_A4,  NOTE_A4,  REST, 


  NOTE_E5,   NOTE_C5, 
  NOTE_D5,   NOTE_B4,
  NOTE_C5,   NOTE_A4,
  NOTE_GS4,   NOTE_B4,   REST,
  NOTE_E5,    NOTE_C5,
  NOTE_D5,    NOTE_B4,
  NOTE_C5,   NOTE_E5, NOTE_A5, 
  NOTE_GS5
};
int NewTone::melody[] = {
// Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192

  NOTE_E5, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_C5, 8,  NOTE_B4, 8,
  NOTE_A4, 4,  NOTE_A4, 8,  NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, -4,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 8,  NOTE_A4, 4,  NOTE_B4, 8,  NOTE_C5, 8,

  NOTE_D5, -4,  NOTE_F5, 8,  NOTE_A5, 4,  NOTE_G5, 8,  NOTE_F5, 8,
  NOTE_E5, -4,  NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 4, REST, 4,

  NOTE_E5, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_C5, 8,  NOTE_B4, 8,
  NOTE_A4, 4,  NOTE_A4, 8,  NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, -4,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 8,  NOTE_A4, 4,  NOTE_B4, 8,  NOTE_C5, 8,

  NOTE_D5, -4,  NOTE_F5, 8,  NOTE_A5, 4,  NOTE_G5, 8,  NOTE_F5, 8,
  NOTE_E5, -4,  NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 4, REST, 4,


  NOTE_E5, 2,  NOTE_C5, 2,
  NOTE_D5, 2,   NOTE_B4, 2,
  NOTE_C5, 2,   NOTE_A4, 2,
  NOTE_GS4, 2,  NOTE_B4, 4,  REST, 8,
  NOTE_E5, 2,   NOTE_C5, 2,
  NOTE_D5, 2,   NOTE_B4, 2,
  NOTE_C5, 4,   NOTE_E5, 4,  NOTE_A5, 2,
  NOTE_GS5, 2,
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int NewTone::notes = sizeof(NewTone::melody) / sizeof(NewTone::melody[0])/2;

// this calculates the duration of a whole note in ms (60s/tempo)*4 beats
int NewTone::wholenote = (60000 * 4) / NewTone::tempo;

int NewTone::divider = 0;

uint8_t NewTone::prescaler = 0;
uint16_t NewTone::top = 0;

void NewTone::a2NewTone(uint8_t pin, uint16_t frequency, uint16_t length) {
  NewTone::noNewToneCheck = false;
  // uint8_t prescaler = _BV(CS10);                  // Try using prescaler 1 first.
  NewTone::prescaler = _BV(CS10);
  NewTone::top = F_CPU / frequency / 4 - 1;  // Calculate the top.
  // uint16_t top = F_CPU / frequency / 4 - 1;  // Calculate the top.
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

  ICR1    = NewTone::top;                      // Set the top.
  if (TCNT1 > NewTone::top) {
    TCNT1 = NewTone::top;           }           // Counter over the top, put within range.
  TCCR1B  = _BV(WGM13)  | NewTone::prescaler;  // Set PWM, phase and frequency corrected (ICR1) and prescaler.
  TCCR1A  = _BV(COM1B0);
  TIMSK1 |= _BV(OCIE1A); 

}

void NewTone::noNewTone(uint8_t pin) {
  TIMSK1 &= ~_BV(OCIE1A);   // Remove the timer interrupt.
  TCCR1B  = _BV(CS11);      // Default clock prescaler of 8.
  TCCR1A  = _BV(WGM10);     // Set to defaults so PWM can work like normal (PWM, phase corrected, 8bit).
  *NewTone::_pinOutput &= ~NewTone::_pinMask;  // Set pin to LOW.
  NewTone::_pinMask = 0;  // Flag so we know note is no longer playing.
  NewTone::noNewToneCheck = true;
}

void NewTone::noNewTone() {
  TIMSK1 &= ~_BV(OCIE1A);   // Remove the timer interrupt.
  TCCR1B  = _BV(CS11);      // Default clock prescaler of 8.
  TCCR1A  = _BV(WGM10);     // Set to defaults so PWM can work like normal (PWM, phase corrected, 8bit).
  *NewTone::_pinOutput &= ~NewTone::_pinMask;  // Set pin to LOW.
  NewTone::_pinMask = 0;  // Flag so we know note is no longer playing.
  NewTone::noNewToneCheck = true;
}
