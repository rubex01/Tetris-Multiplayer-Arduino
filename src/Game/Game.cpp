#include <time.h>
#include "Game.h"
#include "../Display/Display.h"
#include "../Communication/SendQueue.h"
#include "../Communication/Frame.h"

// Interupt demo purpose
ISR(INT1_vect) {
    if(PIND & (1 << PIND3)) {
        Game::startGame();
    }
}

int Game::gameSeed = 0;

void Game::init() {
    Display::drawGameBorder();
    Display::drawHoldSection();
    Display::drawNextSection();
    Display::drawScore();
    Display::drawDemoBlocks();

    // Demo purpose
    PORTD |= (1 << PORTD3);
    EIMSK |= (1 << INT1);
    EICRA |= (1 << ISC10);

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

    // Demo purpose
    Serial.print("Starting game local with seed ");
    Serial.print(gameSeed);
    Serial.println();

    endGame();
}

void Game::startGame(int seed) {
    gameSeed = seed;
    srand(gameSeed);

    // Demo purpose
    Serial.print("Starting game from seed packet with seed ");
    Serial.print(gameSeed);
    Serial.println();

    endGame();
}


