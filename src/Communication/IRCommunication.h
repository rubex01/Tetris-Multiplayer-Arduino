#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#ifndef BLINKSERIAL_IRCOMMUNICATION_H
#define BLINKSERIAL_IRCOMMUNICATION_H

#include "Arduino.h"

class IRCommunication {
    public:
        IRCommunication(int kiloHertz);
        static bool isCurrentlyReceiving();
        static void setCurrentlyReceiving(bool value);
        static void toggleCurrentBitIsOne();
        static void receiveBit();
        static void sendBit();
        static uint8_t getHzDevider();
        static uint8_t getKhz();
        static void handleTimer0Interupt();

    private:
        static void initTimer0();
        static void initIrInterupt();
        static bool currentlyReceiving;
        static bool currentBitIsOne;
        static uint8_t numberOfCurrentReceivingBit;
        static uint8_t dataLength;
        static uint16_t result;
        static uint8_t deviderToGetRightHz;
        static uint8_t khz;
        static uint8_t sendCount;
        static uint8_t receiveCount;
        static uint8_t receivingBitPosition;
};


#endif //BLINKSERIAL_IRCOMMUNICATION_H
