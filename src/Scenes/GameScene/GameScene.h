#ifndef SRC_SCENES_GAMESCENE_GAMESCENE_H_
#define SRC_SCENES_GAMESCENE_GAMESCENE_H_

#include "../Scene.h"
#include "../../Tetris/Block.h"

class GameScene: public Scene {
 public:
    static void init();
    static void startGame();
    static void startGame(int seed);
    static void endGame();
    static void drawScene();
    static int boardCount();
    static bool blockIsMoving;
    static int tetrisBoard[11][10];
    static Block* currentBlock;
    static bool gameTickReached;
    static bool gameOver;
    static int gameTicks;

 private:
    static int gameSeed;
    
    static void drawBoard();
    static void initTimer();
    static void setRandomSeed();
    static int generateRandomSeed();
};

#endif  // SRC_SCENES_GAMESCENE_GAMESCENE_H_
