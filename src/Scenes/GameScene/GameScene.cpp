#include "GameScene.h"
#include "../../Display/Display.h"
#include "../../Communication/SendQueue.h"
#include "../../Communication/Frame.h"
#include "../../Tetris/Tetrominoes/OBlock.h"
#include "../../Tetris/Tetrominoes/TBlock.h"
#include "../../Tetris/Tetrominoes/IBlock.h"
#include "../../Tetris/Tetrominoes/JBlock.h"
#include "../../Tetris/Tetrominoes/LBlock.h"
#include "../../Tetris/Tetrominoes/SBlock.h"
#include "../../Tetris/Tetrominoes/ZBlock.h"
#include "../../Controller/Controller.h"
#include "../../Tetris/BlockFactory.h"

int GameScene::gameSeed = 0;
int GameScene::tetrisBoard[11][10] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};
int GameScene::lastBoard[11][10] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};
Block* GameScene::currentBlock = nullptr;
bool GameScene::gameTickReached = false;
bool GameScene::blockIsMoving = true;
bool GameScene::gameOver = false;
int GameScene::gameCounter = 0;
bool GameScene::moveTickReached = false;
int GameScene::tickValue = 20;

ISR(TIMER1_COMPA_vect) {
    if (GameScene::gameCounter >= GameScene::tickValue) {
        GameScene::gameTickReached = true;
        GameScene::gameCounter = 0;
    }
    GameScene::moveTickReached = true;
    GameScene::gameCounter++;
}

void GameScene::init() {
    if (gameSeed == 0) {
        setRandomSeed();
        startGame();
    }

    Display::drawGameBorder();
    Display::drawHoldSection();
    Display::drawNextSection();
    Display::drawScore();
    GameScene::initTimer();
    GameScene::currentBlock = BlockFactory::createBlock(rand() % 7);
    currentBlock->initBlock();
    GameScene::drawBoard();
}

void GameScene::drawBoard() {
    int y = 100;
    for (int i = 0; i < 11; i++) {
        int x = 20;
            for (int j = 0; j < 10; j++) {
                if (lastBoard[i][j] != 0 && GameScene::tetrisBoard[i][j] == 0) {
                Display::fillRect(x, y, 20, 20, GameScene::tetrisBoard[i][j]);
                } else if (lastBoard[i][j] == 0 && GameScene::tetrisBoard[i][j] != 0) {
                    Display::drawTetrisBlock(x, y, currentBlock->blockColor);
                }
                x += 20;
            }
        y += 20;
    }
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 10; j++) {
            lastBoard[i][j] = GameScene::tetrisBoard[i][j];
        }
    }
}

int GameScene::boardCount() {
    int count = 0;
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 10; j++) {
            if (GameScene::tetrisBoard[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}

void GameScene::initTimer() {
    TCCR1A = 0;
    TCCR1B |= (1 << CS12)|(1 << CS10)|(1 << WGM12);
    TCCR1C = 0;
    OCR1A = (15624/18);
    TCNT1 = 0;
    TIMSK1 |= (1 << OCIE1A);
}

void GameScene::drawScene() {
    if (GameScene::gameOver) {
        Scene::setScene(Scene::LOSE_SCENE);
        Scene::draw();
        return;
    }
    if (!moveTickReached) {
        return;
    }

    bool* array = Controller::getActions();


    if (GameScene::blockIsMoving) {
        if (array[3]) {
            GameScene::tickValue = 2;
        } else {
            GameScene::tickValue = 6;
        }
        if (array[0]) {
            GameScene::currentBlock->moveSideways(1);
        } else if (array[1]) {
            GameScene::currentBlock->moveSideways(-1);
        }

        if (GameScene::gameTickReached) {
            GameScene::currentBlock->moveDown();
            GameScene::gameTickReached = false;
        }
    } else {
        delete GameScene::currentBlock;
        GameScene::currentBlock = BlockFactory::createBlock(rand() % 7);
        GameScene::currentBlock->initBlock();
        blockIsMoving = true;
        GameScene::gameTickReached = false;
    }
    moveTickReached = false;
    GameScene::drawBoard();
    delete[] array;
}

void GameScene::setRandomSeed() {
    srand(micros());
}

int GameScene::generateRandomSeed() {
    return rand() % 63;
}

void GameScene::endGame() {
    setRandomSeed();
}

void GameScene::startGame() {
    gameSeed = generateRandomSeed();
    uint8_t frame = (new Frame(gameSeed, Frame::SEED_TYPE))->getFrame();
    SendQueue::addToQueue(frame);
    srand(gameSeed);
}

void GameScene::startGame(int seed) {
    gameSeed = seed;
    srand(gameSeed);
}
