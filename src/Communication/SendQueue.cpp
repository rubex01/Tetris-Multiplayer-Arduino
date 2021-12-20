#include <avr/io.h>
#include "SendQueue.h"
#include "IRCommunication.h"
#include "Frame.h"

uint8_t SendQueue::itemsInQueue[20] = {0};
int SendQueue::count = 0;

/**
 * Add a new frame to the sendQueue
 *
 * @param frame
 */
void SendQueue::addToQueue(Frame frame) {
    itemsInQueue[count] = frame.getFrame();
    count++;
    IRCommunication::newDataToSend();
}

/**
 * Returns a frame that needs to be sent next then deletes it from the queue
 *
 * @return
 */
uint8_t SendQueue::getItemToSend() {
    if (itemsInQueue[0] == 0) return 0;
    uint8_t returnVal = itemsInQueue[0];
    for (int i = 0; i < 20; ++i) {
        if (i == 20 || itemsInQueue[i+1] == 0)
            itemsInQueue[i] = 0;
        else
            itemsInQueue[i] = itemsInQueue[i+1];
    }
    count--;
    return returnVal;
}
