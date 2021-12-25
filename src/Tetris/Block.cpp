#include "../Scenes/GameScene/GameScene.h"
#include "Block.h"
#include "BlockFactory.h"

/**
 * Block constructor
 *
 * @param xPos
 * @param yPos
 */
Block::Block(int xPos, int yPos) {
    this->xPos = xPos;
    this->yPos = yPos;
    this->rotationLevel = 0;
    this->blockArray = new uint8_t*[4];
    for (int i = 0; i < 4; i++) {
        blockArray[i] = new uint8_t[2];
        blockArray[i][0] = 0;
        blockArray[i][1] = 0;
    }
}

/**
 * Block destructor
 */
Block::~Block() {
    for (int i = 0; i < 4; i++) {
        delete[] Block::blockArray[i];
    }
    delete[] Block::blockArray;
}

/**
 * Inits block, places it at starting location
 */
void Block::initBlock() {
    int valueCount = 0;
    for (int i = 0; i < 4; i++) {
        valueCount += GameScene::tetrisBoard[blockArray[i][1]][blockArray[i][0]];
    }

    if (valueCount != 0) {
        GameScene::gameOver = true;
        return;
    }

    setValue(blockColor);
}

/**
 * Sets values of blocks on all coordinates. 0 means invisisble, 1 means visisble
 *
 * @param value
 */
void Block::setValue(int value) {
    for (int i = 0; i < 4; i++) {
        GameScene::tetrisBoard[blockArray[i][1]][blockArray[i][0]] = value;
    }
}

/**
 * Resets direction of block by certain value
 *
 * @param direction
 */
void Block::resetDirection(int direction) {
    blockArray[0][0] -= direction;
    blockArray[1][0] -= direction;
    blockArray[2][0] -= direction;
    blockArray[3][0] -= direction;
}

/**
 * Rotates tetromino block on the board
 */
void Block::rotate() {
    if (rotationLevel == 3)
        rotationLevel = 0;
    else
        rotationLevel++;

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 10; j++) {
            tempArray[i][j] = GameScene::tetrisBoard[i][j];
        }
    }

    int firstCount = GameScene::boardCount();

    setValue(0);

    int backup[4][2];
    for (int i = 0; i < 4; ++i) {
        backup[i][0] = blockArray[i][0];
        backup[i][1] = blockArray[i][1];
    }

    rotateBlock();

    for (int i = 0; i < 4; i++) {
        if (blockArray[i][0] >= 0 && blockArray[i][0] < 10) {
            GameScene::tetrisBoard[blockArray[i][1]][blockArray[i][0]] = blockColor;
        } else {
            copyArray(tempArray);
            for (int j = 0; j < 4; ++j) {
                blockArray[j][0] = backup[j][0];
                blockArray[j][1] = backup[j][1];
            }
            rotationLevel--;
            return;
        }
    }

    int secondCount = GameScene::boardCount();

    if (firstCount != secondCount) {
        copyArray(tempArray);
        for (int j = 0; j < 4; ++j) {
            blockArray[j][0] = backup[j][0];
            blockArray[j][1] = backup[j][1];
        }
        rotationLevel--;
        return;
    }
}

/**
 * Moves a tetrisblock sideways. The direction param decides if it is left or right
 *
 * @param direction
 */
void Block::moveSideways(int direction) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 10; j++) {
            tempArray[i][j] = GameScene::tetrisBoard[i][j];
        }
    }

    int firstCount = GameScene::boardCount();

    setValue(0);

    blockArray[0][0] += direction;
    blockArray[1][0] += direction;
    blockArray[2][0] += direction;
    blockArray[3][0] += direction;

    for (int i = 0; i < 4; i++) {
        if (blockArray[i][0] >= 0 && blockArray[i][0] < 10) {
            GameScene::tetrisBoard[blockArray[i][1]][blockArray[i][0]] = blockColor;
        } else {
            copyArray(tempArray);
            resetDirection(direction);
            return;
        }
    }

    int secondCount = GameScene::boardCount();

    if (firstCount != secondCount) {
        copyArray(tempArray);
        resetDirection(direction);
        return;
    }
}

/**
 * Copies board array given in parameter into the real board array
 *
 * @param array
 */
void Block::copyArray(uint8_t array[11][10]) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 10; j++) {
            GameScene::tetrisBoard[i][j] = array[i][j];
        }
    }
}

/**
 * Moves the tetromino block one unit down
 */
void Block::moveDown() {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 10; j++) {
            tempArray[i][j] = GameScene::tetrisBoard[i][j];
        }
    }

    int firstCount = GameScene::boardCount();

    setValue(0);

    blockArray[0][1]++;
    blockArray[1][1]++;
    blockArray[2][1]++;
    blockArray[3][1]++;

    for (int i = 0; i < 4; i++) {
        if (blockArray[i][1] < 11) {
            GameScene::tetrisBoard[blockArray[i][1]][blockArray[i][0]] = blockColor;
        } else {
            copyArray(tempArray);
            GameScene::blockIsMoving = false;
            GameScene::checkForFullRows();
            return;
        }
    }

    if (GameScene::blockIsMoving) {
        int secondCount = GameScene::boardCount();

        if (firstCount != secondCount) {
            copyArray(tempArray);
            GameScene::blockIsMoving = false;
            GameScene::checkForFullRows();
            return;
        }
    }
}

/**
 * Moves block one place up
 */
void Block::moveUp() {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 10; j++) {
            tempArray[i][j] = GameScene::tetrisBoard[i][j];
        }
    }

    setValue(0);

    blockArray[0][1]--;
    blockArray[1][1]--;
    blockArray[2][1]--;
    blockArray[3][1]--;

    for (int i = 0; i < 4; i++) {
        if (blockArray[i][1] >= 0) {
            GameScene::tetrisBoard[blockArray[i][1]][blockArray[i][0]] = blockColor;
        } else {
            GameScene::gameOver = true;
            return;
        }
    }
}

/**
 * Calls draw section on block that is currently in section provided in parameter.
 *
 * @param section
 */
void Block::triggerDrawSection(uint8_t section) {
    int blockType = 0;
    if (section == NEXTSECTION)
        blockType = GameScene::nextBlock;
    else
        blockType = GameScene::holdBlock;

    Block* block = BlockFactory::createBlock(blockType);
    block->drawSectionBlock(section);
    delete block;
}
