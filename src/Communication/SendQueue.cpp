#include <avr/io.h>
#include "SendQueue.h"
#include "IRCommunication.h"

uint8_t SendQueue::itemsInQueue[20] = {0};
int SendQueue::count = 0;

void SendQueue::addToQueue(uint8_t dataToSend) {
    itemsInQueue[count] = dataToSend;
    count++;
    IRCommunication::newDataToSend();
}

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
