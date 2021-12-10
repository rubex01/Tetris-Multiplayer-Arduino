#include <avr/io.h>
#include "SendQueue.h"
#include "IRCommunication.h"

uint8_t SendQueue::itemsInQueue[20] = {0};
uint8_t * SendQueue::queuePointers[20] = {};

void SendQueue::addToQueue(uint8_t dataToSend) {
    int i;
    for (i = 0; i < 20; ++i) {
        if (itemsInQueue[i] == 0) {
            itemsInQueue[i] = dataToSend;
            break;
        }
    }
    for (int j = 0; j < 20; ++j) {
        if (queuePointers[j] == nullptr) {
            queuePointers[j] = &itemsInQueue[i];
            break;
        }
    }
    IRCommunication::newDataToSend();
}

uint8_t SendQueue::getItemToSend() {
    uint8_t returnVal;
    if (queuePointers[0] != nullptr) {
        returnVal = *queuePointers[0];
        *queuePointers[0] = 0;
    }
    for (int i = 0; i < 19; ++i) {
        if (queuePointers[i+1] != nullptr)
            queuePointers[i] = queuePointers[i+1];
        else
            queuePointers[i] = nullptr;
    }
    return returnVal;
}

bool SendQueue::isEmpty()
{
    for (int i = 0; i < 20; ++i) {
        if (queuePointers[i] != nullptr) return false;
    }
    return true;
}