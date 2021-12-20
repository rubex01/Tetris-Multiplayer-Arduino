#ifndef SRC_COMMUNICATION_SENDQUEUE_H_
#define SRC_COMMUNICATION_SENDQUEUE_H_

#include "Frame.h"

class SendQueue {
 public:
    static void addToQueue(Frame dataToSend);
    static uint8_t getItemToSend();
    static int count;

 private:
    static uint8_t itemsInQueue[20];
};

#endif  // SRC_COMMUNICATION_SENDQUEUE_H_
