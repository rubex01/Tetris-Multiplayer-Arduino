#include "GameScene.h"
#include "../../Display/Display.h"
#include "../../Communication/SendQueue.h"
#include "../../Communication/Frame.h"

int GameScene::gameSeed = 0;

void GameScene::init() {
    Display::drawGameBorder();
    Display::drawHoldSection();
    Display::drawNextSection();
    Display::drawScore();
    Display::drawDemoBlocks();

    setRandomSeed();
    if (gameSeed == 0)
        startGame();
}

void GameScene::drawScene() {
}

void GameScene::setRandomSeed() {
    srand(micros());
}

int GameScene::generateRandomSeed() {
    return rand() % 63;
}

void GameScene::endGame() {
    setRandomSeed();
}

void GameScene::startGame() {
    gameSeed = generateRandomSeed();
    uint8_t frame = (new Frame(gameSeed, Frame::SEED_TYPE))->getFrame();
    SendQueue::addToQueue(frame);
    srand(gameSeed);
}

void GameScene::startGame(int seed) {
    gameSeed = seed;
    srand(gameSeed);
}
