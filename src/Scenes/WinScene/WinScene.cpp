#include "WinScene.h"
#include "../../Sound/NewTone.h"

/**
 * Init win scene
 */
void WinScene::init() {
    NewTone::startTone = false;
    NewTone::noNewTone(NewTone::buzzer);  // Toon uit
}

/**
 * Draw win scene
 */
void WinScene::drawScene() {
}
