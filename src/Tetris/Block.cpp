#include "../Scenes/GameScene/GameScene.h"
#include "Block.h"
#include "HardwareSerial.h"

Block::Block(int xPos, int yPos){
    this->xPos = xPos;
    this->yPos = yPos;
    this->blockArray = new int*[4];
    for(int i = 0; i < 4; i++){
        blockArray[i] = new int[2];
        blockArray[i][0] = 0;
        blockArray[i][1] = 0;
    }
}

void Block::initBlock(){
    int valueCount = 0;
    for(int i = 0; i < 4; i++){
        valueCount += GameScene::tetrisBoard[blockArray[i][1]][blockArray[i][0]];
    }

    if(valueCount != 0){
        GameScene::gameOver = true;
        return;
    }

    for(int i = 0; i < 4; i++){
        GameScene::tetrisBoard[blockArray[i][1]][blockArray[i][0]] = 1;
    }
}

void Block::reset(int direction){
    blockArray[0][0] -= direction;
    blockArray[1][0] -= direction;
    blockArray[2][0] -= direction;
    blockArray[3][0] -= direction;
}

void Block::moveSideways(int direction){
    int tempArray[11][10] = {{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};
    Serial.println(GameScene::blockIsMoving);

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            tempArray[i][j] = GameScene::tetrisBoard[i][j];
        }       
    }

    int firstCount = GameScene::boardCount();

    for(int i = 0; i < 4; i++){
        GameScene::tetrisBoard[blockArray[i][1]][blockArray[i][0]] = 0;
    }

    blockArray[0][0] += direction;
    blockArray[1][0] += direction;
    blockArray[2][0] += direction;
    blockArray[3][0] += direction;


    for(int i = 0; i < 4; i++){
        if(blockArray[i][0] >= 0 && blockArray[i][0] < 10 ){
            GameScene::tetrisBoard[blockArray[i][1]][blockArray[i][0]] = 1;
        } else {
            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    GameScene::tetrisBoard[i][j] = tempArray[i][j];
                }       
            }
            reset(direction);
            return;
        }
        
    }

    int secondCount = GameScene::boardCount();


    if(firstCount != secondCount){
        for(int i = 0; i < 11; i++){
            for (int j = 0; j < 10; j++){
                GameScene::tetrisBoard[i][j] = tempArray[i][j];
            }
        }
        reset(direction);
        return;
    }

}

Block::~Block(){
    delete[] Block::blockArray;
}

void Block::moveDown(){
    int tempArray[11][10] = {{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}, {0}};

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            tempArray[i][j] = GameScene::tetrisBoard[i][j];
        }       
    }

    int firstCount = GameScene::boardCount();

    for(int i = 0; i < 4; i++){
        GameScene::tetrisBoard[blockArray[i][1]][blockArray[i][0]] = 0;
    }

    blockArray[0][1] += 1;
    blockArray[1][1] += 1;
    blockArray[2][1] += 1;
    blockArray[3][1] += 1;

    for(int i = 0; i < 4; i++){
        if(blockArray[i][1] < 11){
            GameScene::tetrisBoard[blockArray[i][1]][blockArray[i][0]] = 1;
        } else {
            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    GameScene::tetrisBoard[i][j] = tempArray[i][j];
                }       
            }
            GameScene::blockIsMoving = false;
            //Serial.println(GameScene::blockIsMoving);
            return;
        }
    }

    if(GameScene::blockIsMoving != false){
        int secondCount = GameScene::boardCount();

        if(firstCount != secondCount){
            for(int i = 0; i < 11; i++){
                for (int j = 0; j < 10; j++){
                    GameScene::tetrisBoard[i][j] = tempArray[i][j];
                }
            }
            GameScene::blockIsMoving = false;

        // for (int i = 0; i < 11; i++)
        //     {
        //         for (int j = 0; j < 10; j++)
        //         {
        //             Serial.print(GameScene::tetrisBoard[i][j]);
        //         }       
        //         Serial.println("");
        //     }
        //     Serial.println("----");
        return;
    }
    }

}


