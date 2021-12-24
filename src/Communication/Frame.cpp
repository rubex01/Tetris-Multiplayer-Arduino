#include <avr/io.h>
#include "Frame.h"

uint8_t Frame::ROW_TYPE = 0;
uint8_t Frame::SEED_TYPE = 1;
uint8_t Frame::LOST_TYPE = 2;
uint8_t Frame::CONFIRM_TYPE = 3;

/**
 * This constructor encodes data and a type into a valid frame.
 *
 * @param uint8_t data
 * @param uint8_t type
 */
Frame::Frame(uint8_t data, uint8_t type) {
    frame = 0;
    this->data = data;
    this->type = type;

    createFrame();
}

/**
 * This constructor decodes a frame into a data variable and a type variable
 *
 * @param receivedFrameData
 */
Frame::Frame(uint8_t receivedFrameData) {
    frame = receivedFrameData;
    data = 0;
    type = 0;
    decodeFrame();
}

/**
 * Returns the type variable
 *
 * @return uint8_t
 */
uint8_t Frame::getType() {
    return type;
}

/**
 * Returns the data variable
 *
 * @return uint8_t
 */
uint8_t Frame::getData() {
    return data;
}

/**
 * Helper function that decodes a frame into a data and type
 */
void Frame::decodeFrame() {
    for (uint8_t i=0; i < 2; i++)
        if (frame & (1 << i))
            type |= (1 << i);

    for (uint8_t i=0; i < 6; i++)
        if (frame & (1 << (i+2)))
            data |= (1 << i);
}

/**
 * Returns the frame variable
 *
 * @return uint8_t
 */
uint8_t Frame::getFrame() {
    return frame;
}

/**
 * Helper function that encodes data and a type into a frame
 */
void Frame::createFrame() {
    for (uint8_t i=0; i < 6; i++)
        if (data & (1 << i))
            frame |= (1 << (i+2));

    for (uint8_t i=0; i < 2; i++)
        if (type & (1 << i))
            frame |= (1 << i);
}
