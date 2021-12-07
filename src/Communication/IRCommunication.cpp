#include <avr/io.h>
#include "IRCommunication.h"

int IRCommunication::OCRAValue = 0;
int IRCommunication::khz = 0;

void IRCommunication::init(int khz) {
    IRCommunication::khz = khz;

    if (khz == 56)
        IRCommunication::OCRAValue = 141;
    else if (khz == 38)
        IRCommunication::OCRAValue = 206;

    IRCommunication::initPorts();
    IRCommunication::initTimer0();
    IRCommunication::initIrInterrupt();
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