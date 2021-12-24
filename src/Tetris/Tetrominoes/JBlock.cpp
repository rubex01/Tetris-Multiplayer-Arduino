#include "JBlock.h"
#include "../../Display/Display.h"

JBlock::JBlock(int xPos, int yPos) : Block(xPos, yPos) {
    resetBlock();
    blockColor = BLUE;
}

void JBlock::resetBlock() {
    blockArray[0][0] = xPos - 1;
    blockArray[0][1] = yPos;
    blockArray[1][0] = xPos;
    blockArray[1][1] = yPos;
    blockArray[2][0] = xPos + 1;
    blockArray[2][1] = yPos;
    blockArray[3][0] = xPos + 1;
    blockArray[3][1] = yPos + 1;
    rotationLevel = 0;
}

void JBlock::drawSectionBlock(int section) {
    int x = 0;
    int y = 0;
    if (section == NEXTSECTION) {
        x = 194;
        y = 35;
    }
    if (section == HOLDSECTION) {
        x = 33;
        y = 35;
    }
    Display::drawSmallTetrisBlok(x, y, this->blockColor);
    Display::drawSmallTetrisBlok(x+10, y, this->blockColor);
    Display::drawSmallTetrisBlok(x-10, y, this->blockColor);
    Display::drawSmallTetrisBlok(x+10, y+10, this->blockColor);
}

void JBlock::rotateBlock() {
    switch (rotationLevel) {
        case 1:
            blockArray[0][0]++;
            blockArray[1][1]++;
            blockArray[2][0]--;
            blockArray[2][1] += 2;
            blockArray[3][0] -= 2;
            blockArray[3][1]++;
            break;
        case 2:
            blockArray[0][0]--;
            blockArray[0][1]++;
            blockArray[1][0]--;
            blockArray[1][1]++;
            blockArray[3][0] += 2;
            break;
        case 3:
            blockArray[0][0]++;
            blockArray[0][1]--;
            blockArray[1][0] += 2;
            blockArray[1][1] -= 2;
            blockArray[2][1]--;
            blockArray[3][0]--;
            break;
        case 0:
            blockArray[0][0]--;
            blockArray[0][1]++;
            blockArray[1][0]--;
            blockArray[1][1]++;
            blockArray[2][0]++;
            blockArray[3][0]++;
            break;
    }
}
