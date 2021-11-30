#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include "Arduino.h"
#include "IRCommunication.h"

ISR(INT0_vect)
{
    if (!IRCommunication::currentlyReceiving) {
        IRCommunication::setCurrentlyReceiving(true); // Start receiving (start bit detected)
        return;
    }

    IRCommunication::toggleCurrentBitIsOne(); // Toggle on interrupt because there is a change in value
}

ISR(TIMER0_COMPA_vect) {
    IRCommunication::runSendForInterrupt();
    IRCommunication::runReceiveForInterrupt();
}

int IRCommunication::kiloHertz = 38;
boolean IRCommunication::currentlyReceiving = false;
boolean IRCommunication::currentBitIsOne = true;
int IRCommunication::dataLength = 8;
int IRCommunication::numberOfCurrentReceivingBit = 0;
uint8_t IRCommunication::result = 0;
int IRCommunication::bitCount = 0;
int IRCommunication::sendCounter = 0;
int IRCommunication::receiveCount = 0;
int IRCommunication::deviderToGetRightHz = 29; // 38 khz
//int IRCommunication::deviderToGetRightHz = 42; // 56 khz
uint8_t IRCommunication::data = 170;

void IRCommunication::init()
{
    initPorts();
    initTimer0();
    initIrInterupt();
}

void IRCommunication::runSendForInterrupt()
{
    if (sendCounter == deviderToGetRightHz) {
        sendDataBit();
        sendCounter = 0;
    }
    sendCounter++;
}

void IRCommunication::runReceiveForInterrupt()
{
    if (currentlyReceiving) {
        if (
            (receiveCount == deviderToGetRightHz && numberOfCurrentReceivingBit != 0) ||
            (numberOfCurrentReceivingBit == 0 && receiveCount == deviderToGetRightHz+(deviderToGetRightHz/2))
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

void IRCommunication::toggleCurrentBitIsOne()
{
    currentBitIsOne = !currentBitIsOne;
}

void IRCommunication::resetReceiver()
{
    numberOfCurrentReceivingBit = 0;
    currentlyReceiving = false;
    currentBitIsOne = true;
    Serial.println(result);
    result = 0;
}

void IRCommunication::sendDataBit()
{
    if (bitCount == 0) { // Start bit
        TCCR0A |= (1<<COM0A0); // Enable compare interrupt
        bitCount = 1; // Set bit to one as this is the first data bit that will be sent next cycle
        return;
    }

    if (bitCount >= dataLength+1) { // End of Frame
        TCCR0A &= ~(1<<COM0A0); // Set line to low for some time
        bitCount++;
        if (bitCount == dataLength+20) bitCount = 0; // Set bitcount to 0 for the next frame
        return;
    }

    if ((data & (1<<(bitCount-1))) > 0) // Check if next data bit is 0 or 1
        TCCR0A |= (1<<COM0A0); // Enable compare interrupt
    else
        TCCR0A &= ~(1<<COM0A0); // Disconnect

    bitCount++; // Increase bit count for next data bit
}

void IRCommunication::initPorts()
{
    DDRD |= (1<<DDD6);
    PORTD |= (1<<PORTD2);
}

void IRCommunication::initTimer0()
{
    TCCR0A |= (1<<WGM00)|(1<<WGM01);
    TCCR0B |= (1<<WGM02);
    TCCR0A |= (1<<COM0A0);
    TCCR0B |= (1<<CS00);
//    OCR0A = 141; // 56 khz
    OCR0A = 206; // 38 khz
    TIMSK0 |= (1<<OCIE0A);
    TCNT0 = 0;
}

void IRCommunication::setCurrentlyReceiving(boolean value)
{
    currentlyReceiving = value;
}

void IRCommunication::initIrInterupt()
{
    EIMSK |= (1<<INT0);
    EICRA |= (1<<ISC00);
}