#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include "Arduino.h"
#include "IRCommunication.h"

ISR(INT0_vect)
{
    if (!IRCommunication::isCurrentlyReceiving()) {
        IRCommunication::setCurrentlyReceiving(true); // Start receiving (start bit detected)
        return;
    }

    IRCommunication::toggleCurrentBitIsOne(); // Toggle on interrupt because there is a change in value
}

ISR(TIMER0_COMPA_vect) {
    IRCommunication::handleTimer0Interupt();
}

IRCommunication::IRCommunication(int kiloHertz) {
    currentlyReceiving = false;
    currentBitIsOne = true;
    numberOfCurrentReceivingBit = 0;
    dataLength = 16;
    result = 0;
    deviderToGetRightHz = (kiloHertz == 56) ? 18 : 12;
    khz = kiloHertz;
    sendCount = 0;
    receiveCount = 0;
    receivingBitPosition = 0;

    DDRD |= (1<<DDD6);
    PORTD |= (1<<PORTD2);

    initTimer0();
    initIrInterupt();
}

void IRCommunication::initIrInterupt()
{
    EIMSK |= (1<<INT0);
    EICRA |= (1<<ISC00);
}

void IRCommunication::initTimer0()
{
    TCCR0A |= (1<<WGM00)|(1<<WGM01);
    TCCR0B |= (1<<WGM02);
    TCCR0A |= (1<<COM0A0);
    TCCR0B |= (1<<CS00);
    OCR0A = (IRCommunication::getKhz() == 56) ? 141 : 209;
    TIMSK0 |= (1<<OCIE0A);
    TCNT0 = 0;
}

uint8_t IRCommunication::getKhz()
{
    return khz;
}

void IRCommunication::handleTimer0Interupt()
{
    if (sendCount == IRCommunication::getHzDevider()) {
        sendBit();
        sendCount = 0;
    }
    if (IRCommunication::isCurrentlyReceiving()) {
        receiveCount++;
        receiveBit();
    }
    sendCount++;
}

bool IRCommunication::isCurrentlyReceiving()
{
    return currentlyReceiving;
}

void IRCommunication::setCurrentlyReceiving(bool value)
{
    currentlyReceiving = value;
}

void IRCommunication::toggleCurrentBitIsOne()
{
    currentBitIsOne = !currentBitIsOne;
}

void IRCommunication::receiveBit()
{
    if (
        (numberOfCurrentReceivingBit == 0 && receiveCount == deviderToGetRightHz + (deviderToGetRightHz / 2)) ||
        (numberOfCurrentReceivingBit > 0 && receiveCount == deviderToGetRightHz)
        ) { // Start sampling in middle of data bit

        if (numberOfCurrentReceivingBit <
            dataLength) { // If inside the data bit, save the data to the result variable
            if (currentBitIsOne) // Check if the current data bit is a 1 or 0
                result |= (1 << numberOfCurrentReceivingBit);
            else
                result &= ~(1 << numberOfCurrentReceivingBit);
        }

        receiveCount = 0;
        numberOfCurrentReceivingBit++;

        if (numberOfCurrentReceivingBit ==
            dataLength + 1) { // End of data, line is low again so reset settings for next frame
            numberOfCurrentReceivingBit = 0;
            currentlyReceiving = false;
            currentBitIsOne = true;
            Serial.println(result);
            result = 0;
        }
    }
}

void IRCommunication::sendBit()
{
    if (receivingBitPosition == 0) { // Start bit
        TCCR0A |= (1<<COM0A0); // Enable compare interrupt
        receivingBitPosition = 1; // Set bit to one as this is the first data bit that will be sent next cycle
        return;
    }

    if (receivingBitPosition >= dataLength+1) { // End of Frame
        TCCR0A &= ~(1<<COM0A0); // Set line to low for some time
        receivingBitPosition++;
        if (receivingBitPosition == dataLength*2.5) receivingBitPosition = 0; // Set bitcount to 0 for the next frame
        return;
    }

    if ((result & (1<<(receivingBitPosition-1))) > 0) // Check if next data bit is 0 or 1
        TCCR0A |= (1<<COM0A0); // Enable compare interrupt
    else
        TCCR0A &= ~(1<<COM0A0); // Disconnect

    receivingBitPosition++; // Increase bit count for next data bit
}

uint8_t IRCommunication::getHzDevider()
{
    return deviderToGetRightHz;
}