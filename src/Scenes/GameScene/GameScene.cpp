#include "GameScene.h"
#include "../../Display/Display.h"
#include "../../Communication/SendQueue.h"
#include "../../Communication/Frame.h"
#include "../../Controller/Controller.h"
#include "../../Tetris/BlockFactory.h"
#include "../../Tetris/Score.h"
#include "../../Communication/ReceivedData.h"
#include "../../HighScore/HighScore.h"

int GameScene::gameSeed = 0;
int GameScene::tetrisBoard[11][10] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};
int GameScene::lastBoard[11][10] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};
Block* GameScene::currentBlock = nullptr;
bool GameScene::gameTickReached = false;
bool GameScene::blockIsMoving = true;
bool GameScene::gameOver = false;
int GameScene::gameCounter = 0;
bool GameScene::moveTickReached = false;
int GameScene::tickValue = 68;
int GameScene::moveTickCounter = 0;
Block* GameScene::nextBlock = nullptr;

ISR(TIMER2_COMPA_vect) {
    if (GameScene::gameCounter >= GameScene::tickValue) {
        GameScene::gameTickReached = true;
        GameScene::gameCounter = 0;
    }
    if (GameScene::moveTickCounter == 4) {
        GameScene::moveTickReached = true;
        GameScene::moveTickCounter = 0;
    }
    GameScene::moveTickCounter++;
    GameScene::gameCounter++;
}

/**
 * Init game scene, draw all game borders and elements
 */
GameScene::GameScene() {
    if (gameSeed == 0) {
        setRandomSeed();
        startGame();
    }

    Display::drawGameBorder();
    Display::drawHoldSection();
    Display::drawNextSection();
    Score::updateScore(0);
    GameScene::initTimer();
    GameScene::nextBlock = BlockFactory::createBlock(6);
    GameScene::currentBlock = BlockFactory::createBlock(rand() % 7);
    GameScene::nextBlock->drawSectionBlock();
    currentBlock->initBlock();
    GameScene::drawBoard();
}

/**
 * Draw all new blocks on the tetrisBoard with the correct color
 */
void GameScene::drawBoard() {
    int y = 100;
    for (int i = 0; i < 11; i++) {
        int x = 20;
        for (int j = 0; j < 10; j++) {
            if (lastBoard[i][j] != 0 && GameScene::tetrisBoard[i][j] == 0) {
                Display::fillRect(x, y, 20, 20, GameScene::tetrisBoard[i][j]);
            } else if (lastBoard[i][j] != GameScene::tetrisBoard[i][j]) {
                Display::drawTetrisBlock(x, y, tetrisBoard[i][j]);
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

/**
 * Check the board for any full rows, remove them if found
 */
void GameScene::checkForFullRows() {
    int totalFullRows = 0;
    for (int i = 0; i < 11; ++i) {
        boolean fullRow = true;
        for (int j = 0; j < 10; ++j) {
            if (GameScene::tetrisBoard[i][j] == 0) {
                fullRow = false;
                break;
            }
        }
        if (fullRow) {
            totalFullRows++;
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
    if (totalFullRows != 0) {
        Score::updateScore(totalFullRows);
        generateRowFrame(totalFullRows);
    }
}

/**
 * Generates frames for sending rows with gaps for the opponent
 *
 * @param height
 */
void GameScene::generateRowFrame(int height) {
    uint8_t location = currentBlock->blockArray[0][0];
    uint8_t data = (location << 2);

    for (int i = 0; i < 2; ++i)
        if ((height-1) & (1 << i))
            data |= (1 << i);

    Frame rowFrame(data, Frame::ROW_TYPE);
    SendQueue::addToQueue(rowFrame);
}

/**
 * Get the count of all single tetris blocks on the board
 */
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

/**
 * Init timer 2 to be later used for the game loop
 */
void GameScene::initTimer() {
    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22)|(1 << CS21)|(1 << CS20);
    OCR2A = 255;
    TIMSK2 |= (1 << OCIE2A);
}

/**
 * Draw current game state, score etc.
 */
void GameScene::drawScene() {
    if (GameScene::gameOver) {
        endGame(true);
        return;
    }

    if (checkForReceivedFrames()) return;

    if (!moveTickReached) {
        return;
    }

    bool* actions = Controller::getActions();
    bool* array2 = Controller::getNonContinuingTriggerActions();

    if (GameScene::blockIsMoving) {
        if (actions[Controller::DOWN]) {
            GameScene::tickValue = 2;
        } else {
            GameScene::tickValue = 68;
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
        GameScene::currentBlock = GameScene::nextBlock;
        GameScene::currentBlock->initBlock();
        GameScene::nextBlock = BlockFactory::createBlock(rand() % 7);
        Display::clearNextSection();
        GameScene::nextBlock->drawSectionBlock();
        blockIsMoving = true;
        GameScene::gameTickReached = false;
    }
    moveTickReached = false;
    GameScene::drawBoard();
    delete[] actions;
    delete[] array2;
}

/**
 * Adds one row to the bottom of the playing field with a gap
 *
 * @param data
 */
void GameScene::addOpponentReceivedRow(uint8_t data) {
    GameScene::currentBlock->setValue(0);

    int height = 0;
    for (int i=0; i < 2; i++)
        if (data & (1 << i))
            height |= (1 << i);
    height++;

    int gapLocation = 0;
    for (int i=2; i < 6; i++)
        if (data & (1 << i))
            gapLocation |= (1 << (i-2));

    for (int i = 0; i < 11; i++) {
        if (i == 10 || i + height > 10) break;
        for (int j = 0; j < 10; j++) {
            GameScene::tetrisBoard[i][j] = GameScene::tetrisBoard[i+height][j];
        }
    }

    for (int i = 11-height; i < 11; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (j != gapLocation)
                GameScene::tetrisBoard[i][j] = ENEMYBLOCK;
            else
                GameScene::tetrisBoard[i][j] = 0;
        }
    }

    int count = boardCount();
    GameScene::currentBlock->setValue(currentBlock->blockColor);
    int count2 = boardCount();

    if ((count2 - count) != 4) gameOver = true;
}

/**
 * Check if there are any new frames that have been received
 *
 * @return bool if received new row
 */
bool GameScene::checkForReceivedFrames() {
    if (!ReceivedData::newResultsAvailable()) return false;

    bool returnVal = false;

    uint8_t * frames = ReceivedData::getResults();
    for (int i = 0; i < 20; ++i) {
        if (frames[i] == 0) continue;
        Frame a = Frame(frames[i]);
        uint8_t type = a.getType();
        if (type == Frame::ROW_TYPE) {
            addOpponentReceivedRow(a.getData());
            returnVal = true;
        } else if (type == Frame::LOST_TYPE) {
            returnVal = true;
            endGame(false);
        }
    }

    return returnVal;
}

/**
 * Sets a random seed for the default random function
 */
void GameScene::setRandomSeed() {
    srand(micros());
}

/**
 * Generates a new random seed between 0 and 64 using the random function
 *
 * @return int
 */
int GameScene::generateRandomSeed() {
    return rand() % 63;
}

/**
 * Ends the game and resets all variables + random seed
 */
void GameScene::endGame(bool lostGame) {
    HighScore::newScore((uint16_t) Score::getCurrentScore());

    delete currentBlock;
    delete nextBlock;
    setRandomSeed();
    Score::clearScore();

    gameSeed = 0;
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 10; ++j) {
            tetrisBoard[i][j] = 0;
            lastBoard[i][j] = 0;
        }
    }

    gameTickReached = false;
    blockIsMoving = true;
    gameOver = false;
    gameCounter = 0;
    moveTickReached = false;
    moveTickCounter = 0;

    if (lostGame)
        Scene::setScene(Scene::LOSE_SCENE);
    else
        Scene::setScene(Scene::WIN_SCENE);
}

/**
 * Starts the game with own random seed, also adds this seed to sendQueue so second player will receive the seed
 */
void GameScene::startGame() {
    gameSeed = generateRandomSeed();
    Frame frame(gameSeed, Frame::SEED_TYPE);
    SendQueue::addToQueue(frame);
    srand(gameSeed);
}

/**
 * Start game with received seed
 *
 * @param seed
 */
void GameScene::startGame(int seed) {
    gameSeed = seed;
    srand(gameSeed);
}
