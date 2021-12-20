#include "GameScene.h"
#include "../../Display/Display.h"
#include "../../Communication/SendQueue.h"
#include "../../Communication/Frame.h"
#include "../../Sound/NewTone.h"

int GameScene::gameSeed = 0;

/**
 * Init game scene, draw all game borders and elements
 */
void GameScene::init() {
    Display::drawGameBorder();
    Display::drawHoldSection();
    Display::drawNextSection();
    Display::drawScore();
    Display::drawDemoBlocks();
    NewTone::aNewTone(NewTone::buzzer, NewTone::melody[NewTone::thisNote], NewTone::noteDuration*0.9);

    setRandomSeed();
    if (gameSeed == 0)
        startGame();
}

/**
 * Draw current game state, score etc.
 */
void GameScene::drawScene() {
}

/**
 * Sets a random seed for the default random function
 */
void GameScene::setRandomSeed() {
    srand(micros());
}

/**
 * Generates a new random seed between 0 and 64 using the random function
 *
 * @return int
 */
int GameScene::generateRandomSeed() {
    return rand() % 63;
}

/**
 * Ends the game and resets the random seed
 */
void GameScene::endGame() {
    setRandomSeed();
}

/**
 * Starts the game with own random seed, also adds this seed to sendQueue so second player will receive the seed
 */
void GameScene::startGame() {
    gameSeed = generateRandomSeed();
    Frame frame(gameSeed, Frame::SEED_TYPE);
    SendQueue::addToQueue(frame);
    srand(gameSeed);
}

/**
 * Start game with received seed
 *
 * @param seed
 */
void GameScene::startGame(int seed) {
    gameSeed = seed;
    srand(gameSeed);
}
