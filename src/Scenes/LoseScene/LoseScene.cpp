#include "LoseScene.h"
#include "../../Sound/NewTone.h"
#include "../../Display/Display.h"

/**
 * Init lose scene
 */
void LoseScene::init() {
    NewTone::startTone = false;
    NewTone::noNewTone(NewTone::buzzer);  // Toon uit
}

/**
 * Draw lose scene
 */
void LoseScene::drawScene() {
}
