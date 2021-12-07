#ifndef KBS_IRCOMMUNICATION_H
#define KBS_IRCOMMUNICATION_H

class IRCommunication {
    public:
        static void init(int khz);
        static void startReceiving();
        static void sendDataBit();
        static void resetReceive();
        static void receiveInterrupt();
        static void initDemoButton();

        static int OCRAValue;
        static int khz;
        static int devider;
        static bool wantToSend;
        static bool sending;

        static int receiveCounter;
        static int receivingBitIndex;
        static bool bitIsOne;
        static bool currentlyReceiving;
        static uint8_t result;

        static int sendCounter;
        static int bitIndex;
        static uint8_t data;
        static uint8_t dataLength;

    private:
        static void initTimer0();
        static void initIrInterrupt();
        static void initPorts();
};

#endif //KBS_IRCOMMUNICATION_H

