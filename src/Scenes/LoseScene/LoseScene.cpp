#include "LoseScene.h"
#include "../../Sound/NewTone.h"
#include "../../Display/Display.h"

/**
 * Init lose scene
 */
void LoseScene::init() {
    NewTone::noNewTone(NewTone::buzzer);  // Toon uit
}

/**
 * Draw lose scene
 */
void LoseScene::drawScene() {
}
