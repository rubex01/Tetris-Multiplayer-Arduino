#ifndef KBS_SENDQUEUE_H
#define KBS_SENDQUEUE_H

class SendQueue {
    public:
        static void addToQueue(uint8_t dataToSend);
        static uint8_t getItemToSend();
        static bool isEmpty();

    private:
        static uint8_t itemsInQueue[20];
        static uint8_t* queuePointers[20];
};


#endif //KBS_SENDQUEUE_H
