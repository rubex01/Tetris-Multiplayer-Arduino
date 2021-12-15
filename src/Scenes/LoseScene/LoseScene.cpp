#include "LoseScene.h"
#include "../../Display/Display.h" 

void LoseScene::init() {
    Display::drawText(60, 50, 2, "haha loser", ILI9341_RED);
}

void LoseScene::drawScene() {
}
