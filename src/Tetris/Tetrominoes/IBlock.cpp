#include "IBlock.h"
#include "../../Display/Display.h"

IBlock::IBlock(int xPos, int yPos) : Block(xPos, yPos) {
    resetBlock();
    blockColor = CYAN;
}

void IBlock::resetBlock() {
    blockArray[0][0] = xPos - 1;
    blockArray[0][1] = yPos;
    blockArray[1][0] = xPos;
    blockArray[1][1] = yPos;
    blockArray[2][0] = xPos + 1;
    blockArray[2][1] = yPos;
    blockArray[3][0] = xPos + 2;
    blockArray[3][1] = yPos;
    rotationLevel = 0;
}

void IBlock::drawSectionBlock(int section) {
    int x = 0;
    int y = 0;
    if (section == NEXTSECTION) {
        x = 179;
        y = 37;
    }
    if (section == HOLDSECTION) {
        x = 20;
        y = 37;
    }

    Display::drawSmallTetrisBlok(x, y, this->blockColor);
    Display::drawSmallTetrisBlok(x+10, y, this->blockColor);
    Display::drawSmallTetrisBlok(x+20, y, this->blockColor);
    Display::drawSmallTetrisBlok(x+30, y, this->blockColor);
}

void IBlock::rotateBlock() {
    switch (rotationLevel) {
        case 1:
            blockArray[0][0] += 2;
            blockArray[1][0]++;
            blockArray[1][1]++;
            blockArray[2][1] += 2;
            blockArray[3][0]--;
            blockArray[3][1] += 3;
            break;
        case 2:
            blockArray[0][0] -= 2;
            blockArray[0][1] += 2;
            blockArray[1][0]--;
            blockArray[1][1]++;
            blockArray[3][0]++;
            blockArray[3][1]--;
            break;
        case 3:
            blockArray[0][0]++;
            blockArray[0][1] -= 2;
            blockArray[1][1]--;
            blockArray[2][0]--;
            blockArray[3][0] -= 2;
            blockArray[3][1]++;
            break;
        case 0:
            blockArray[0][0]--;
            blockArray[0][1] += 2;
            blockArray[1][1]++;
            blockArray[2][0]++;
            blockArray[3][0] += 2;
            blockArray[3][1]--;
            break;
    }
}
