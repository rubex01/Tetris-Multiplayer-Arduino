#include "GameScene.h"
#include "../../Display/Display.h"
#include "../../Communication/SendQueue.h"
#include "../../Communication/Frame.h"
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
int GameScene::tickValue = 8;

int volatile counter = 0;

// ISR(TIMER1_COMPA_vect) {
ISR(TIMER2_COMPA_vect) {
    if(counter++ > 4) {
        counter = 0;
        if (GameScene::gameCounter >= GameScene::tickValue) {
            GameScene::gameTickReached = true;
            GameScene::gameCounter = 0;
        }
        GameScene::moveTickReached = true;
        GameScene::gameCounter++;
    }
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

void GameScene::checkForFullRows() {
    for (int i = 0; i < 11; ++i) {
        boolean fullRow = true;
        for (int j = 0; j < 10; ++j) {
            if (GameScene::tetrisBoard[i][j] == 0) {
                fullRow = false;
                break;
            }
        }
        if (fullRow) {
            for (int j = i; j >= 0; --j) {
                for (int k = 0; k < 10; ++k) {
                    if (j == 0)
                        GameScene::tetrisBoard[j][k] = 0;
                    else
                        GameScene::tetrisBoard[j][k] = GameScene::tetrisBoard[j-1][k];
                }
            }
        }
    }
}

int GameScene::boardCount() {
    int count = 0;
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 10; j++) {
            if (GameScene::tetrisBoard[i][j] != 0) {
                count++;
            }
        }
    }
    return count;
}

// void GameScene::initTimer() {
//     TCCR1A = 0;
//     TCCR1B |= (1 << CS12)|(1 << CS10)|(1 << WGM12);
//     TCCR1C = 0;
//     OCR1A = (15624/18);
//     TCNT1 = 0;
//     TIMSK1 |= (1 << OCIE1A);
// }

void GameScene::initTimer() {
    // TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22)|(1 << CS21)|(1 << CS20);
    OCR2A = 215;  // 255 / 18 ~= 14
    // OCR2B = 100;
    TCNT2 = 0;
    TIMSK2 |= (1 << OCIE2A);
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

    bool* actions = Controller::getActions();
    bool* array2 = Controller::getNonContinuingTriggerActions();

    if (GameScene::blockIsMoving) {
        if (actions[Controller::DOWN]) {
            GameScene::tickValue = 1;
        } else {
            GameScene::tickValue = 8;
        }

        if (array2[Controller::Z_BUTTON]) {
            GameScene::currentBlock->rotate();
        }

        if (actions[Controller::RIGHT]) {
            GameScene::currentBlock->moveSideways(1);
        } else if (actions[Controller::LEFT]) {
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
    delete[] actions;
    delete[] array2;
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
