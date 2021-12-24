#include "WinScene.h"
#include "../../Sound/NewTone.h"
#include "../../Display/Display.h"
#include "../../Controller/Controller.h"
#include "../../HighScore/HighScore.h"
#include "../Helpers/drawHighScoreMessage.h"

/**
 * Win scene constructor
 */
WinScene::WinScene() {
    NewTone::startTone = false;
    NewTone::noNewTone(NewTone::buzzer);  // Toon uit

    titleAnimationCounter = 0;
    titleColorAnimationCounter = 0;
    continueAnimationCounter = 0;

    drawHighScoreMessage();
}

/**
 * Is called by the main while loop. Draws animations and checks for input to continue to start scene.
 */
void WinScene::drawScene() {
    bool* actions = Controller::getNonContinuingTriggerActions();
    if (actions[Controller::Z_BUTTON] || actions[Controller::C_BUTTON]) {
        Scene::setScene(Scene::START_SCENE);
        delete[] actions;
        return;
    }
    delete[] actions;

    continueTextAnimation();
    continueAnimationCounter++;

    if (titleAnimationCounter != 40) {
        titleAnimationCounter++;
        titleTextAnimation();
    } else {
        titleColorAnimationCounter++;
        titleColorAnimation();
    }
}

/**
 * Animation for the "click to continue" text at bottom of lose screen
 */
void WinScene::continueTextAnimation() {
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
 * Color animation for YOU WON title
 */
void WinScene::titleColorAnimation() {
    if (titleColorAnimationCounter == 1) {
        Display::drawText(80, 100, 5, "YOU", Display::colors[CYAN][0]);
        Display::drawText(80, 150, 5, "WON", Display::colors[CYAN][0]);
    } else if (titleColorAnimationCounter == 600) {
        Display::drawText(80, 100, 5, "YOU", Display::colors[BLUE][0]);
        Display::drawText(80, 150, 5, "WON", Display::colors[BLUE][0]);
    } else if (titleColorAnimationCounter == 1200) {
        Display::drawText(80, 100, 5, "YOU", Display::colors[ORANGE][0]);
        Display::drawText(80, 150, 5, "WON", Display::colors[ORANGE][0]);
    } else if (titleColorAnimationCounter == 1800) {
        Display::drawText(80, 100, 5, "YOU", Display::colors[YELLOW][0]);
        Display::drawText(80, 150, 5, "WON", Display::colors[YELLOW][0]);
    } else if (titleColorAnimationCounter == 2400) {
        Display::drawText(80, 100, 5, "YOU", Display::colors[GREEN][0]);
        Display::drawText(80, 150, 5, "WON", Display::colors[GREEN][0]);
    } else if (titleColorAnimationCounter == 3000) {
        Display::drawText(80, 100, 5, "YOU", Display::colors[PURPLE][0]);
        Display::drawText(80, 150, 5, "WON", Display::colors[PURPLE][0]);
    } else if (titleColorAnimationCounter == 3600) {
        Display::drawText(80, 100, 5, "YOU", Display::colors[RED][0]);
        Display::drawText(80, 150, 5, "WON", Display::colors[RED][0]);
    } else if (titleColorAnimationCounter == 4200) {
        titleColorAnimationCounter = 0;
    }
}

/**
 * Zoom in animation for YOU WON title
 */
void WinScene::titleTextAnimation() {
    if (titleAnimationCounter == 0) {
        Display::drawText(120, 100, 1, "YOU", ILI9341_YELLOW);
        Display::drawText(120, 150, 1, "WON", ILI9341_YELLOW);
    } else if (titleAnimationCounter == 10) {
        Display::drawText(120, 100, 1, "YOU", ILI9341_BLACK);
        Display::drawText(120, 150, 1, "WON", ILI9341_BLACK);
        Display::drawText(110, 100, 2, "YOU", ILI9341_YELLOW);
        Display::drawText(110, 150, 2, "WON", ILI9341_YELLOW);
    } else if (titleAnimationCounter == 20) {
        Display::drawText(110, 100, 2, "YOU", ILI9341_BLACK);
        Display::drawText(110, 150, 2, "WON", ILI9341_BLACK);
        Display::drawText(100, 100, 3, "YOU", ILI9341_YELLOW);
        Display::drawText(100, 150, 3, "WON", ILI9341_YELLOW);
    } else if (titleAnimationCounter == 30) {
        Display::drawText(100, 100, 3, "YOU", ILI9341_BLACK);
        Display::drawText(100, 150, 3, "WON", ILI9341_BLACK);
        Display::drawText(90, 100, 4, "YOU", ILI9341_YELLOW);
        Display::drawText(90, 150, 4, "WON", ILI9341_YELLOW);
    } else if (titleAnimationCounter == 40) {
        Display::drawText(90, 100, 4, "YOU", ILI9341_BLACK);
        Display::drawText(90, 150, 4, "WON", ILI9341_BLACK);
        Display::drawText(80, 100, 5, "YOU", ILI9341_YELLOW);
        Display::drawText(80, 150, 5, "WON", ILI9341_YELLOW);
    }
}
