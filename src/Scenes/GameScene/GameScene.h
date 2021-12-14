#ifndef SRC_SCENES_GAMESCENE_GAMESCENE_H_
#define SRC_SCENES_GAMESCENE_GAMESCENE_H_

#include "../Scene.h"

class GameScene: public Scene {
 public:
    static void init();
    static void startGame();
    static void startGame(int seed);
    static void endGame();
    static void drawScene();

 private:
    static int gameSeed;

    static void setRandomSeed();
    static int generateRandomSeed();
};

#endif  // SRC_SCENES_GAMESCENE_GAMESCENE_H_
