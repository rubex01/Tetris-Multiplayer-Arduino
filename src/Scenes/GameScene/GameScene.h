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
    static int lastBoard[11][10];
    static bool gameTickReached;
    static bool gameOver;
    static int gameCounter;
    static bool moveTickReached;
    static int tickValue;
    static void checkForFullRows();
    static int moveTickCounter;
   //  static bool startTone;

 private:
    static int gameSeed;
    static Block* currentBlock;
    static void drawBoard();
    static void initTimer();
    static void setRandomSeed();
    static int generateRandomSeed();
    static void generateRowFrame(int height);
};

#endif  // SRC_SCENES_GAMESCENE_GAMESCENE_H_
