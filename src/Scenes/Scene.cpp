#include "Scene.h"
#include "../Display/Display.h"
#include "StartScene/StartScene.h"
#include "GameScene/GameScene.h"
#include "WinScene/WinScene.h"
#include "LoseScene/LoseScene.h"
#include "Leaderboard/Leaderboard.h"

Scene* Scene::currentScene = nullptr;

/**
 * Called continuously, the method calls the drawScene method in the current selected scene
 */
void Scene::draw() {
    currentScene->drawScene();
}

/**
 * Update scene, this method calls init on the new scene
 *
 * @param scene
 */
void Scene::setScene(const Constants& scene) {
    delete currentScene;
    Display::fillRect(0, 0, 240, 320, ILI9341_BLACK);
    switch (scene) {
        case START_SCENE:
            currentScene = new StartScene();
            break;
        case GAME_SCENE:
            currentScene = new GameScene();
            break;
        case WIN_SCENE:
            currentScene = new WinScene();
            break;
        case LOSE_SCENE:
            currentScene = new LoseScene();
            break;
        case LEADERBOARD_SCENE:
            currentScene = new Leaderboard();
            break;
    }
}

Scene* Scene::getCurrentScene() {
    return currentScene;
}
