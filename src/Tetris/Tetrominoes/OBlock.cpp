#include "OBlock.h"
#include "../../Display/Display.h"
#include "HardwareSerial.h"

OBlock::OBlock(int xPos, int yPos) : Block(xPos, yPos) {
    resetBlock();
    blockColor = YELLOW;
}

void OBlock::resetBlock() {
    blockArray[0][0] = xPos;
    blockArray[0][1] = yPos;
    blockArray[1][0] = xPos + 1;
    blockArray[1][1] = yPos;
    blockArray[2][0] = xPos;
    blockArray[2][1] = yPos + 1;
    blockArray[3][0] = xPos + 1;
    blockArray[3][1] = yPos + 1;
    rotationLevel = 0;
}

void OBlock::rotateBlock() {}

void OBlock::drawSectionBlock(int section) {
    int x = 0;
    int y = 0;
    if (section == NEXTSECTION) {
        x = 190;
        y = 35;
    }
    if (section == HOLDSECTION) {
        x = 33;
        y = 35;
    }
    Display::drawSmallTetrisBlok(x, y, this->blockColor);
    Display::drawSmallTetrisBlok(x+10, y, this->blockColor);
    Display::drawSmallTetrisBlok(x, y+10, this->blockColor);
    Display::drawSmallTetrisBlok(x+10, y+10, this->blockColor);
}
