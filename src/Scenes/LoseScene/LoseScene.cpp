#include "LoseScene.h"
#include "../../Display/Display.h"
#include "../../Communication/SendQueue.h"

int LoseScene::titleAnimationCounter = 0;
int LoseScene::continueAnimationCounter = 0;

/**
 * Init lose scene
 */
void LoseScene::init() {
    Frame loseFrame(21, Frame::LOST_TYPE);
    SendQueue::addToQueue(loseFrame);
}

/**
 * Draw lose scene
 */
void LoseScene::drawScene() {
    continueTextAnimation();
    continueAnimationCounter++;

    if (titleAnimationCounter != 40) {
        titleAnimationCounter++;
        titleTextAnimation();
    }
}

/**
 * Animation for the "click to continue" text at bottom of lose screen
 */
void LoseScene::continueTextAnimation() {
    if (continueAnimationCounter == 1) {
        Display::drawText(70, 240, 1, "Click to continue...", ILI9341_BLACK);
        Display::drawText(70, 240, 1, "Click to continue.", ILI9341_YELLOW);
    } else if (continueAnimationCounter == 600) {
        Display::drawText(70, 240, 1, "Click to continue..", ILI9341_YELLOW);
    } else if (continueAnimationCounter == 1200) {
        Display::drawText(70, 240, 1, "Click to continue...", ILI9341_YELLOW);
    } else if (continueAnimationCounter == 1800) {
        continueAnimationCounter = 0;
    }
}

/**
 * Zoom in animation for game over title
 */
void LoseScene::titleTextAnimation() {
    if (titleAnimationCounter == 0) {
        Display::drawText(110, 100, 1, "GAME", ILI9341_RED);
        Display::drawText(110, 150, 1, "OVER", ILI9341_RED);
    } else if (titleAnimationCounter == 10) {
        Display::drawText(110, 100, 1, "GAME", ILI9341_BLACK);
        Display::drawText(110, 150, 1, "OVER", ILI9341_BLACK);
        Display::drawText(100, 100, 2, "GAME", ILI9341_RED);
        Display::drawText(100, 150, 2, "OVER", ILI9341_RED);
    } else if (titleAnimationCounter == 20) {
        Display::drawText(100, 100, 2, "GAME", ILI9341_BLACK);
        Display::drawText(100, 150, 2, "OVER", ILI9341_BLACK);
        Display::drawText(90, 100, 3, "GAME", ILI9341_RED);
        Display::drawText(90, 150, 3, "OVER", ILI9341_RED);
    } else if (titleAnimationCounter == 30) {
        Display::drawText(90, 100, 3, "GAME", ILI9341_BLACK);
        Display::drawText(90, 150, 3, "OVER", ILI9341_BLACK);
        Display::drawText(80, 100, 4, "GAME", ILI9341_RED);
        Display::drawText(80, 150, 4, "OVER", ILI9341_RED);
    } else if (titleAnimationCounter == 40) {
        Display::drawText(80, 100, 4, "GAME", ILI9341_BLACK);
        Display::drawText(80, 150, 4, "OVER", ILI9341_BLACK);
        Display::drawText(70, 100, 5, "GAME", ILI9341_RED);
        Display::drawText(70, 150, 5, "OVER", ILI9341_RED);
    }
}
