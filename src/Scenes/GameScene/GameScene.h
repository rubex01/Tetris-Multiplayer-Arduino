#ifndef SRC_SCENES_GAMESCENE_GAMESCENE_H_
#define SRC_SCENES_GAMESCENE_GAMESCENE_H_

#include <stdint.h>
#include <stdio.h>
#include "../Scene.h"
#include "../../Tetris/Block.h"

class GameScene: public Scene {
 public:
    static uint8_t tetrisBoard[11][10];
    static uint8_t lastBoard[11][10];
    static uint8_t moveTickCounter;
    static uint8_t gameCounter;
    static uint8_t tickValue;
    static bool blockIsMoving;
    static bool gameTickReached;
    static bool gameOver;
    static bool moveTickReached;

    GameScene();
    void drawScene();
    static void startGame();
    static void startGame(int seed);
    static void endGame(bool lostGame);
    static int boardCount();
    static void checkForFullRows();

 private:
    static uint8_t gameSeed;
    static Block* currentBlock;
    static Block* nextBlock;
    static void drawBoard();
    static void setRandomSeed();
    static int generateRandomSeed();
    static void generateRowFrame(int height);
    static bool checkForReceivedFrames();
    static void addOpponentReceivedRow(uint8_t data);
};

#endif  // SRC_SCENES_GAMESCENE_GAMESCENE_H_
