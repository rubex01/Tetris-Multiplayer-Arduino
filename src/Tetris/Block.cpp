#include "../Scenes/GameScene/GameScene.h"
#include "Block.h"

Block::Block(int xPos, int yPos) {
    this->xPos = xPos;
    this->yPos = yPos;
    this->rotationLevel = 0;
    this->blockArray = new int*[4];
    for (int i = 0; i < 4; i++) {
        blockArray[i] = new int[2];
        blockArray[i][0] = 0;
        blockArray[i][1] = 0;
    }
}

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

void Block::setValue(int value) {
    for (int i = 0; i < 4; i++) {
        GameScene::tetrisBoard[blockArray[i][1]][blockArray[i][0]] = value;
    }
}

void Block::resetDirection(int direction) {
    blockArray[0][0] -= direction;
    blockArray[1][0] -= direction;
    blockArray[2][0] -= direction;
    blockArray[3][0] -= direction;
}

void Block::rotate() {
    if (rotationLevel == 3)
        rotationLevel = 0;
    else
        rotationLevel++;

    int tempArray[11][10] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 10; j++) {
            tempArray[i][j] = GameScene::tetrisBoard[i][j];
        }
    }

    int firstCount = GameScene::boardCount();

    setValue(0);

    int** backup;
    backup = new int* [4];
    for (int i = 0; i < 4; ++i) {
        backup[i] = new int[2];
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
                delete[] backup[j];
            }
            delete[] backup;
            return;
        }
    }

    int secondCount = GameScene::boardCount();

    if (firstCount != secondCount) {
        copyArray(tempArray);
        for (int j = 0; j < 4; ++j) {
            blockArray[j][0] = backup[j][0];
            blockArray[j][1] = backup[j][1];
            delete[] backup[j];
        }
        delete[] backup;
        return;
    }

    for (int j = 0; j < 4; ++j) {
        delete[] backup[j];
    }
    delete[] backup;
}

void Block::moveSideways(int direction) {
    int tempArray[11][10] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};

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

void Block::copyArray(int array[11][10]) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 10; j++) {
            GameScene::tetrisBoard[i][j] = array[i][j];
        }
    }
}

Block::~Block() {
    for (int i = 0; i < 4; i++) {
        delete[] Block::blockArray[i];
    }
    delete[] Block::blockArray;
}

void Block::rotateBlock() {}

void Block::moveDown() {
    int tempArray[11][10] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};

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
            GameScene::tetrisBoard[blockArray[i][1]][blockArray[i][0]] = 1;
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
