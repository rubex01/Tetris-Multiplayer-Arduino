#ifndef SRC_COMMUNICATION_SENDQUEUE_H_
#define SRC_COMMUNICATION_SENDQUEUE_H_

class SendQueue {
 public:
    static void addToQueue(uint8_t dataToSend);
    static uint8_t getItemToSend();
    static int count;

 private:
    static uint8_t itemsInQueue[20];
};

#endif  // SRC_COMMUNICATION_SENDQUEUE_H_
