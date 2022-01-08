#ifndef SRC_COMMUNICATION_SENDQUEUE_H_
#define SRC_COMMUNICATION_SENDQUEUE_H_

#include "Frame.h"

class SendQueue {
 public:
    static uint8_t count;

    static void addToQueue(Frame dataToSend);
    static uint8_t getItemToSend();

 private:
    static uint8_t itemsInQueue[20];
};

#endif  // SRC_COMMUNICATION_SENDQUEUE_H_
