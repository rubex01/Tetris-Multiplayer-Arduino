#ifndef SRC_COMMUNICATION_IRCOMMUNICATION_H_
#define SRC_COMMUNICATION_IRCOMMUNICATION_H_

class IRCommunication {
 public:
    static int leftToSend;
    static int OCRAValue;
    static int divider;
    static bool wantToSend;
    static bool sending;

    static int receiveCounter;
    static float receiveDivider;
    static int receivingBitIndex;
    static bool bitIsOne;
    static bool currentlyReceiving;
    static uint8_t result;

    static int sendCounter;
    static int sendBitIndex;
    static uint8_t data;
    static uint8_t dataLength;

    static void init(int khz);
    static void startReceiving();
    static void sendDataBit();
    static void resetReceive();
    static void newDataToSend();

 private:
    static void initTimer0();
    static void initIrInterrupt();
    static void initPorts();
};

#endif  // SRC_COMMUNICATION_IRCOMMUNICATION_H_

