#include <avr/io.h>
#include <avr/interrupt.h>
#include "IRCommunication.h"
#include "SendQueue.h"
#include "ReceivedData.h"

ISR(INT0_vect)
{
    if (IRCommunication::sending) return;
    if (!IRCommunication::currentlyReceiving) {
        IRCommunication::startReceiving();
        return;
    }

    float calc = IRCommunication::receiveCounter / IRCommunication::receiveDevider;
    int count = (int)(calc + 0.5f);

    if (IRCommunication::receivingBitIndex == 0) {
        count--;
        IRCommunication::receivingBitIndex = 1;
    }

    for (int i = 0; i < count; ++i) {
        if (IRCommunication::bitIsOne) {
            IRCommunication::result |= (1<<IRCommunication::receivingBitIndex-1);
        }
        IRCommunication::receivingBitIndex++;
    }

    IRCommunication::receiveCounter = 0;
    IRCommunication::bitIsOne = !IRCommunication::bitIsOne;
}

ISR(TIMER0_COMPA_vect) {
    if (IRCommunication::currentlyReceiving && !IRCommunication::sending) {
        IRCommunication::receiveCounter++;
        if (IRCommunication::receiveCounter == 1700)
            IRCommunication::resetReceive();
    }
    else if (IRCommunication::wantToSend) {
        if (!IRCommunication::sending) {
            IRCommunication::sending = true;
            IRCommunication::data = SendQueue::getItemToSend();
        }
        if (IRCommunication::sendCounter == IRCommunication::devider) {
            IRCommunication::sendDataBit();
            IRCommunication::sendCounter = 0;
        }
        IRCommunication::sendCounter++;
    }
}

int IRCommunication::OCRAValue = 0;
bool IRCommunication::wantToSend = false;
bool IRCommunication::sending = false;

int IRCommunication::receiveCounter = 0;
int IRCommunication::receivingBitIndex = 0;
float IRCommunication::receiveDevider = 0.0f;
uint8_t IRCommunication::result = 0;
bool IRCommunication::bitIsOne = true;
bool IRCommunication::currentlyReceiving = false;

int IRCommunication::sendCounter = 0;
int IRCommunication::devider = 0;
int IRCommunication::sendBitIndex = 0;
uint8_t IRCommunication::data = 0;
uint8_t IRCommunication::dataLength = 8;

void IRCommunication::init(int khz) {
    if (khz == 56) {
        OCRAValue = 141;
        devider = 190;
        receiveDevider = 182.0f;
    }
    else if (khz == 38) {
        OCRAValue = 206;
        devider = 130;
        receiveDevider = 135.0f;
    }

    initPorts();
    initTimer0();
    initIrInterrupt();
}

void IRCommunication::newDataToSend()
{
    wantToSend = true;
}

void IRCommunication::resetReceive()
{
    receivingBitIndex = 0;
    currentlyReceiving = false;
    bitIsOne = true;
    receiveCounter = 0;
    ReceivedData::addNewResult(result);
    result = 0;
}

void IRCommunication::sendDataBit()
{
    if (sendBitIndex == 0) { // Start bit
        TCCR0A |= (1<<COM0A0);
        sendBitIndex = 1;
        return;
    }

    if (sendBitIndex == dataLength+1) { // Stop bit
        TCCR0A |= (1<<COM0A0);
        sendBitIndex++;
        return;
    }

    if (sendBitIndex > dataLength+1) { // End of Frame
        TCCR0A &= ~(1<<COM0A0);
        sendBitIndex++;
        if (sendBitIndex == dataLength+50) { // Ready for next frame
            sendBitIndex = 0;
            PORTD |= (1<<PORTD2);
            wantToSend = !SendQueue::isEmpty(); // Check if we want to send more data
            sending = false;
        }
        return;
    }

    if ((data & (1<<(sendBitIndex-1))) > 0) // Check if bit is 0 or 1
        TCCR0A |= (1<<COM0A0);
    else
        TCCR0A &= ~(1<<COM0A0);

    IRCommunication::sendBitIndex++;
}

void IRCommunication::startReceiving() {
    IRCommunication::currentlyReceiving = true;
}

void IRCommunication::initPorts() {
    DDRD |= (1<<DDD6);
    PORTD |= (1<<PORTD2);
}

void IRCommunication::initTimer0() {
    TCCR0A |= (1<<WGM00)|(1<<WGM01);
    TCCR0B |= (1<<WGM02);
    TCCR0A |= (1<<COM0A0);
    TCCR0B |= (1<<CS00);
    OCR0A = IRCommunication::OCRAValue;
    TIMSK0 |= (1<<OCIE0A);
    TCNT0 = 0;
}

void IRCommunication::initIrInterrupt()
{
    EIMSK |= (1<<INT0);
    EICRA |= (1<<ISC00);
}