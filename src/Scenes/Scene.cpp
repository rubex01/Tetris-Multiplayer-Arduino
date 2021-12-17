#include "Scene.h"
#include "../Display/Display.h"
#include "StartScene/StartScene.h"
#include "GameScene/GameScene.h"
#include "WinScene/WinScene.h"
#include "LoseScene/LoseScene.h"

int Scene::currentScene = Scene::START_SCENE;

/**
 * Called continuously, the method calls the drawScene method in the current selected scene
 */
void Scene::draw() {
    switch (currentScene) {
        case START_SCENE:
            StartScene::drawScene();
            break;
        case GAME_SCENE:
            GameScene::drawScene();
            break;
        case WIN_SCENE:
            WinScene::drawScene();
            break;
        case LOSE_SCENE:
            LoseScene::drawScene();
            break;
    }
}

/**
 * Update scene, this method calls init on the new scene
 *
 * @param scene
 */
void Scene::setScene(const Constants& scene) {
    Display::fillRect(0, 0, 240, 320, ILI9341_BLACK);
    currentScene = scene;
    switch (currentScene) {
        case START_SCENE:
            StartScene::init();
            break;
        case GAME_SCENE:
            GameScene::init();
            break;
        case WIN_SCENE:
            WinScene::init();
            break;
        case LOSE_SCENE:
            LoseScene::init();
            break;
    }
}
