#include "JBlock.h"
#include "../../Display/Display.h"
#include "HardwareSerial.h"

JBlock::JBlock(int xPos, int yPos) : Block(xPos, yPos) {
    blockArray[0][0] = xPos;
    blockArray[0][1] = yPos;
    blockArray[1][0] = xPos;
    blockArray[1][1] = yPos + 1;
    blockArray[2][0] = xPos - 1;
    blockArray[2][1] = yPos + 1;
    blockArray[3][0] = xPos - 2;
    blockArray[3][1] = yPos + 1;
    blockColor = BLUE;
}
