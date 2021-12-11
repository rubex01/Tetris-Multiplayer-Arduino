#include "Game.h"
#include "../Display/Display.h"

void Game::init() {
    Display::drawGameBorder();
    Display::drawHoldSection();
    Display::drawNextSection();
    Display::drawScore();
    Display::drawDemoBlocks();
}
