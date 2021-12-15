#include "GameScene.h"
#include "../../Display/Display.h"
#include "../../Communication/SendQueue.h"
#include "../../Communication/Frame.h"
#include "../../Tetris/Square.h"
#include "../../Controller/Controller.h"
volatile int counter = 0;
volatile bool test = false;

ISR(TIMER1_COMPA_vect){
    if(counter == 12){
        GameScene::gameTickReached = true;
        counter = 0;
    }
    test = true;
    counter++;
}

int GameScene::gameSeed = 0;
int GameScene::tetrisBoard[11][10] = {{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};
int lastBoard[11][10] = {{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};
Block* GameScene::currentBlock = nullptr;
bool GameScene::gameTickReached = false;
bool GameScene::blockIsMoving = true;
bool GameScene::gameOver = false;
int GameScene::gameTicks = 0;

void GameScene::init() {
    Display::drawGameBorder();
    Display::drawHoldSection();
    Display::drawNextSection();
    Display::drawScore();
    GameScene::initTimer();
    GameScene::currentBlock = new Square(4,0);
    currentBlock->initBlock();
    GameScene::drawBoard();

    setRandomSeed();
    if (gameSeed == 0)
        startGame();
    Serial.println(gameSeed);
}

void GameScene::drawBoard(){
    // int x = 20;
    // int y = 100;
    // for(int i = 0; i < 11; i++){
    //     int x = 20;
    //     for(int j = 0; i < 10; j++){
    //         if(lastBoard[i][j] == 1 && GameScene::tetrisBoard[i][j] == 0){
    //             Display::fillRect(x,y,20,20,ILI9341_BLACK);
    //         } else if (lastBoard[i][j] == 0 && GameScene::tetrisBoard[i][j] == 1) {
    //             Display::drawTetrisBlock(x,y,1);
    //         }
    //         x+= 20;
    //     }
    //     y += 20;
    // }

    int x = 20;
    int y = 100;
    for(int i = 0; i < 11; i++){
        int x = 20;
            for (int j = 0; j < 10; j++){
                if(lastBoard[i][j] == 1 && GameScene::tetrisBoard[i][j] == 0){
                Display::fillRect(x,y,20,20,ILI9341_BLACK);
                } else if (lastBoard[i][j] == 0 && GameScene::tetrisBoard[i][j] == 1) {
                    Display::drawTetrisBlock(x,y,1);
                }             
                x += 20;
            }
        y += 20;
    }
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            lastBoard[i][j] = GameScene::tetrisBoard[i][j];
        }       
    }

}

int GameScene::boardCount(){
    int count = 0;
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 10; j++){
            if(GameScene::tetrisBoard[i][j] == 1){
                count++;
            }
        }
    }
    return count;
}

void GameScene::initTimer() {
    TCCR1A = 0;
    TCCR1B |= (1 << CS12)|(1<<CS10)|(1<<WGM12);
    TCCR1C = 0;
    OCR1A = (15624/24);
    TCNT1 = 0;
    TIMSK1 |= (1<<OCIE1A);
}

void GameScene::drawScene() {
    if(GameScene::gameOver){
        Scene::setScene(Scene::LOSE_SCENE);
        Scene::draw();
        return;
    }
    if(!test){
        return;
    }

    bool* array = Controller::getActions();


    if(GameScene::blockIsMoving) {
        if(array[0]){
            GameScene::currentBlock->moveSideways(1);
        }
        else if(array[1]){
            GameScene::currentBlock->moveSideways(-1);
        }
        if(GameScene::gameTickReached){
            GameScene::currentBlock->moveDown();
            GameScene::gameTickReached = false;
        }
        
    }
    if(!GameScene::blockIsMoving) {
        delete GameScene::currentBlock;
        GameScene::currentBlock = new Square(4,0);
        GameScene::currentBlock->initBlock();
        blockIsMoving = true;
        GameScene::gameTickReached = false;
    }
    test = false;
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
