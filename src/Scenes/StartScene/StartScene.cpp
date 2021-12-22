#include "StartScene.h"
#include "../../Display/Display.h"
#include "../../Controller/Controller.h"
#include "../../Communication/ReceivedData.h"
#include "../../Communication/Frame.h"
#include "../GameScene/GameScene.h"

int StartScene::selected = 0;

/**
 * Init start scene
 */
void StartScene::init() {
    Display::drawText(60, 50, 2, "Start game", ILI9341_YELLOW);
    Display::drawText(60, 80, 2, "Other button", ILI9341_YELLOW);
    Display::fillCircle(40, 55, 5, ILI9341_YELLOW);
}

/**
 * Draws the selected item in the start menu
 *
 * @param dirUp
 */
void StartScene::drawSelected(bool dirUp) {
    if ((dirUp && selected == 0) || (!dirUp && selected == 1)) return;
    Display::fillCircle(40, 55+(selected*30), 5, ILI9341_BLACK);
    if (dirUp && selected != 0) selected--;
    else if (selected != 1) selected++;
    Display::fillCircle(40, 55+(selected*30), 5, ILI9341_YELLOW);
}

/**
 * Draws scene and checks for input from nunchuk to update states
 */
void StartScene::drawScene() {
    if (!checkForSeedPacket()) {
        bool* actionArray = Controller::getActions();
        if (actionArray[Controller::Z_BUTTON]) {
            Scene::setScene(Scene::GAME_SCENE);
        }
        if (actionArray[Controller::UP] || actionArray[Controller::DOWN]) {
            drawSelected(actionArray[Controller::UP]);
        }
        delete[] actionArray;
    }
}

/**
 * Checks for a new seed packet and returns true if it found one
 *
 * @return bool
 */
bool StartScene::checkForSeedPacket() {
    bool returnValue = false;
    if (ReceivedData::newResultsAvailable()) {
        uint8_t* data = ReceivedData::getResults();
        for (int i = 0; i < 20; ++i) {
            if (data[i] == 0) continue;
            Frame a = Frame(data[i]);
            if (a.getType() == Frame::SEED_TYPE) {
                GameScene::startGame(a.getData());
                Scene::setScene(Scene::GAME_SCENE);
                returnValue = true;
            }
        }
        delete[] data;
    }
    return returnValue;
}
