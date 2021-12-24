#ifndef SRC_TETRIS_BLOCK_H_
#define SRC_TETRIS_BLOCK_H_

#include <stdint.h>

class Block {
 public:
    uint8_t** blockArray;
    uint8_t blockColor;
    uint8_t tempArray[11][10] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};

    Block(int xPos, int yPos);
    ~Block();
    void initBlock();
    void moveDown();
    void moveSideways(int direction);
    void rotate();
    void setValue(int value);
    virtual void drawSectionBlock() = 0;
    virtual void rotateBlock() = 0;

 protected:
    uint8_t xPos;
    uint8_t yPos;
    uint8_t rotationLevel;

    void copyArray(uint8_t array[11][10]);
    void resetDirection(int direction);
};

#endif  // SRC_TETRIS_BLOCK_H_
