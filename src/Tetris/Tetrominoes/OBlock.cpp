#include "OBlock.h"
#include "../../Display/Display.h"
#include "HardwareSerial.h"

OBlock::OBlock(int xPos, int yPos) : Block(xPos, yPos) {
    blockArray[0][0] = xPos;
    blockArray[0][1] = yPos;
    blockArray[1][0] = xPos + 1;
    blockArray[1][1] = yPos;
    blockArray[2][0] = xPos;
    blockArray[2][1] = yPos + 1;
    blockArray[3][0] = xPos + 1;
    blockArray[3][1] = yPos + 1;
    blockColor = YELLOW;
}

void OBlock::rotateBlock() {}

void OBlock::drawSectionBlock() {
    int x = 190;
    int y = 35;
    Display::drawSmallTetrisBlok(x, y, this->blockColor);
    Display::drawSmallTetrisBlok(x+10, y, this->blockColor);
    Display::drawSmallTetrisBlok(x, y+10, this->blockColor);
    Display::drawSmallTetrisBlok(x+10, y+10, this->blockColor);
}
