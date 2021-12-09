#include <avr/io.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>
#include "IRCommunication.h"

ISR(INT1_vect) {
    if(PIND & (1 << PIND3)) {
        IRCommunication::wantToSend = true;
    }
}

ISR(INT0_vect)
{
    if (IRCommunication::sending) return;
    if (!IRCommunication::currentlyReceiving) {
        IRCommunication::startReceiving();
        return;
    }

    float calc = IRCommunication::receiveCounter / 140.0f;
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
        if (
            (IRCommunication::khz == 56 && IRCommunication::receiveCounter == 1700) ||
            (IRCommunication::khz == 38 && IRCommunication::receiveCounter == 800)
        )
            IRCommunication::resetReceive();
    }
    else if (IRCommunication::wantToSend) {
        if (!IRCommunication::sending) {
            IRCommunication::sending = true;
        }
        if (IRCommunication::sendCounter == IRCommunication::devider) {
            IRCommunication::sendDataBit();
            IRCommunication::sendCounter = 0;
        }
        IRCommunication::sendCounter++;
    }
}

int IRCommunication::OCRAValue = 0;
int IRCommunication::khz = 0;
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
int IRCommunication::bitIndex = 0;
uint8_t IRCommunication::data = 44;
uint8_t IRCommunication::dataLength = 8;

void IRCommunication::init(int khz) {
    IRCommunication::khz = khz;

    if (khz == 56) {
        IRCommunication::OCRAValue = 141;
        IRCommunication::devider = 190;
        IRCommunication::receiveDevider = 140.0f;
    }
    else if (khz == 38) {
        IRCommunication::OCRAValue = 206;
        IRCommunication::devider = 130;
        IRCommunication::receiveDevider = 80.0f;
    }

    IRCommunication::initPorts();
    IRCommunication::initTimer0();
    IRCommunication::initIrInterrupt();
    IRCommunication::initDemoButton();
}

void IRCommunication::resetReceive()
{
    receivingBitIndex = 0;
    currentlyReceiving = false;
    bitIsOne = true;
    receiveCounter = 0;
    Serial.println(result);
    Serial.println("=====");
    result = 0;
}

void IRCommunication::sendDataBit()
{
    if (IRCommunication::bitIndex == 0) { // Start bit
        TCCR0A |= (1<<COM0A0); // Enable compare interrupt
        IRCommunication::bitIndex = 1; // Set bit to one as this is the first data bit that will be sent next cycle
        return;
    }

    if (IRCommunication::bitIndex == IRCommunication::dataLength+1) { // Start bit
        TCCR0A |= (1<<COM0A0); // Enable compare interrupt
        IRCommunication::bitIndex++; // Set bit to one as this is the first data bit that will be sent next cycle
        return;
    }

    if (IRCommunication::bitIndex > IRCommunication::dataLength+1) { // End of Frame
        TCCR0A &= ~(1<<COM0A0); // Set line to low for some time
        IRCommunication::bitIndex++;
        if (IRCommunication::bitIndex == IRCommunication::dataLength+50) {
            IRCommunication::bitIndex = 0; // Set bitcount to 0 for the next frame
            PORTD |= (1<<PORTD2);
            wantToSend = false;
            sending = false;
        }
        return;
    }

    if ((IRCommunication::data & (1<<(IRCommunication::bitIndex-1))) > 0) // Check if next data bit is 0 or 1
        TCCR0A |= (1<<COM0A0); // Enable compare interrupt
    else
        TCCR0A &= ~(1<<COM0A0); // Disconnect

    IRCommunication::bitIndex++; // Increase bit count for next data bit
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

void IRCommunication::initDemoButton()
{
    PORTD |= (1 << PORTD3);                         // Pullup D2
    EIMSK |= (1 << INT1);                           // Enable int0
    EICRA |= (1 << ISC10);
}

void IRCommunication::initIrInterrupt()
{
    EIMSK |= (1<<INT0);
    EICRA |= (1<<ISC00);
}