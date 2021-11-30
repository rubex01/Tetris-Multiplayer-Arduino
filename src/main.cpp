#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include "Arduino.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "HardwareSerial.h"
#include "Controller.h"
#include "Character.h"
#include "Display.h"

uint8_t data = 173;
uint8_t dataLength = 8;
uint8_t bitCount = 0;
uint8_t sendCounter = 0;

boolean currentlyReceiving = false;
uint8_t numberOfCurrentReceivingBit = 0;
uint8_t receiveCount = 0;
boolean currentBitIsOne = true;
uint8_t result = 0;

void sendData()
{
    if (bitCount == 0) { // Start bit
        TCCR0A |= (1<<COM0A0); // Enable compare interrupt
        bitCount = 1; // Set bit to one as this is the first data bit that will be sent next cycle
        return;
    }

    if (bitCount >= dataLength+1) { // End of Frame
        TCCR0A &= ~(1<<COM0A0); // Set line to low for some time
        bitCount++;
        if (bitCount == dataLength+50) bitCount = 0; // Set bitcount to 0 for the next frame
        return;
    }

    if ((data & (1<<(bitCount-1))) > 0) // Check if next data bit is 0 or 1
        TCCR0A |= (1<<COM0A0); // Enable compare interrupt
    else
        TCCR0A &= ~(1<<COM0A0); // Disconnect

    bitCount++; // Increase bit count for next data bit
}

ISR(INT0_vect)
{
    if (!currentlyReceiving) {
        currentlyReceiving = true; // Start receiving (start bit detected)
        return;
    }

    currentBitIsOne = !currentBitIsOne; // Toggle on interrupt because there is a change in value
}

void resetReceiver()
{
    numberOfCurrentReceivingBit = 0;
    currentlyReceiving = false;
    currentBitIsOne = true;
    Serial.println(result);
    result = 0;
}

ISR(TIMER0_COMPA_vect) {
    uint8_t deviderToGetRightHz = 42; // 56 khz
//    uint8_t deviderToGetRightHz = 29; // 38 khz

    if (sendCounter == deviderToGetRightHz) {
        sendData();
        sendCounter = 0;
    }
    sendCounter++;

    if (currentlyReceiving) {
        if (
            (receiveCount == deviderToGetRightHz && numberOfCurrentReceivingBit != 0) ||
            (numberOfCurrentReceivingBit == 0 && receiveCount == deviderToGetRightHz+(deviderToGetRightHz/2/2))
        ){ // Start sampling in middle of data bit

            if (currentBitIsOne && numberOfCurrentReceivingBit < dataLength)
                result |= (1<<numberOfCurrentReceivingBit);

            receiveCount = 0;

            if (numberOfCurrentReceivingBit == dataLength) resetReceiver();
            else numberOfCurrentReceivingBit++;
        }
        else
            receiveCount++;
    }
}

void initTimer0()
{
    TCCR0A |= (1<<WGM00)|(1<<WGM01);
    TCCR0B |= (1<<WGM02);
    TCCR0A |= (1<<COM0A0);
    TCCR0B |= (1<<CS00);
    OCR0A = 141; // 56 khz
//    OCR0A = 206; // 38 khz
    TIMSK0 |= (1<<OCIE0A);
    TCNT0 = 0;
}

void initIrInterupt()
{
    EIMSK |= (1<<INT0);
    EICRA |= (1<<ISC00);
}

int main()
{
    DDRD |= (1<<DDD6);
    PORTD |= (1<<PORTD2);

    Serial.begin(9600);

    sei();
      Controller::Init();
  Display::Init();

    initTimer0();
    initIrInterupt();

    while(true) {
              Display::FillCircle(Character::xPos, Character::yPos, 10, ILI9341_BLACK);
      Controller::Update();
      Display::FillCircle(Character::xPos, Character::yPos, 10, ILI9341_MAGENTA);
      _delay_ms(50);
    }

    return(0);
    // Super loop to check button state and display counter
}
