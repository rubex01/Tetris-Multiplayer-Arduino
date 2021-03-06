#include <avr/io.h>
#include <avr/interrupt.h>
#include "IRCommunication.h"
#include "SendQueue.h"
#include "ReceivedData.h"

#define reachedEndOfFrame 1700

ISR(INT0_vect) {
    if (IRCommunication::sending) return;
    if (!IRCommunication::currentlyReceiving) {
        IRCommunication::startReceiving();
        return;
    }

    float calc = IRCommunication::receiveCounter / IRCommunication::receiveDivider;
    int count = static_cast<int>(calc + 0.5f);

    if (IRCommunication::receivingBitIndex == 0) {
        count--;
        IRCommunication::receivingBitIndex = 1;
    }

    for (int i = 0; i < count; ++i) {
        if (IRCommunication::bitIsOne) {
            IRCommunication::result |= (1 << IRCommunication::receivingBitIndex-1);
        }
        IRCommunication::receivingBitIndex++;
    }

    IRCommunication::receiveCounter = 0;
    IRCommunication::bitIsOne = !IRCommunication::bitIsOne;
}

ISR(TIMER0_COMPA_vect) {
    if (IRCommunication::currentlyReceiving && !IRCommunication::sending) {
        IRCommunication::receiveCounter++;
        if (IRCommunication::receiveCounter == reachedEndOfFrame)
            IRCommunication::resetReceive();
    } else if (IRCommunication::leftToSend != 0) {
        if (!IRCommunication::sending) {
            IRCommunication::sending = true;
            IRCommunication::data = SendQueue::getItemToSend();
        }
        if (IRCommunication::sendCounter == IRCommunication::divider) {
            IRCommunication::sendDataBit();
            IRCommunication::sendCounter = 0;
        }
        IRCommunication::sendCounter++;
    }
}

int IRCommunication::leftToSend = 0;
int IRCommunication::OCRAValue = 0;
bool IRCommunication::sending = false;

int IRCommunication::receiveCounter = 0;
int IRCommunication::receivingBitIndex = 0;
float IRCommunication::receiveDivider = 0.0f;
uint8_t IRCommunication::result = 0;
bool IRCommunication::bitIsOne = true;
bool IRCommunication::currentlyReceiving = false;

int IRCommunication::sendCounter = 0;
int IRCommunication::divider = 0;
int IRCommunication::sendBitIndex = 0;
uint8_t IRCommunication::data = 0;
uint8_t IRCommunication::dataLength = 8;

/**
 * Init the infrared communication.
 *
 * @param khz
 */
void IRCommunication::init(int khz) {
    if (khz == 56) {
        OCRAValue = 141;
        divider = 190;
        receiveDivider = 182.0f;
    } else if (khz == 38) {
        OCRAValue = 206;
        divider = 130;
        receiveDivider = 135.0f;
    }

    initPorts();
    initTimer0();
    initIrInterrupt();
}

/**
 * Increase frames left to be sent
 */
void IRCommunication::newDataToSend() {
    leftToSend++;
}

/**
 * Resets the receive variables. Called when done receiving a frame.
 */
void IRCommunication::resetReceive() {
    receivingBitIndex = 0;
    currentlyReceiving = false;
    bitIsOne = true;
    receiveCounter = 0;
    ReceivedData::addNewResult(result);
    result = 0;
}

/**
 * Sends one data bit.
 */
void IRCommunication::sendDataBit() {
    if (sendBitIndex == 0) {  /// Start bit
        TCCR0A |= (1 << COM0A0);
        sendBitIndex = 1;
        return;
    }

    if (sendBitIndex == dataLength+1) {  /// Stop bit
        TCCR0A |= (1 << COM0A0);
        sendBitIndex++;
        return;
    }

    if (sendBitIndex > dataLength+1) {  /// End of Frame
        TCCR0A &= ~(1 << COM0A0);
        sendBitIndex++;
        if (sendBitIndex == dataLength+50) {  /// Ready for next frame
            sendBitIndex = 0;
            PORTD |= (1 << PORTD2);
            leftToSend--;
            sending = false;
        }
        return;
    }

    if ((data & (1 << (sendBitIndex-1))) > 0)  /// Check if bit that needs to be sent is 0 or 1
        TCCR0A |= (1 << COM0A0);
    else
        TCCR0A &= ~(1 << COM0A0);

    IRCommunication::sendBitIndex++;
}

/**
 * Start receiving, this will make sure we won't start sending when we are receiving
 */
void IRCommunication::startReceiving() {
    IRCommunication::currentlyReceiving = true;
}

/**
 * Init the ports used by infrared communication
 */
void IRCommunication::initPorts() {
    DDRD |= (1 << DDD6);
    PORTD |= (1 << PORTD2);
}

/**
 * Init timer0 so it can be used for infrared communication
 */
void IRCommunication::initTimer0() {
    TCCR0A |= (1 << WGM00)|(1 << WGM01);
    TCCR0B |= (1 << WGM02);
    TCCR0B |= (1 << CS00);
    OCR0A = IRCommunication::OCRAValue;
    TIMSK0 |= (1 << OCIE0A);
    TCNT0 = 0;
}

/**
 * Init infrared sensor interrupts
 */
void IRCommunication::initIrInterrupt() {
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
}
