#include <avr/io.h>
#include "Frame.h"

uint8_t Frame::ROW_TYPE = 0;
uint8_t Frame::SEED_TYPE = 1;
uint8_t Frame::LOST_TYPE = 2;
uint8_t Frame::CONFIRM_TYPE = 3;

Frame::Frame(uint8_t data, uint8_t type) {
    frame = 0;
    this->data = data;
    this->type = type;

    createFrame();
}

Frame::Frame(uint8_t receivedFrameData) {
    frame = receivedFrameData;
    data = 0;
    type = 0;
    decodeFrame();
}

uint8_t Frame::getType() {
    return type;
}

uint8_t Frame::getData() {
    return data;
}

void Frame::decodeFrame() {
    for (int i=0; i < 2; i++)
        if (frame & (1 << i))
            type |= (1 << i);

    for (int i=0; i < 6; i++)
        if (frame & (1 << (i+2)))
            data |= (1 << i);
}

uint8_t Frame::getFrame() {
    return frame;
}

void Frame::createFrame() {
    for (int i=0; i < 6; i++)
        if (data & (1 << i))
            frame |= (1 << (i+2));

    for (int i=0; i < 2; i++)
        if (type & (1 << i))
            frame |= (1 << i);
}
