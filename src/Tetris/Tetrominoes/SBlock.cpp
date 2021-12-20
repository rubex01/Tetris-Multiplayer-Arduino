#include "SBlock.h"
#include "HardwareSerial.h"
#include "../../Display/Display.h"

SBlock::SBlock(int xPos, int yPos) : Block(xPos, yPos) {
    blockArray[0][0] = xPos;
    blockArray[0][1] = yPos;
    blockArray[1][0] = xPos + 1;
    blockArray[1][1] = yPos;
    blockArray[2][0] = xPos;
    blockArray[2][1] = yPos + 1;
    blockArray[3][0] = xPos - 1;
    blockArray[3][1] = yPos + 1;
    blockColor = GREEN;
}
