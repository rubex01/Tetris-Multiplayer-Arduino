#ifndef KBS_IRCOMMUNICATION_H
#define KBS_IRCOMMUNICATION_H

class IRCommunication {
    public:
        static void init(int khz);

        static int OCRAValue;
        static int khz;

    private:
        static void initTimer0();
        static void initIrInterrupt();
        static void initPorts();
};

#endif //KBS_IRCOMMUNICATION_H

