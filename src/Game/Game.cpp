#include <time.h>
#include "Game.h"
#include "../Display/Display.h"
#include "../Communication/SendQueue.h"
#include "../Communication/Frame.h"

int Game::gameSeed = 0;

void Game::init() {
    Display::drawGameBorder();
    Display::drawHoldSection();
    Display::drawNextSection();
    Display::drawScore();
    Display::drawDemoBlocks();

    setRandomSeed();
}

void Game::setRandomSeed() {
    srand(micros());
}

int Game::generateRandomSeed() {
    return rand() % 63;
}

void Game::endGame() {
    setRandomSeed();
}

void Game::startGame() {
    gameSeed = generateRandomSeed();
    uint8_t frame = (new Frame(gameSeed, Frame::SEED_TYPE))->getFrame();
    SendQueue::addToQueue(frame);
    srand(gameSeed);
}

void Game::startGame(int seed) {
    gameSeed = seed;
    srand(gameSeed);
}


