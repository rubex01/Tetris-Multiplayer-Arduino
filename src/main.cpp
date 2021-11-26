#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#include "Arduino.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "HardwareSerial.h"

uint16_t data = 23421;
uint16_t dataLength = 16;
uint16_t bitCount = 0;
uint16_t counter = 0;

boolean currentlyReceiving = false;
uint16_t numberOfCurrentReceivingBit = 0;
uint16_t receiveCount = 0;
boolean currentBitIsOne = false;
uint16_t result = 0x0;

void sendData()
{
    if (bitCount == 0) { // Start bit
        TCCR0A &= ~(1<<COM0A0); // Enable compare interrupt
        bitCount = 1; // Set bit to one as this is the first data bit that will be sent next cycle
        return;
    }

    if (bitCount >= dataLength+1) { // End of Frame
        TCCR0A |= (1<<COM0A0); // Set line to low for some time
        bitCount++;
        if (bitCount == dataLength*2.5) bitCount = 0; // Set bitcount to 0 for the next frame
        return;
    }

    if ((data & (1<<(bitCount-1))) > 0) // Check if next data bit is 0 or 1
        TCCR0A &= ~(1<<COM0A0); // Enable compare interrupt
    else
        TCCR0A |= (1<<COM0A0); // Disconnect

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

ISR(TIMER0_COMPA_vect) {
//    if (counter == 19) { // 38 khz
    if (counter == 18) { // 56 khz
        sendData();
        counter = 0;
    }
    if (currentlyReceiving) {
        receiveCount++;

        if (
                (numberOfCurrentReceivingBit == 0 && receiveCount == 27) ||
                (numberOfCurrentReceivingBit > 0 && receiveCount == 18)
            ) { // Start sampling in middle of data bit

            if (numberOfCurrentReceivingBit < dataLength) { // If inside the data bit, save the data to the result variable
                if (currentBitIsOne) // Check if the current data bit is a 1 or 0
                    result &= ~(1<<numberOfCurrentReceivingBit);
                else
                    result |= (1<<numberOfCurrentReceivingBit);
            }

            receiveCount = 0;
            numberOfCurrentReceivingBit++;

            if (numberOfCurrentReceivingBit == dataLength+1) { // End of data, line is low again so reset settings for next frame
                numberOfCurrentReceivingBit = 0;
                currentlyReceiving = false;
                currentBitIsOne = false;
                Serial.println(result);
                result = 0;
            }
        }
    }
    counter++;
}

void initTimer0()
{
    TCCR0A |= (1<<WGM00)|(1<<WGM01);
    TCCR0B |= (1<<WGM02);
    TCCR0A |= (1<<COM0A0);
    TCCR0B |= (1<<CS00);
    OCR0A = 141; // 56 khz
    // OCR0A = 209; // 38 khz
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

    initTimer0();
    initIrInterupt();
    sei();

    while(true) {
    }

    return(0);
    // Super loop to check button state and display counter
}