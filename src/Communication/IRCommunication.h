#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#ifndef BLINKSERIAL_IRCOMMUNICATION_H
#define BLINKSERIAL_IRCOMMUNICATION_H

#include "Arduino.h"

class IRCommunication {
    public:
        static void init();
        static void setCurrentlyReceiving(boolean value);
        static void toggleCurrentBitIsOne();
        static void runSendForInterrupt();
        static void runReceiveForInterrupt();
        static void sendDataBit();

        static int kiloHertz;
        static boolean currentlyReceiving;
        static boolean currentBitIsOne;
        static uint8_t data;
        static uint8_t result;
        static int dataLength;
        static int numberOfCurrentReceivingBit;
        static int bitCount;
        static int sendCounter;
        static int receiveCount;
        static int deviderToGetRightHz;

        static void initTimer0();
        static void initIrInterupt();
        static void initPorts();
        static void resetReceiver();
};


#endif //BLINKSERIAL_IRCOMMUNICATION_H
